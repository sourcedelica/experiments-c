#pragma once

#include <string>
#include <exception>

class Exception : public std::runtime_error {
public:
    Exception() : std::runtime_error("") {}
    Exception(const std::string &message) : std::runtime_error(message) {}
    Exception(const Exception &other) : std::runtime_error(other.what()) {}
};

class ClientInitializationException : public Exception {
public:
    ClientInitializationException() : Exception("Client not initialized") {}
    ClientInitializationException(const std::string &message) : Exception(message) {}
};

class NoServersConnectedException : public ClientInitializationException {
public:
    NoServersConnectedException() : ClientInitializationException("Not connected to primary or backup") {}
    NoServersConnectedException(const std::string &message) : ClientInitializationException(message) {}
};

class ClientTerminatingException : public Exception {
public:
    ClientTerminatingException() : Exception("Client is terminating") {}
};

class TimeoutException : public Exception {
public:
    TimeoutException(const std::string &message) : Exception(message) {}
};

class RequestTimeoutException : public TimeoutException {
public:
    RequestTimeoutException() : TimeoutException("Request timed out") {}
    RequestTimeoutException(const std::string &message) : TimeoutException(message) {}
};

class UnexpectedResponseException : public Exception {
public:
    UnexpectedResponseException() : Exception("Unexpected response") {}
};

class ZeroMQException : public Exception {
public:
    ZeroMQException(const std::string &message) : Exception(message) {}
};