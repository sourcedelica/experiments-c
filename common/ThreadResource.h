#include <thread>

/**
 * If a joinable std::thread is destroyed it will terminate the program.
 * This class is an RAII wrapper for std::thread that either joins or detaches
 * the thread before it is destroyed, preventing program termination.
 *
 * Typical usage:
 *
 * class Foo {
 *   Foo() : tr(std::thread(doLoop)) {}
 *
 * private:
 *   ...
 *   ThreadResource tr;  // Should be the last data member in the containing class
 *
 *   static void doLoop() { ... }
 * }
 *
 */
class ThreadResource {
public:
    enum class OnDestroy { Join, Detach };

    ThreadResource() {}

    /**
     * Create thread resource
     *
     * @param thread    Running (joinable) thread which will be moved into this object
     * @param onDestroy Behavior when this object is destroyed:
     *                  OnDestroy::Join - join thread
     *                  OnDestroy::Detach - detach thread
     */
    ThreadResource(std::thread&& thread, OnDestroy onDestroy = OnDestroy::Join)
            : onDestroy(onDestroy), thread(std::move(thread)) {}

    /**
     * Start thread resource
     *
     * If it is not possible to create a thread when this object is constructed,
     * use the default constructor and then call this function when creating the thread.
     *
     * The parameters are the same as the non-default constructor
     */
    void start(std::thread&& thread, OnDestroy onDestroy = OnDestroy::Join) {
        assert(!this->thread.joinable());  // non-default constructor was used
        this->thread = std::move(thread);
        this->onDestroy = onDestroy;
    }

    ~ThreadResource() {
        if (thread.joinable()) {
            if (onDestroy == OnDestroy::Join) {
                thread.join();
            } else {
                thread.detach();
            }

        }
    }

    ThreadResource(ThreadResource const&) = delete;
    ThreadResource &operator=(ThreadResource const&) = delete;
    ThreadResource(ThreadResource&&) = default;
    ThreadResource &operator=(ThreadResource&&) = default;

    std::thread &get() { return thread; }

private:
    OnDestroy onDestroy;
    std::thread thread;
};

