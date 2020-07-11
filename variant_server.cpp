#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma ide diagnostic ignored "MemberFunctionCanBeStatic"

#include <iostream>
#include <unordered_map>
#include <utility>
#include <boost/variant.hpp>
#include "match_hana.h"

// Server functionality that components need to access
// Note - not templated, so can be implemented in .cpp
class Server {
public:
    Server() = default;
};

// Contains the components
template <typename ...Ts>
class CompositeServer : public Server {
    // Using boost::blank to avoid requiring an (unused) default constructor for each component
    using component_t = boost::variant<boost::blank, Ts...>;

    std::unordered_map<std::string, component_t> components;

public:
    CompositeServer() : Server() {
        registerComponent<Ts...>(std::forward<Ts>(Ts(this))...);
        connectAll();  // Assuming this is needed in addition to component constructor
    }

    ~CompositeServer() {
        closeAll();    // Assuming this is needed in addition to component destructor
    }

private:
    template <typename T>
    void registerComponent(T&& policy) {
        std::string name = policy.name();
        std::cout << "Registering component: " << name << std::endl;
        components.emplace(name, std::forward<T>(policy));
    }

    template <typename T, typename ...Tz>
    void registerComponent(T&& t, Tz&&... ts) {
        registerComponent(std::forward<T>(t));
        registerComponent<Tz...>(std::forward<Tz>(ts)...);
    }

    // Call connect() on all components that have that method
    void connectAll() {
        for (auto& tup : components) {
            match(tup.second)(
                [](auto& component) -> decltype(component.connect(), void()) {
                    component.connect();
                }
            );
        }
    }

    // Call close() on all components that have that method
    void closeAll() {
        for (auto& tup : components) {
            match(tup.second)(
                [](auto& component) -> decltype(component.close(), void()) {
                    component.close();
                }
            );
        }
    }
};

class NetworkA {
public:
    // Note: make sure that moved-from destructor doesn't touch any moved-to data
    NetworkA(NetworkA&&) = default;
    NetworkA& operator=(NetworkA&& that) = default;
    NetworkA(const NetworkA&) = delete;       // Move-only
    NetworkA& operator=(NetworkA&) = delete;

    template <typename ...Ts>
    explicit NetworkA(CompositeServer<Ts...>* server) : server(server) {}
    ~NetworkA() { std::cout << "Destroying: " << Name << std::endl; }

    static constexpr const char* Name = "NetworkA";
    static std::string name() { return Name; }
    void close() { std::cout << "Closing: " << Name << std::endl; }
    void connect() { std::cout << "Connecting: " << Name << std::endl; }
    void networkA() {}

private:
    Server *server;
};

class NetworkB {
public:
    NetworkB(NetworkB&&) = default;
    NetworkB& operator=(NetworkB&&) = default;
    NetworkB(const NetworkB&) = delete;
    NetworkB& operator=(NetworkB&) = delete;
    
    template <typename ...Ts>
    explicit NetworkB(CompositeServer<Ts...>* server) : server(server) {}
    ~NetworkB() { std::cout << "Destroying: " << Name << std::endl; }

    static constexpr const char* Name = "NetworkB";
    static std::string name() { return Name; }
    void close() { std::cout << "Closing: " << Name << std::endl; }
    void connect() { std::cout << "Connecting: " << Name << std::endl; }
    void networkB() {}

private:
    Server *server;
};

class Database {
public:
    Database(Database&&) = default;
    Database& operator=(Database&&) = default;
    Database(const Database&) = delete;
    Database& operator=(Database&) = delete;

    template <typename ...Ts>
    explicit Database(CompositeServer<Ts...>* server) : server(server) {}
    ~Database() { std::cout << "Destroying: " << Name << std::endl; }

    static constexpr const char* Name = "Database";
    static std::string name() { return Name; }
    void close() { std::cout << "Closing: " << Name << std::endl; }
    void database() {}

private:
    Server *server;
};

int main(int argc, char **argv) {
    CompositeServer<NetworkA, NetworkB, Database> server{};
}
