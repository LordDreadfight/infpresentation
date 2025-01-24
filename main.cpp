#include <iostream>
#include <chrono>
#include <string>
#include <vector>
using namespace std;
using namespace std::chrono;

// Branch prediction hints
#define likely(x)    __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)

unsigned long long fibonacci(int n) {
    unsigned long long base_case = (n <= 1);
    unsigned long long result = n * base_case;
    
    // Main calculation only happens if n > 1
    unsigned long long a = 0, b = 1;
    
    // Unrolled loop for better branch prediction and instruction pipelining
    // Process 4 numbers at a time
    int i = 2;
    for (; likely(i + 3 <= n); i += 4) {
        unsigned long long temp = b;
        b = a + b;
        a = temp;
        
        temp = b;
        b = a + b;
        a = temp;
        
        temp = b;
        b = a + b;
        a = temp;
        
        temp = b;
        b = a + b;
        a = temp;
    }
    
    // Handle remaining iterations (0-3 iterations)
    for (; likely(i <= n); ++i) {
        unsigned long long temp = b;
        b = a + b;
        a = temp;
    }
    
    // Branchless return using multiplication
    return (result * (n <= 1)) + (b * (n > 1));
}

vector<unsigned long long> fibonacci_sequence(int n) {
    // Pre-allocate memory to avoid reallocation
    vector<unsigned long long> sequence;
    sequence.reserve(n + 1);
    
    // Add known first values to avoid branches in the main loop
    sequence.push_back(0);  // F(0)
    
    if (likely(n >= 1)) {
        sequence.push_back(1);  // F(1)
        
        // Calculate rest using optimized loop
        sequence.reserve(n + 1);
        for (int i = 2; likely(i <= n); ++i) {
            // Direct calculation using last two values
            // This is branchless and highly predictable
            sequence.push_back(sequence[i-1] + sequence[i-2]);
        }
    }
    
    return sequence;
}

int main() {
    int n = 2000000;
    
    auto start_time = high_resolution_clock::now();
    unsigned long long result = fibonacci(n);
    auto end_time = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end_time - start_time);
    double execution_time_μs = duration.count();
    
    string result_str = to_string(result);
    cout << "Execution time: " << fixed << execution_time_μs << " μs\n";
    return 0;
}