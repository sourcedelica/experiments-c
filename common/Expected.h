#pragma once

#include <string>
#include "Error.h"

template <class T>
class Expected {
public:
    Expected(const T &value) : engaged_(true), value_(value) {}
    Expected(const Error &error) : engaged_(false), error_(error) {}
    Expected(const Expected &other) { construct(other); }

    ~Expected() {
        destroy();
    }

    Expected &operator=(const Expected &other) {
        if (engaged_ && other.engaged_)
            value_ = other.value_;
        else if (!engaged_ && !other.engaged_)
            error_ = other.error_;
        else {
            destroy();
            construct(other);
        }
        return *this;
    }

    Expected& operator=(const T& x) {
        if (engaged_) {
            value_ = x;
        } else {
            destroy();
            engaged_ = true;
            new (&value_) T(x);
        }
        return *this;
    }

    Expected& operator=(Error e) noexcept {
        if (!engaged_)
            error_ = e;
        else {
            destroy();
            engaged_ = false;
            new (&value_) Error(e);
        }
        return *this;
    }

    const Error &error() const noexcept {
        return error_;
    }

    T &value() const noexcept {
        return value_;
    }

    operator bool() const noexcept {
        return engaged_;
    }

private:
    bool engaged_;

    union {
        T value_;
        Error error_;
    };

    void construct(const Expected& other) {
        if (other.engaged_)
            new (&value_) T(other.value_);
        else
            new (&error_) Error(other.error_);
        engaged_ = other.engaged_;
    }

    void destroy() {
        if (engaged_)
            value_.~T();
        else
            error_.~Error();
    }
};
