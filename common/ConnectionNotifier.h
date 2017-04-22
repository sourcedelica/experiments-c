#pragma once

#include <vector>
#include <functional>
#include "ServerType.h"

class ConnectionNotifier {
public:
    virtual void onConnection(ServerType) const = 0;
    virtual void onReconnection(ServerType) const  = 0;
    virtual void onDisconnection() const = 0;
    virtual void onOtherConnection(ServerType) const = 0;
};

#if __cplusplus >= 201103L

struct ConnectionCallbacks : public ConnectionNotifier {
public:
    ConnectionCallbacks(
            std::function<void(ServerType)> connection_,
            std::function<void(ServerType)> reconnection_,
            std::function<void()>           disconnection_,
            std::function<void(ServerType)> otherConnection_)
        : connection(connection_), reconnection(reconnection_),
          disconnection(disconnection_), otherConnection(otherConnection_) {}

    void onConnection(ServerType serverType)      const override { if (connection) connection(serverType); }
    void onReconnection(ServerType serverType)    const override { if (reconnection) reconnection(serverType); };
    void onDisconnection()                        const override { if (disconnection) disconnection(); }
    void onOtherConnection(ServerType serverType) const override { if (otherConnection) otherConnection(serverType); };

private:
    std::function<void(ServerType)> connection;
    std::function<void(ServerType)> reconnection;
    std::function<void()>           disconnection;
    std::function<void(ServerType)> otherConnection;
};

/**
 * Collection of ConnectionCallbacks, so both client and server can use them
 */
class CompositeConnectionNotifier : public ConnectionNotifier {
public:
    CompositeConnectionNotifier(std::initializer_list<ConnectionCallbacks> initializerList) {
        for (auto &cc : initializerList) {
            notifiers.push_back(std::move(cc));
        }
    }

    virtual ~CompositeConnectionNotifier() = default;

    virtual void onConnection(ServerType serverType) const override {
        for (auto &notif : notifiers) notif.onConnection(serverType);
    }
    virtual void onReconnection(ServerType serverType) const override {
        for (auto &notif : notifiers) notif.onReconnection(serverType);
    };
    virtual void onDisconnection() const override {
        for (auto &notif : notifiers) notif.onDisconnection();
    }
    virtual void onOtherConnection(ServerType serverType) const override {
        for (auto &notif : notifiers) notif.onOtherConnection(serverType);
    };

private:
    std::vector<ConnectionCallbacks> notifiers;
};

#endif // __cplusplus >= 201103L

struct NullConnectionNotifier : public ConnectionNotifier {
public:
    void onConnection(ServerType) const override {}
    void onReconnection(ServerType) const override {}
    void onDisconnection() const override {}
    void onOtherConnection(ServerType) const override {}
};
