// From https://www.fluentcpp.com/2020/06/26/implementing-a-universal-reference-wrapper/

#include <algorithm>
#include <utility>
#include <vector>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

struct owner_tag {};
struct reference_tag {};

template <typename Tag, typename T>
struct universal_wrapper;


template <typename T>
struct universal_wrapper<owner_tag, T>
{
private:
    T value;

public:
    constexpr universal_wrapper(T&& t)  // NOLINT
            : value(std::move(t)) {}

    [[nodiscard]] constexpr T& get() &
    { return value; }

    [[nodiscard]] constexpr T&& get() &&
    { return std::move(value); }

    [[nodiscard]] constexpr const T& get() const &
    { return value; }

    [[nodiscard]] constexpr universal_wrapper<reference_tag, const T> ref() const &
    {
        return universal_wrapper<reference_tag, const T>{get()};
    }

    [[nodiscard]] constexpr universal_wrapper<reference_tag, const T> ref() &
    {
        return universal_wrapper<reference_tag, const T>{get()};
    }

    [[nodiscard]] constexpr universal_wrapper<reference_tag, const T> ref() && = delete;

    [[nodiscard]] constexpr universal_wrapper<reference_tag, T> mutable_ref() &
    {
        return universal_wrapper<reference_tag, T>{get()};
    }

    [[nodiscard]] constexpr universal_wrapper<reference_tag, T> mutable_ref() && = delete;
};

template <typename T>
struct universal_wrapper<reference_tag, T>
{
private:
    T& value;

public:
    constexpr universal_wrapper(T& t)   // NOLINT
            : value(t)
    {}

    [[nodiscard]] constexpr T& get()
    { return value; }

    [[nodiscard]] constexpr const T& get() const
    { return value; }
};

template <typename T>
using reference_to = universal_wrapper<reference_tag, T>;

template <typename T>
using owner = universal_wrapper<owner_tag, T>;

namespace detail
{
    template <typename T>
    struct ownership_tag : std::conditional<
            std::is_lvalue_reference_v<T>,
            reference_tag,
            owner_tag>
    {};

    template <typename T>
    struct infer_universal_wrapper
    {
        using tag_type = typename ownership_tag<T>::type;
        using value_type = std::remove_reference_t<T>;
        using type = universal_wrapper<tag_type, value_type>;
    };

    template <typename T>
    using infer_universal_wrapper_t = typename infer_universal_wrapper<T>::type;

}

template <typename T>
constexpr auto make_universal_wrapper(T&& t)
{
    return detail::infer_universal_wrapper_t<T>(std::forward<T>(t));
}

// See https://www.fluentcpp.com/2020/06/05/out-of-line-lambdas/
template<typename Function>
class OutOfLineLambda
{
public:
    explicit OutOfLineLambda(Function function)
            : function_(function)
    {}

    template<typename Context>
    auto operator()(const Context& context) const
    {
        return [wrapper = make_universal_wrapper(std::forward<Context>(context)), this]
                (auto&&... objects)
        {
            return function_(wrapper.get(), std::forward<decltype(objects)>(objects)...);
        };
    }

    template<typename Context>
    auto operator()(Context&& context) const
    {
        return [wrapper = make_universal_wrapper(std::forward<Context>(context)), this]
                (auto&&... objects) mutable
        {
            return function_(std::move(wrapper).get(), std::forward<decltype(objects)>(objects)...);
        };
    }

private:
    Function function_;
};

/***********************************************************************************/

struct Car{};
struct GearBox{};

void inspect(reference_to<const Car>) {}

owner<Car> replace(owner<Car> car) {
    return car;
}

bool repairGearbox(GearBox &&box, Car &car) { return true; }

void repair(reference_to<Car> car) {
//    replace(std::move(car));  // this does not compile anymore
}

int main(int argc, const char** argv) {
    Car mycar;
    GearBox gearBox;

    repair(mycar);
    mycar = replace(std::move(mycar)).get();  // NOLINT

    std::vector<Car> cars, repairedCars;
    std::copy_if(cars.begin(), cars.end(), std::back_inserter(repairedCars),
            OutOfLineLambda(repairGearbox)(std::move(gearBox)));   // NOLINT
}
