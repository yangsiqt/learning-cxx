#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 如果已经缓存了足够的值，直接返回
        if (i < cached) {
            return cache[i];
        }
        
        // 计算并缓存从当前缓存位置到目标位置的所有值
        for (; cached <= i; ++cached) {
            if (cached == 0) {
                cache[0] = 0;  // fibonacci(0) = 0
            } else if (cached == 1) {
                cache[1] = 1;  // fibonacci(1) = 1
            } else {
                cache[cached] = cache[cached - 1] + cache[cached - 2];
            }
        }
        
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib{{0}, 0};  // 初始化cache数组为0，cached为0
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
