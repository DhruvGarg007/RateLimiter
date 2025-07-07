#include "LeakyBucketRateLimiter.h"
#include <algorithm> 
using namespace std; 

LeakyBucketRateLimiter::LeakyBucketRateLimiter(ll capacity,ld leakRatePerSecond)
    : capacity_(capacity),current_requests_(0),
      leak_rate_per_ms_(leakRatePerSecond/1000.0),
      last_leak_time_(Clock::now()) {}

bool LeakyBucketRateLimiter::allow() 
{
    TimePoint now=Clock::now();
    Milliseconds time_elapsed=chrono::duration_cast<Milliseconds>(now-last_leak_time_);

    current_requests_=max(0LL,current_requests_-static_cast<long>(time_elapsed.count()*leak_rate_per_ms_));
    last_leak_time_=now;

    if (current_requests_<capacity_) 
    {
        current_requests_++;
        return true;
    }
    return false;
}