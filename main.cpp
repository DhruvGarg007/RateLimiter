#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include "TokenBucketRateLimiter.h"
#include "LeakyBucketRateLimiter.h"
#include "FixedWindowRateLimiter.h"

using namespace std;
using namespace std::chrono; 

void run_simulation(RateLimiter& limiter, const string& name,
                    int total_requests, milliseconds request_interval_ms) {
    cout << "--- Simulating " << name << " ---" << endl;
    cout << "Total Requests to Attempt: " << total_requests << endl;
    cout << "Request Interval: " << request_interval_ms.count() << "ms" << endl;

    int allowed_count = 0;
    int denied_count = 0;

    auto start_time = steady_clock::now();

    for (int i = 0; i < total_requests; ++i) {
        if (limiter.allow()) {
            allowed_count++;
            // cout << name << ": Request " << i + 1 << " ALLOWED" << endl;
        } else {
            denied_count++;
            // cout << name << ": Request " << i + 1 << " DENIED" << endl;
        }
        this_thread::sleep_for(request_interval_ms);
    }

    auto end_time = steady_clock::now(); // End timer for this simulation
    auto elapsed_ms = duration_cast<milliseconds>(end_time - start_time);

    cout << "Simulation Results for " << name << ":" << endl;
    cout << "  Allowed: " << allowed_count << endl;
    cout << "  Denied:  " << denied_count << endl;
    cout << "  Total:   " << total_requests << endl;
    cout << "  Time Taken: " << elapsed_ms.count() << " ms" << endl;
    cout << "  Effective Rate: " << fixed << setprecision(2) << (double)allowed_count / (elapsed_ms.count() / 1000.0) << " req/sec" << endl;

    cout << "-------------------------------------" << endl << endl;
}


int main() {
    cout << "--- Rate Limiting Algorithms Quantifiable Demonstration ---" << endl;
    cout << "---------------------------------------------------------" << endl << endl;

    cout << "### Scenario 1: High Burst Traffic (100 requests in 1 second) ###" << endl;
    int burst_requests = 100;
    milliseconds burst_interval = milliseconds(10);

    // Token Bucket: Capacity 10, Refill 5 tokens/sec
    // Expect: Initial 10 allowed, then denied until refill
    TokenBucketRateLimiter tbLimiter1(10, 5);
    run_simulation(tbLimiter1, "Token Bucket (Burst)", burst_requests, burst_interval);

    // Leaky Bucket: Capacity 5, Leak 2 requests/sec
    // Expect: Initial 5 allowed, then most denied as bucket fills fast
    LeakyBucketRateLimiter lbLimiter1(5, 2);
    run_simulation(lbLimiter1, "Leaky Bucket (Burst)", burst_requests, burst_interval);

    // Fixed Window: Window 1000ms, Max 5 requests
    // Expect: 5 allowed in first second, then all denied
    FixedWindowRateLimiter fwLimiter1(1000, 5);
    run_simulation(fwLimiter1, "Fixed Window (Burst)", burst_requests, burst_interval);

    cout << "Press Enter to continue to Scenario 2..." << endl;
    cin.ignore();
    cin.get(); 

    cout << "### Scenario 2: Moderate Steady Traffic (50 requests over 10 seconds) ###" << endl;
    int steady_requests = 50;
    milliseconds steady_interval = milliseconds(200);

    // Token Bucket: Capacity 10, Refill 5 tokens/sec
    // Expect: All allowed, as rate is equal to refill
    TokenBucketRateLimiter tbLimiter2(10, 5);
    run_simulation(tbLimiter2, "Token Bucket (Steady)", steady_requests, steady_interval);

    // Leaky Bucket: Capacity 5, Leak 2 requests/sec
    // Expect: Many denied as incoming rate (5/s) > leak rate (2/s)
    LeakyBucketRateLimiter lbLimiter2(5, 2);
    run_simulation(lbLimiter2, "Leaky Bucket (Steady)", steady_requests, steady_interval);

    // Fixed Window: Window 1000ms, Max 5 requests
    // Expect: All allowed, as rate is equal to max per window
    FixedWindowRateLimiter fwLimiter2(1000, 5);
    run_simulation(fwLimiter2, "Fixed Window (Steady)", steady_requests, steady_interval);

    cout << "--- End of Quantifiable Demonstration ---" << endl;
    return 0;
}