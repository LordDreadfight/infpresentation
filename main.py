import time
import sys

sys.set_int_max_str_digits(1000000000)  # Increase the limit to handle large numbers

def fibonacci(n):
    if n <= 0:
        return int(0)
    elif n == 1:
        return int(1)
    
    a, b = int(0), int(1)
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b

def main():
    n = 2000000
    
    start_time = time.time()
    result = fibonacci(n)
    end_time = time.time()
    
    execution_time_ms = (end_time - start_time) * 1000
    
    print(f"Fibonacci number at position {n}: {len(str(result))}")
    print(f"Execution time: {execution_time_ms:.2f} ms")

if __name__ == "__main__":
    main()
