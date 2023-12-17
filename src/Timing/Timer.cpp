#include "Timer.h"

namespace Nova_Lang
{
        Timer::Timer()
        {
            start_time = std::chrono::high_resolution_clock::now();
        }

        Timer::~Timer() = default;

        float Timer::getDuration()
        {
            end_time = std::chrono::high_resolution_clock::now();
            duration = end_time - start_time;

            // Convert from seconds to milliseconds
            float ms = duration.count() * 1000.0f;

            return ms;
        }
}