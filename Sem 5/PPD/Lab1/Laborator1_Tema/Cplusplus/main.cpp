#include <cassert>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#include <sys/resource.h>

#define NMAX 10007
#define MMAX 10007
#define nMAX 5
#define mMAX 5
using namespace std;

int matrix[NMAX][MMAX] = {};
int result[NMAX][MMAX] = {};
int result2[NMAX][MMAX] = {};
int conv[nMAX][mMAX] = {};
int N, M, n, m, p;

void initMatrix(int matrix[NMAX][MMAX], const int iStart, const int iFinal, const int jStart, const int jFinal, ifstream& f) {
    for (int i = iStart; i <= iFinal; i++) {
        for (int j = jStart; j <= jFinal; j++) {
            f >> matrix[i][j];
        }
    }
}

void initConv(int matrix[nMAX][mMAX], const int iStart, const int iFinal, const int jStart, const int jFinal, ifstream& f) {
    for (int i = iStart; i <= iFinal; i++) {
        for (int j = jStart; j <= jFinal; j++) {
            f >> matrix[i][j];
        }
    }
}

void border(int matrix[NMAX][MMAX], const int N, const int n, const int M, const int m) {
    for (int j = (m - 1) / 2; j <= M + (m - 1) / 2; j++) {
        matrix[(n - 1) / 2 - 1][j] = matrix[(n - 1) / 2][j];
        matrix[(n - 1) / 2 + N][j] = matrix[(n - 1) / 2 + N - 1][j];
    }

    for (int i = (n - 1) / 2; i <= N + (n - 1) / 2; i++) {
        matrix[i][(m - 1) / 2 - 1] = matrix[i][(m - 1) / 2];
        matrix[i][(m - 1) / 2 + M] = matrix[i][(m - 1) / 2 + M - 1];
    }

    matrix[(n - 1) / 2 - 1][(m - 1) / 2 - 1] = matrix[(n - 1) / 2][(m - 1) / 2];
    matrix[(n - 1) / 2 + N][(m - 1) / 2 + M] = matrix[N + (n - 1) / 2 - 1][M + (m - 1) / 2 - 1];
    matrix[(n - 1) / 2 - 1][(m - 1) / 2 + M] = matrix[(n - 1) / 2][(m - 1) / 2 + M - 1];
    matrix[(n - 1) / 2 + N][(m - 1) / 2 - 1] = matrix[(n - 1) / 2 + N - 1][(m - 1) / 2];
}

void operation(int matrix[NMAX][MMAX], int conv[nMAX][mMAX], int result[NMAX][MMAX], const int i, const int j, const int n, const int m) {
    result[i - (n - 1) / 2][j - (m - 1) / 2] = 0;
    for (int l = i - (n - 1) / 2, t = 0; l <= i + (n - 1) / 2; l++, t++) {
        for (int c = j - (m - 1) / 2, q = 0; c <= j + (m - 1) / 2; c++, q++) {
            result[i - (n - 1) / 2][j - (m - 1) / 2] += matrix[l][c] * conv[t][q];
        }
    }
}

void sequential(int matrix[NMAX][MMAX], int conv[nMAX][mMAX], int result[NMAX][MMAX], const int n, const int m, const int N, const int M) {
    for (int i = (n - 1) / 2; i <= N + (n - 1) / 2 - 1; i++) {
        for (int j = (m - 1) / 2; j <= M + (m - 1) / 2 - 1; j++) {
            operation(matrix, conv, result, i, j, n, m);
        }
    }
}

void liniar(int matrix[NMAX][MMAX], int conv[nMAX][mMAX], int result[NMAX][MMAX], const int n, const int m, const int N, const int M, int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = (m - 1) / 2; j <= M + (m - 1) / 2 - 1; j++) {
            operation(matrix, conv, result, i, j, n, m);
        }
    }
}

void coloana(int matrix[NMAX][MMAX], int conv[nMAX][mMAX], int result[NMAX][MMAX], const int n, const int m, const int N, const int M, int start, int end) {
    for (int j = start; j < end; j++) {
        for (int i = (n - 1) / 2; i <= N + (n - 1) / 2 - 1; i++) {
            operation(matrix, conv, result, i, j, n, m);
        }
    }
}

