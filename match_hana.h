#pragma once

#include <boost/variant.hpp>
#include <boost/hana/functional/overload_linearly.hpp>

template <typename ...TVariants>
constexpr auto match(TVariants&&... vs) {
    return [&vs...](auto&&... fs) -> decltype(auto) {
        auto visitor = boost::hana::overload_linearly(
                std::forward<decltype(fs)>(fs)...,
                [](auto& ...) {}
        );

        return boost::apply_visitor(visitor, std::forward<TVariants>(vs)...);
    };
}
