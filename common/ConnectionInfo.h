#pragma once

#include <string>
#include <sstream>

struct ConnectionInfo {
public:
    std::string host;
    uint16_t port;
    uint16_t broadcastPort;
    uint16_t registerPort;
    uint16_t pingPort;


    ConnectionInfo() : port(0), broadcastPort(0) { }
    ConnectionInfo(const std::string& _host, uint16_t _port, uint16_t _broadcastPort = 0,
                   uint16_t _registerPort = 0, uint16_t _pingPort = 0)
            : host(_host), port(_port), broadcastPort(_broadcastPort), registerPort(_registerPort), pingPort(_pingPort) {

        if (broadcastPort == 0 && _port != 0) broadcastPort = port + uint16_t(1);
        if (registerPort == 0  && _port != 0)  registerPort = port + uint16_t(2);
        if (pingPort == 0      && _port != 0)      pingPort = port + uint16_t(3);
    }
    ~ConnectionInfo() { }
#if __cplusplus > 201103L
    ConnectionInfo(const ConnectionInfo &) = default;
#endif

    std::string toString() const
    {
        std::stringstream stream;
        stream << host << ":"  << port << "," << broadcastPort << "," << registerPort << "," << pingPort;
        return stream.str();
    }

    bool isValid() const { return port != 0 || broadcastPort != 0; }
};