void bloc(int matrix[NMAX][MMAX], int conv[nMAX][mMAX], int result[NMAX][MMAX], const int n, const int m, const int N,
    const int M, int startI, int endI, int startJ, int endJ) {
    for (int i = startI; i < endI; i++) {
        for (int j = startJ; j < endJ; j++) {
            operation(matrix, conv, result, i, j, n, m);
        }
    }
}


bool comp(int N, int M, int n, int m) {
    for (int i = (n - 1) / 2; i <= (n - 1) / 2 + N - 1; i++) {
        for (int j = (m - 1) / 2; j <= (m - 1) / 2 + M - 1; j++) {
            if (result[i][j] != result2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    srand(time(nullptr));
    string pathInput = argv[1];
    string pathOutput = argv[2];

    ifstream f(pathInput);
    if (!f.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    ofstream output(pathOutput, ios::app);


    f >> N >> M >> n >> m;
    p = stoi(argv[3]);



    initMatrix(matrix, (n - 1) / 2, (n - 1) / 2 + N - 1, (m - 1) / 2, (m - 1) / 2 + M - 1, f);
    initConv(conv, 0, n - 1, 0, m - 1, f);

    border(matrix, N, n, M, m);
    auto t_start = std::chrono::high_resolution_clock::now();
    sequential(matrix, conv, result, n, m, N, M);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end-t_start).count();
    std::cout << elapsed_time_ms << "\n";
    output << "static " << N << " " << M << " " << n << " " << m << " " << p << " secvential C++ " << elapsed_time_ms << endl;

    t_start = std::chrono::high_resolution_clock::now();
    int start = 0, end = N / p, rest = N % p;
    vector<thread> threads(p);
    for (int i = 0; i < p; i++) {
        if (rest) {
            end++;
            rest--;
        }
        threads[i] = thread(liniar, ref(matrix), ref(conv), ref(result2), n, m, N, M, start + (n - 1) / 2, end + (n - 1) / 2);
        start = end;
        end = start + N / p;
    }
    for (int i = 0; i < p; i++) {
        if (threads[i].joinable())
            threads[i].join();
    }
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end-t_start).count();
    std::cout << elapsed_time_ms << "\n";
    output << "static "<< N << " " << M << " " << n << " " << m << " " << p <<  " linie C++ " << elapsed_time_ms << endl;
    assert(comp(N, M, n, m) == true);


    t_start = std::chrono::high_resolution_clock::now();
    start = 0, end = M / p, rest = M % p;
    for (int i = 0; i < p; i++) {
        if (rest) {
            end++;
            rest--;
        }
        threads[i] = thread(coloana, ref(matrix), ref(conv), ref(result2), n, m, N, M, start + (m - 1) / 2, end + (m - 1) / 2);
        start = end;
        end = start + M / p;
    }
    for (int i = 0; i < p; i++) {
        if (threads[i].joinable())
            threads[i].join();
    }
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end-t_start).count();
    std::cout << elapsed_time_ms << "\n";
    output << "static " << N << " " << M << " " << n << " " << m  << " " << p <<   " coloane C++ " << elapsed_time_ms << endl;
    assert(comp(N, M, n, m) == true);


    t_start = std::chrono::high_resolution_clock::now();
    int startI = 0, startJ = 0, endI = N / p, endJ = M / p, restI = N % p, restJ = M % p;
    for (int i = 0; i < p; i++) {
        if (restI) {
            endI++;
            restI--;
        }
        if (restJ) {
            endJ++;
            restJ--;
        }
        threads[i] = thread(bloc, ref(matrix), ref(conv), ref(result2), n, m, N, M, startI + (n - 1) / 2, endI + (n - 1) / 2,
            startJ + (m - 1) / 2, endJ + (m - 1) / 2);
        startI = endI;
        endI = startI + N / p;
        startJ = endJ;
        endJ = startJ + M / p;
    }
    for (int i = 0; i < p; i++) {
        if (threads[i].joinable())
            threads[i].join();
    }
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end-t_start).count();
    std::cout << elapsed_time_ms << "\n";
    output << "static " << N << " " << M << " " << n << " " << m << " " << p <<  " bloc C++ " << elapsed_time_ms << endl;
    assert(comp(N, M, n, m) == true);



    f.close();
    output.close();

    return 0;
}
