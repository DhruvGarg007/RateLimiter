#ifndef LEAKYBUCKETRATELIMITER_H
#define LEAKYBUCKETRATELIMITER_H

#include "RateLimiter.h"
#include <chrono>
using ll = long long;
using ld = long double;
using Clock = std::chrono::steady_clock;
using TimePoint = Clock::time_point;
using Milliseconds = std::chrono::milliseconds;

class LeakyBucketRateLimiter : public RateLimiter 
{
private:
    ll capacity_;
    ll current_requests_;
    ld leak_rate_per_ms_;
    TimePoint last_leak_time_;

public:
    LeakyBucketRateLimiter(ll capacity, ld leakRatePerSecond);
    bool allow() override;
};

#endif