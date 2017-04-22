#pragma once

#include <thread>

/**
 * Create a thread that does not live outside the scope of the current block.
 * Useful for preventing dangling references from the thread to variables in the block.
 */
class ScopedThread {
public:
    explicit ScopedThread(std::thread t) : thread(std::move(t)) {
        if (!thread.joinable()) throw std::logic_error("Thread not joinable");
    }

    ~ScopedThread() { thread.join(); }

    ScopedThread(ScopedThread &&other) : thread(std::move(other.thread)) {}

    ScopedThread(ScopedThread const &) = delete;
    ScopedThread &operator=(ScopedThread const &) = delete;

private:
    std::thread thread;
};

template <typename... Ts>
ScopedThread makeScopedThread(Ts&&... ts) {
    return ScopedThread(std::thread(std::forward<Ts>(ts)...));
}