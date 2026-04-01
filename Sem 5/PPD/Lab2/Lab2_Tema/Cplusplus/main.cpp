#include <barrier>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#define NMAX 10007
#define MMAX 10007
#define nMAX 3
#define mMAX 3
#define MaxP 32
using namespace std;

vector<vector<int> > matrix(NMAX, vector<int>(MMAX, 0));
vector<vector<int> > result_seq(NMAX, vector<int>(MMAX, 0));
vector<vector<int> > conv(nMAX, vector<int>(mMAX, 1));
int N, M, n, m, p;


void initMatrix(const int iStart, const int iFinal, const int jStart, const int jFinal,
                ifstream &f) {
    for (int i = iStart; i <= iFinal; i++) {
        for (int j = jStart; j <= jFinal; j++) {
            f >> matrix[i][j];
        }
    }
}

void initConv(const int iStart, const int iFinal, const int jStart, const int jFinal,
              ifstream &f) {
    for (int i = iStart; i <= iFinal; i++) {
        for (int j = jStart; j <= jFinal; j++) {
            f >> conv[i][j];
        }
    }
}

void border(const int N, const int n, const int M, const int m) {
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

vector<int> operation(const vector<int> &before, const vector<int> &line, const vector<int> &after,
                      const vector<vector<int> > &conv) {
    vector<int> aux(NMAX, 0);


    aux[(m - 1) / 2 - 1] = line[(m - 1) / 2 - 1];
    aux[M + (m - 1) / 2] = line[M + (m - 1) / 2];


    for (int j = (m - 1) / 2; j <= M + (m - 1) / 2 - 1; j++) {
        aux[j] = 0;
        for (int q = 0; q < 3; q++) {
            aux[j] += before[j + q - 1] * conv[0][q] + line[j + q - 1] * conv[1][q] + after[j + q - 1] * conv[2][q];
        }
    }

    return aux;
}

void thread_f(int startI, int endI, barrier<> &b) {
    if (startI > N) {
        b.arrive_and_wait();
        return;
    }
    vector<int> b2(NMAX, 0);
    vector<int> before = matrix[startI - 1];
    vector<int> after = matrix[endI];
    b.arrive_and_wait();
    if (endI == startI + 1) {
        matrix[startI] = operation(before, matrix[startI], after, conv);
        return;
    }
    vector<int> buffer_before = operation(before, matrix[startI], matrix[startI + 1], conv);
    vector<int> buffer_after = operation(matrix[endI - 2], matrix[endI - 1], after, conv);
    vector<int> line = matrix[startI];
    int i;
    vector<int> b1 = buffer_before;
    for (i = startI + 1; i < endI - 1; i++) {
        before = line;
        line = matrix[i];
        b2 = operation(before, line, matrix[i + 1], conv);
        matrix[i - 1] = b1;
        b1 = b2;
    }
    matrix[endI - 2] = b1;
    matrix[startI] = buffer_before;
    matrix[endI - 1] = buffer_after;
}

void seq() {
    vector<int> buffer = operation(matrix[(n - 1) / 2 - 1], matrix[(n - 1) / 2], matrix[(n - 1) / 2 + 1], conv);

    vector<int> buffer2;
    int i;
    for (i = (n - 1) / 2 + 1; i <= N + (n - 1) / 2 - 1; i++) {
        buffer2 = operation(matrix[i - 1], matrix[i], matrix[i + 1], conv);
        matrix[i - 1] = buffer;
        buffer = buffer2;
    }

    matrix[i - 1] = buffer;
}


int main(int argc, char **argv) {
    srand(time(nullptr));
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return 1;
    }


    string pathInput = argv[1];
    string pathOutput = argv[2];



    ifstream f(pathInput);
    if (!f.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    ofstream output(pathOutput, ios::app);
    if (!output.is_open()) {
        cerr << "Failed to open output file." << endl;
        return 1;
    }

    f >> N >> M >> n >> m;
    p = stoi(argv[3]);
    cout << pathInput << " " << p << '\n';
    barrier b(p);

    initMatrix((n - 1) / 2, (n - 1) / 2 + N - 1, (m - 1) / 2, (m - 1) / 2 + M - 1, f);
    initConv(0, n - 1, 0, m - 1, f);
    border(N, n, M, m);

    auto t_start = std::chrono::high_resolution_clock::now();
    seq();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << elapsed_time_ms << "\n";
    output << N << " " << M << " " << "Secvential a facut " << elapsed_time_ms << "\n";
    result_seq = matrix;

    f.clear();
    f.seekg(0, ios::beg);
    f >> N >> M >> n >> m;
    initMatrix((n - 1) / 2, (n - 1) / 2 + N - 1, (m - 1) / 2, (m - 1) / 2 + M - 1, f);
    initConv(0, n - 1, 0, m - 1, f);
    border(N, n, M, m);

    t_start = std::chrono::high_resolution_clock::now();
    int start = 0, end = N / p, rest = N % p;
    vector<thread> threads(p);
    for (int i = 0; i < p; i++) {
        if (rest) {
            end++;
            rest--;
        }
        threads[i] = thread(thread_f, start + (n - 1) / 2, end + (n - 1) / 2, ref(b));
        start = end;
        end = end + N / p;
    }
    for (auto& t : threads) {
        t.join();
    }
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    output << N << " " << M << " " << "C++ dinamic cu " << p << " thread-uri a facut " << elapsed_time_ms << "\n";
    assert(matrix == result_seq);
    return 0;
}
