#ifndef TOKENBUCKETRATELIMITER_H
#define TOKENBUCKETRATELIMITER_H

#include "RateLimiter.h"
#include <chrono>
using namespace std;
using ll = long long;
using ld = long double;
using Clock = chrono::steady_clock;
using TimePoint = Clock::time_point;
using Milliseconds = chrono::milliseconds;

class TokenBucketRateLimiter : public RateLimiter {
private:
    ld capacity_;
    ld tokens_;
    ld refill_rate_per_ms_;
    TimePoint last_refill_time_;

public:
    TokenBucketRateLimiter(ld capacity, ld refillRatePerSecond);
    bool allow() override;
};

#endif