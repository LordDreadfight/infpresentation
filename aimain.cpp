#include <iostream>
#include <chrono>
#include <string>
#include <vector>
using namespace std;
using namespace std::chrono;

unsigned long long fibonacci(int n) {
    if (n <= 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    
    unsigned long long a = 0, b = 1;
    for (int i = 2; i <= n; i++) {
        unsigned long long temp = b;
        b = a + b;
        a = temp;
    }
    return b;
}

vector<unsigned long long> fibonacci_sequence(int n) {
    vector<unsigned long long> sequence;
    sequence.reserve(n + 1);
    
    for (int i = 0; i <= n; ++i) {
        sequence.push_back(fibonacci(i));
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
    cout << "Execution time: " << fixed << execution_time_μs << " μs" << endl;
    
    return 0;
}