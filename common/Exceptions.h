#pragma once

#include <string>
#include <exception>

class Exception : public std::runtime_error {
public:
    Exception() : std::runtime_error("") {}
    Exception(const std::string &message) : std::runtime_error(message) {}
    Exception(const Exception &other) : std::runtime_error(other.what()) {}
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
