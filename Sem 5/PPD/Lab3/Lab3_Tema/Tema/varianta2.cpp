#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <mpi.h>


using namespace std;

void read_data(vector<int> &n1, vector<int> &n2, vector<int> &n3, int &N1, int &N2, ifstream &f,
               ifstream &f2) {
    f >> N1;
    f2 >> N2;
    n3.clear();
    n1.clear();
    for (int i = 0; i < N1; i++) {
        int x;
        f >> x;
        n1.push_back(x);
    }
    n2.clear();
    for (int i = 0; i < N2; i++) {
        int x;
        f2 >> x;
        n2.push_back(x);
    }
    if (n1.size() > n2.size()) {
        const unsigned int n1_size = n1.size();
        for (unsigned int i = n2.size(); i < n1_size; i++) {
            n2.push_back(0);
        }
    } else if (n2.size() > n1.size()) {
        const unsigned int n2_size = n2.size();
        for (unsigned int i = n1.size(); i < n2_size; i++) {
            n1.push_back(0);
        }
    }
}

void seq(const vector<int> &n1, const vector<int> &n2, vector<int> &result) {
    int t = 0;
    const unsigned int size = n1.size();
    for (unsigned int i = 0; i < size; i++) {
        const auto value = n1.at(i) + n2.at(i) + t;
        auto rest = value % 10;
        t = value / 10;
        result.push_back(rest);
    }
    if (t) {
        result.push_back(t);
    }
}

int operation(const vector<int> &n1, const vector<int> &n2, vector<int> &result) {
    int t = 0;
    const unsigned int size = n1.size();
    for (unsigned int i = 0; i < size; i++) {
        const auto value = n1.at(i) + n2.at(i) + t;
        auto rest = value % 10;
        t = value / 10;
        result.push_back(rest);
    }
    return t;
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    vector<int> n1;
    vector<int> n2;
    vector<int> result;
    vector<int> result_seq;

    int N1, N2;
    ifstream f(argv[1]), f2(argv[2]);
    ofstream outputFile(argv[3], ios::app);
    if (!f.is_open() || !f2.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }
    if (!outputFile.is_open()) {
        cerr << "Failed to open output file." << endl;
        return 1;
    }

    if (world_rank == 0) {
        auto t_start = std::chrono::high_resolution_clock::now();
        read_data(n1, n2, result, N1, N2, f, f2);
        seq(n1, n2, result);
        auto t_end = std::chrono::high_resolution_clock::now();
        auto elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
        result_seq = result;
        outputFile << "Varianta 2 cu " << N1 << " " << N2 << " " << elapsed_time_ms << "\n";
    }
    f.clear();
    f2.clear();
    n1.clear();
    n2.clear();
    result.clear();
    f.seekg(0, ios::beg);
    f2.seekg(0, ios::beg);

    auto t_start = std::chrono::high_resolution_clock::now();
    f >> N1;
    f2 >> N2;
    int t;
    int p = world_size - 1;
    int n = max(N1, N2);
    int l = n + (p - n % p);
    int chunk_size = l / p;
    n1.resize(l, 0);
    n2.resize(l, 0);
    result.resize(l + 1, 0);
    MPI_Status status;
    vector<int> aux1(chunk_size, 0), aux2(chunk_size, 0), res(chunk_size, 0), displacement(p + 1, 0);
    vector<int> send_counts(world_size, chunk_size);
    vector<int> recv_counts(world_size, chunk_size);
    if (world_rank == 0) {
        int x;
        for (int j = 0; j < l; j++) {
            if (f >> x) {
                n1[j] = x;
            } else {
                n1[j] = 0;
            }
            if (f2 >> x) {
                n2[j] = x;
            } else {
                n2[j] = 0;
            }
        }
        displacement[0] = 0;
        send_counts[0] = 0;
        recv_counts[0] = 0;
        for (int i = 1; i < displacement.size(); i++) {
            displacement[i] = displacement[i - 1] + send_counts[i - 1];
        }
    }
    MPI_Scatterv(n1.data(), send_counts.data(), displacement.data(), MPI_INT, aux1.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatterv(n2.data(), send_counts.data(), displacement.data(), MPI_INT, aux2.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);
    if (world_rank != 0) {
        t = 0;
        int t_prec = 0;
        l = chunk_size;

        for (int i = 0; i < l; i++) {
            auto v = aux1.at(i) + aux2.at(i) + t;
            res[i] = (v % 10);
            t = v / 10;
        }
        if (world_rank != 1) {
            MPI_Recv(&t_prec, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, &status);
        }
        if (t_prec) {
            for (int i = 0; i < l; i++) {
                auto v = res.at(i) + t_prec;
                res.at(i) = v % 10;
                t_prec = v / 10;
                if (!t_prec)
                    break;
            }
        }
        if (t_prec) {
            t = t_prec;
        }
        if (world_rank == p) {
            MPI_Send(&t, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } else {
            MPI_Send(&t, 1, MPI_INT, world_rank + 1, 0, MPI_COMM_WORLD);
        }
    }
    MPI_Gatherv(res.data(), chunk_size, MPI_INT, result.data(), recv_counts.data(), displacement.data(), MPI_INT, 0, MPI_COMM_WORLD);
    if (world_rank == 0) {
        MPI_Recv(&t, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, &status);
        if (t) {
            result.back() = t;
        } else {
            result.pop_back();
        }
        while (result.back() == 0) {
            result.pop_back();
        }
        auto t_end = std::chrono::high_resolution_clock::now();
        auto elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
        cout << endl << elapsed_time_ms << "\n";
        assert(result_seq == result);
        outputFile << "Varianta 2 MPI cu " << N1 << " " << N2 << " " << p << " procese a luat " << elapsed_time_ms << "\n";
    }
    MPI_Finalize();
    return 0;
}
