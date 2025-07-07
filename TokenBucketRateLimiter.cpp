#include "TokenBucketRateLimiter.h"
#include <algorithm> 
using namespace std;

TokenBucketRateLimiter::TokenBucketRateLimiter(ld capacity, ld refillRatePerSecond)
    : capacity_(capacity), tokens_(capacity),
      refill_rate_per_ms_(refillRatePerSecond / 1000.0),
      last_refill_time_(Clock::now()) {}

bool TokenBucketRateLimiter::allow() {

    TimePoint now = Clock::now();
    Milliseconds time_elapsed = chrono::duration_cast<Milliseconds>(now - last_refill_time_);

    tokens_ = min(capacity_, tokens_ + time_elapsed.count() * refill_rate_per_ms_);
    last_refill_time_ = now;

    if (tokens_>=1.0) 
    {
        tokens_-=1.0;
        return true;
    }
    return false;
}