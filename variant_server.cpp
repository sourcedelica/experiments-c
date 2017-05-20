#include <string>
#include <iostream>
#include <unordered_map>
#include <boost/variant.hpp>
#include "make_overload.h"

// Contains any server functionality that components need to access
class Server {
public:
    Server() = default;
};

// Contains the components
template <typename ...Ts>
class CompositeServer : public Server {
    using component_t = boost::variant<Ts...>;

public:
    CompositeServer() : Server() {
        registerComponent<Ts...>(std::forward<Ts>(Ts(this))...);
        connectAll();
    }

    ~CompositeServer() {
        auto visitor = vrm::make_overload(
                [](auto &component){ component.close(); }
        );
        for (auto &tup : components) {
            boost::apply_visitor(visitor, tup.second);
        }
    }

private:
    std::unordered_map<std::string, component_t> components;

    template <typename T>
    void registerComponent(T &&policy) {
        std::string name = policy.name();
        std::cout << "Registering: " << name << std::endl;
        components.emplace(name, std::move(policy));
        auto i = 0;
    }

    template <typename T, typename ...Tz>
    void registerComponent(T&& t, Tz&&... ts) {
        registerComponent(std::forward<T>(t));
        registerComponent<Tz...>(std::forward<Tz>(ts)...);
    }

    void connectAll() {
        auto visitor = vrm::make_overload(
                [](auto &component) -> decltype(component.connect(), void()) { component.connect(); },
                [](...) -> void {}
        );
        for (auto &tup : components) {
            boost::apply_visitor(visitor, tup.second);
        }
    }
};

class NetworkA {
public:
    NetworkA() = default;
    NetworkA(const NetworkA&) = delete;  // Move-only
    NetworkA& operator=(NetworkA&) = delete;
    // Note: when moving, make sure that when moved-from destructor runs it is safe
    NetworkA(NetworkA&&) = default;
    NetworkA& operator=(NetworkA&& that) = default;

    template <typename ...Ts>
    NetworkA(CompositeServer<Ts...> *server) : server(server) {}

    ~NetworkA() { std::cout << "Destroying: " << name() << " server: " << server << std::endl; }

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