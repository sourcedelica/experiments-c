#pragma once

#include <string>

class Error {
public:
    enum Code { Unknown, ClientInitialization, Timeout, ZeroMQ, ClientTerminating };

    static std::string Message(Code code) {
        switch(code) {
            case Unknown:              return "Unknown";
            case ClientInitialization: return "Client not initialized";
            case Timeout:              return "Timeout";
            case ZeroMQ:               return "ZeroMQ error";
            case ClientTerminating:    return "Client is shutting down";
        }
        return "Invalid code";
    };

    Error() : code_(Unknown), message_(Message(Unknown)) {}
    Error(Code code) : code_(code), message_(Message(code)) {}
    Error(Code code, const std::string &message) : code_(code), message_(message) {}

    Code code() const { return code_; }

private:
    Code code_;
    std::string message_;
};
