#include <string>
#include <iostream>
#include <unordered_map>
#include <boost/variant.hpp>
#include "match.h"

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
        for (auto& tup : components) {
            vrm::match(tup.second)([](auto& component){ component.close(); });
        }
    }

private:
    std::unordered_map<std::string, component_t> components;

    template <typename T>
    void registerComponent(T&& policy) {
        std::string name = policy.name();
        std::cout << "Registering: " << name << std::endl;
        components.emplace(name, std::move(policy));
    }

    template <typename T, typename ...Tz>
    void registerComponent(T&& t, Tz&&... ts) {
        registerComponent(std::forward<T>(t));
        registerComponent<Tz...>(std::forward<Tz>(ts)...);
    }

    void connectAll() {
        for (auto& tup : components) {
            vrm::match(tup.second)(
                [](auto& component) -> decltype(component.connect(), void()) { component.connect(); },
                [](auto& ...) -> void {}
            );
        }
    }
};

class NetworkA {
public:
    NetworkA() = default;                // Needed for variant
    NetworkA(const NetworkA&) = delete;  // Move-only
    NetworkA& operator=(NetworkA&) = delete;
    // Note: when moving, make sure that when moved-from destructor doesn't touch any moved-to data
    NetworkA(NetworkA&&) = default;
    NetworkA& operator=(NetworkA&& that) = default;

    template <typename ...Ts>
    NetworkA(CompositeServer<Ts...>* server) : server(server) {}

    ~NetworkA() { std::cout << "Destroying: " << Name << std::endl; }

    static constexpr const char* Name = "NetworkA";

    std::string name() { return Name; }

    void close() { std::cout << "Closing: " << Name << std::endl; }

    void connect() { std::cout << "Connecting: " << Name << std::endl; }

    void networkA() {}

private:
    Server *server;
};

class NetworkB {
public:
    NetworkB() = default;                
    NetworkB(const NetworkB&) = delete;  
    NetworkB& operator=(NetworkB&) = delete;
    NetworkB(NetworkB&&) = default;
    NetworkB& operator=(NetworkB&&) = default;
    
    template <typename ...Ts>
    NetworkB(CompositeServer<Ts...>* server) : server(server) {}

    ~NetworkB() { std::cout << "Destroying: " << Name << std::endl; }

    static constexpr const char* Name = "NetworkB";

    std::string name() { return Name; }

    void close() { std::cout << "Closing: " << Name << std::endl; }

    void connect() { std::cout << "Connecting: " << Name << std::endl; }

    void networkB() {}

private:
    Server *server;
};

class Database {
public:
    Database() = default;
    Database(const Database&) = delete;
    Database& operator=(Database&) = delete;
    Database(Database&&) = default;
    Database& operator=(Database&&) = default;

    template <typename ...Ts>
    Database(CompositeServer<Ts...>* server) : server(server) {}

    ~Database() { std::cout << "Destroying: " << Name << std::endl; }

    static constexpr const char* Name = "Database";

    std::string name() { return Name; }

    void close() { std::cout << "Closing: " << Name << std::endl; }

    void database() {}

private:
    Server *server;
};

int main(int argc, char **argv) {
    CompositeServer<NetworkA, NetworkB, Database> server{};
}