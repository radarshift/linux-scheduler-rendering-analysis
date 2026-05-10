#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>
#include <cmath>

using clock_type = std::chrono::steady_clock;

std::atomic<bool> running(true);

void workerTask() {

    volatile double value = 0.0;

    while (running.load()) {

        // Sustained floating-point computation
        for (int i = 1; i < 1000; i++) {
            value += std::sin(i) * std::cos(i);
        }
    }
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        std::cout << "Usage: ./stressor <thread_count> <duration_seconds>\n";
        return -1;
    }

    int threadCount = std::stoi(argv[1]);
    int durationSeconds = std::stoi(argv[2]);

    std::cout << "Starting CPU stressor\n";
    std::cout << "Threads: " << threadCount << "\n";
    std::cout << "Duration: " << durationSeconds << " seconds\n";

    std::vector<std::thread> workers;

    auto startTime = clock_type::now();

    // Spawn worker threads
    for (int i = 0; i < threadCount; i++) {
        workers.emplace_back(workerTask);
    }

    // Wait for duration
    while (true) {

        auto now = clock_type::now();

        auto elapsed =
            std::chrono::duration_cast<std::chrono::seconds>(
                now - startTime
            ).count();

        if (elapsed >= durationSeconds) {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    running.store(false);

    // Join threads
    for (auto& worker : workers) {
        worker.join();
    }

    std::cout << "CPU stressor finished\n";

    return 0;
}