#include <iostream>
#include <thread>
#include <chrono>

#include "TokenBucketRateLimiter.h"
#include "LeakyBucketRateLimiter.h"
#include "FixedWindowRateLimiter.h"

using namespace std;

int main() 
{ 
    cout << "--- Rate Limiting Algorithms Demonstration ---" << endl;
    cout << "-------------------------------------------------------------" << endl << endl;

    //Token Bucket Rate Limiter Example
    cout << "### Token Bucket Rate Limiter (Capacity: 10, Refill: 2 tokens/sec) ###" << endl;
    TokenBucketRateLimiter tbLimiter(10, 2);
    for (int i=0; i<20; i++)
    {
        if(tbLimiter.allow()){
            cout << "Token Bucket: Request " << i + 1 << " ALLOWED" << endl;
        } else {
            cout << "Token Bucket: Request " << i + 1 << " DENIED" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
    cout << "Press Enter to continue to next example..." << endl;
    cin.ignore();


    // --- Leaky Bucket Rate Limiter Example ---
    cout << "### Leaky Bucket Rate Limiter (Capacity: 5, Leak: 1 request/sec) ###" << endl;
    LeakyBucketRateLimiter lbLimiter(5, 1);
    for (int i = 0; i < 15; ++i) {
        if (lbLimiter.allow()) {
            cout << "Leaky Bucket: Request " << i + 1 << " ALLOWED" << endl;
        } else {
            cout << "Leaky Bucket: Request " << i + 1 << " DENIED (Bucket Full)" << endl;
        }
        if (i < 5) {
            this_thread::sleep_for(chrono::milliseconds(100));
        } else {
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
    cout << endl;
    cout << "Press Enter to continue to next example..." << endl;
    cin.ignore();


    // --- Fixed Window Rate Limiter Example ---
    cout << "### Fixed Window Rate Limiter (Window: 2000ms, Max Requests: 3) ###" << endl;
    FixedWindowRateLimiter fwLimiter(2000, 3);
    for (int i = 0; i < 10; ++i) {
        if (fwLimiter.allow()) {
            cout << "Fixed Window: Request " << i + 1 << " ALLOWED" << endl;
        } else {
            cout << "Fixed Window: Request " << i + 1 << " DENIED (Limit Reached)" << endl;
        }
        if (i == 2 || i == 5) {
            this_thread::sleep_for(chrono::milliseconds(2100));
        } else {
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
    cout << endl;
    cout << "--- End of Demonstration ---" << endl;
    return 0;
}