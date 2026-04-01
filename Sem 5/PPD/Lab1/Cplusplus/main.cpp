#include <iostream>
#include <vector>
#include <thread>
#include <cassert>

using namespace std;

int generateRandomNumber(int upperBoundary) {
    return rand() % upperBoundary + 1;
}

void printArray(vector<int> a, int n) {
    for (int i = 0; i < n; i ++)
        cout << a[i] << " ";
    cout << "\n";
}

int sum(int a, int b) {
    return a * b * a * b - a * b * b;
}

void seq(vector<int> &a, vector<int> &b, vector<int> &c, int n) {
    for(int i = 0; i < n; i++) {
        c[i] = sum(a[i], b[i]);
    }
}

void seq2(vector<int> &a, vector<int> &b, vector<int> &c, int start, int end) {
    for(int i = start; i < end; i++) {
        c[i] = sum(a[i], b[i]);
    }
}

int main() {
    auto t_start = std::chrono::high_resolution_clock::now();
    srand(time(nullptr));
    vector<int> a, b, c, cParalel;
    int n = 100000, upperBoundary = 10000000;

    for (int i = 0; i < n; i++) {
        a.push_back(generateRandomNumber(upperBoundary));
        b.push_back(generateRandomNumber(upperBoundary));
        c.push_back(0);
        cParalel.push_back(0);
    }
    seq(a, b, c, n);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout << elapsed_time_ms << "\n";

    t_start = std::chrono::high_resolution_clock::now();

    int p = 4;
    int start = 0, end = n / p, rest = n % p;
    vector<thread> threads(p);
    for (int i = 0; i < p; i++) {
        if (rest) {
            end++;
            rest--;
        }
        threads[i] = thread(seq2, ref(a), ref(b), ref(cParalel), start, end);
        start = end;
        end = start + n / p;
    }

    for (int i = 0; i < p; i++) {
        if (threads[i].joinable())
            threads[i].join();
    }
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    std::cout << elapsed_time_ms << "\n";
    assert(c == cParalel);
    return 0;
}

