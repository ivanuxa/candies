#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#define ull unsigned long long
#define ll long long

struct Pair {
    ull count;
    ull next;
};

#define MAX_SIZE 1'000'000
static ull A[MAX_SIZE]; // 8 MB
static double counts[MAX_SIZE]; // 8 MB

static std::unordered_map<ull, Pair> mapa;

double mean(int N) {
    double sum = 0ull;
    for (int i = 0; i < N; ++i)
        sum += A[i];
    return sum  / N;
}

int count(int N, double mean) {
    int count = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (A[i] > mean)
            ++count;
        else break;
    }
    return count;
}

int main() {
    int N;
    std::cin >> N;
    bool repeated = true;
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i];
    }
    
    std::sort(A, A + N); // NlogN or N2

    for (int i = 0; i < N; ++i) {
        if (mapa.find(A[i]) == mapa.end()) {
            mapa[A[i]] = Pair{1, (i + 1 < N) ? A[i + 1] : 0};
        }
        else {
            ++(mapa[A[i]].count);
            mapa[A[i]].next = (i + 1 < N) ? A[i + 1] : 0;
        }
    }

    // for (auto item : mapa) {
    //     std::cout << "Key: " << item.first << ", Value: { Count: " << item.second.count << ", Next: " << item.second.next << "}\n";
    // }

    if (A[0] == A[N - 1]) {
        std::cout << 0;
        return 0;
    }

    counts[0] = 0;
    double m = A[0];
    ull idx = A[0];
    for (int i = 1; i < N; ++i) {
        const double low = std::ceil(m);
        ull j = low;
        const ull next = mapa[idx].next;
        m = (A[i] + m * i) / (i + 1);
        const double high = std::floor(m);
        counts[i] = counts[i - 1];
        while (j <= high && next != 0) {
            if (j < next) {
                idx = mapa[idx].next;
                j = idx;
                continue;
            }
            counts[i] -= mapa[idx].count;
            idx = mapa[idx].next;
            j = idx;
        }
        counts[i] += A[i] > m ? 1 : 0;
    }

    for (int i = 0; i < N; ++i) {
        std::cout << counts[i] << " ";
    }


    // int max = 0;
    // while (N > 0) {
    //     if (max == N - 1)
    //         break;
    //     int c = count(N, m);
    //     if (c > max)
    //         max = c;
    //     N -= 1;
    // }

    // std::cout << max;
}