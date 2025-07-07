#include "FixedWindowRateLimiter.h"
using namespace std; 

FixedWindowRateLimiter::FixedWindowRateLimiter(ll windowSizeMs, ll maxRequests)
    : window_size_ms_(windowSizeMs), max_requests_(maxRequests),
      request_count_(0), window_start_time_(Clock::now()) {}

bool FixedWindowRateLimiter::allow() 
{
    TimePoint now = Clock::now();
    Milliseconds time_elapsed = chrono::duration_cast<Milliseconds>(now - window_start_time_);

    if (time_elapsed.count()>=window_size_ms_) 
    {
        window_start_time_ = now;
        request_count_ = 0;
    }

    if (request_count_<max_requests_) 
    {
        request_count_++;
        return true;
    }
    return false;
}