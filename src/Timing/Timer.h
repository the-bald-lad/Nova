#pragma once

#include <chrono>

namespace Nova_Lang
{
    struct Timer
    {
        std::chrono::high_resolution_clock::time_point start_time, end_time;
        std::chrono::duration<float> duration {};

        // Will get the starting time when the object is created
        Timer();

        ~Timer();  // Default destructor

        // Returns the duration of the timer in milliseconds
        float getDuration();
    };
}