#include <string>
#include <iostream>
#include <unordered_map>
#include <boost/variant.hpp>

template <typename T> using identity_t = T;

// Contains any server functionality that components need to access
class Server {
public:
    Server() = default;
};

// Contains the components
template <typename ...Ts>
class CompositeServer : public Server {
public:
    using component_t = boost::variant<Ts...>;

    CompositeServer() : Server() {
        registerBase<Ts...>(identity_t<Ts>(this)...);
        connectAll();
    }

    ~CompositeServer() {
        visitor_closer_t visitor;
        for (auto &tup : components) {
            boost::apply_visitor(visitor, tup.second);
        }
    }

private:
    std::unordered_map<std::string, component_t> components;

    // TODO - replace these functors with lambdas using boost::hana::overload or vr::core
    struct visitor_closer_t {
        template <typename T>
        void operator()(T base) {
            base.close();
        }
    };

    struct visitor_connect_t {
        template <typename T>
        auto operator()(T base) -> decltype(base.connect(), void()){
            base.connect();
        }
        auto operator()(...) -> void {}
    };

    template <typename T>
    void registerBase(T&& policy) {
        std::string name = policy.name();
        std::cout << "Registering: " << name << std::endl;
        components[name] = std::move(policy);
    }

    template <typename T, typename ...Tz>
    void registerBase(T&& t, Tz&&... ts) {
        registerBase(std::forward<T>(t));
        registerBase<Tz...>(std::forward<Tz>(ts)...);
    }

    void connectAll() {
        visitor_connect_t visitor;
        for (auto &tup : components) {
            boost::apply_visitor(visitor, tup.second);
        }
    }
};

class NetworkA {
public:
    NetworkA() = default;

    template <typename ...Ts>
    NetworkA(CompositeServer<Ts...> *server) : server(server) {}

    std::string name() { return "NetworkA"; }

    void close() { std::cout << "Closing: " << name() << std::endl; }

    void connect() { std::cout << "Connecting: " << name() << std::endl; }

    void networkA() {}

private:
    Server *server;
};

class NetworkB {
public:
    NetworkB() = default;

    template <typename ...Ts>
    NetworkB(CompositeServer<Ts...> *server) : server(server) {}

    std::string name() { return "NetworkB"; }

    void close() { std::cout << "Closing: " << name() << std::endl; }

    void connect() { std::cout << "Connecting: " << name() << std::endl; }

    void networkB() {}

private:
    Server *server;
};

class Database {
public:
    Database() = default;

    template <typename ...Ts>
    Database(CompositeServer<Ts...> *server) : server(server) {}

    std::string name() { return "Database"; }

    void close() { std::cout << "Closing: " << name() << std::endl; }

    void database() {}

private:
    Server *server;
};

int main(int argc, char **argv) {
    CompositeServer<NetworkA, NetworkB, Database> server{};
}