#include <chrono>
#include <iostream>
#include <thread>

int main() {
    std::cout << "Sleeping for 30 secs..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));
}

