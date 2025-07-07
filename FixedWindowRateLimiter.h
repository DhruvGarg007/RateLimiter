#ifndef FIXEDWINDOWRATELIMITER_H
#define FIXEDWINDOWRATELIMITER_H

#include "RateLimiter.h"
#include <chrono>
using namespace std;
using Clock = chrono::steady_clock;
using TimePoint = chrono::steady_clock::time_point;
using Milliseconds = chrono::milliseconds;
using ll = long long;

class FixedWindowRateLimiter : public RateLimiter {
private:
    ll window_size_ms_;
    ll max_requests_;
    ll request_count_;
    TimePoint window_start_time_;

public:
    FixedWindowRateLimiter(ll windowSizeMs, ll maxRequests);
    bool allow() override;
};

#endif 