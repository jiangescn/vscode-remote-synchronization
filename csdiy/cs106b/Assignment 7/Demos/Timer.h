#ifndef Timer_Included
#define Timer_Included

#include <chrono>

namespace Timing {
    /**
     * 表示秒表的类型，用于测量各种操作的耗时
     * 操作。
     */
    class Timer {
    public:
        void start() {
            current = std::chrono::high_resolution_clock::now();
        }

        void stop() {
            total += std::chrono::high_resolution_clock::now() - current;
        }

        double elapsed() const {
            return std::chrono::duration_cast<std::chrono::nanoseconds>(total).count();
        }

    private:
        std::chrono::high_resolution_clock::duration total =
                std::chrono::high_resolution_clock::duration::zero();
        std::chrono::high_resolution_clock::time_point current;
    };
}

#endif
