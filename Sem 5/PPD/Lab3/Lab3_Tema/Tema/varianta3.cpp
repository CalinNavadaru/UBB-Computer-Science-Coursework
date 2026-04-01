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
        outputFile << "Varianta 1 cu " << N1 << " " << N2 << " " << elapsed_time_ms << "\n";
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
    n1.resize(N1);
    n2.resize(N2);
    result.resize(max(N1, N2) + 1);

    vector<int> aux1, aux2;
    int start, end;
    MPI_Status status;
    MPI_Request request, req, req1;;
    int p = world_size - 1;
    vector<MPI_Request> requests(world_size - 1), requests_t(world_size - 1);
    if (world_rank == 0) {
        int step = max(N1, N2) / p, rest = max(N1, N2) % p;
        int t = 0;
        start = 0, end = step;
        for (int i = 1; i < world_size; i++) {
            if (rest) {
                end++;
                rest--;
            }
            int x, y;
            aux1.clear();
            aux2.clear();
            for (int j = start; j < end; j++) {
                if (f >> x) {
                    aux1.push_back(x);
                } else {
                    aux1.push_back(0);
                }

                if (f2 >> y) {
                    aux2.push_back(y);
                } else {
                    aux2.push_back(0);
                }
            }
            MPI_Isend(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(aux1.data(), end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(aux2.data(), end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &request);
            start = end;
            end += step;
        }
        step = max(N1, N2) / p, rest = max(N1, N2) % p;
        start = 0, end = step;
        for (int i = 1; i < world_size; i++) {
            if (rest) {
                end++;
                rest--;
            }
            MPI_Irecv(result.data() + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &requests[i - 1]);
            start = end;
            end += step;
        }
        MPI_Waitall(static_cast<int>(requests.size()), requests.data(), &status);
        for (int i = 1; i <= world_size - 1; i++) {
            MPI_Irecv(&t, 1,MPI_INT, world_size - 1, world_size - 1, MPI_COMM_WORLD, &requests_t[i - 1]);
        }
        MPI_Waitall(static_cast<int>(requests_t.size()), requests_t.data(), &status);
        if (t) {
            result.back() = t;
        } else {
            result.pop_back();
        }
        auto t_end = std::chrono::high_resolution_clock::now();
        auto elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
        assert(result_seq == result);
        outputFile << "Varianta 1 MPI cu " << N1 << " " << N2 << " " << p << " procese a luat " << elapsed_time_ms <<
                "\n";
    } else {
        int index = 1;
        MPI_Irecv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);
        MPI_Irecv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &req1);
        aux1.clear();
        aux2.clear();
        MPI_Wait(&req, &status);
        MPI_Wait(&req1, &status);
        aux1.resize(end - start);
        aux2.resize(end - start);
        MPI_Irecv(aux1.data(), end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);
        MPI_Irecv(aux2.data(), end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &req1);
        int t = 0, t_prec = 0, l = end - start;
        vector<int> res;
        MPI_Wait(&req, &status);
        MPI_Wait(&req1, &status);
        for (int i = 0; i < l; i++) {
            auto v = aux1.at(i) + aux2.at(i) + t;
            res.push_back(v % 10);
            t = v / 10;
        }
        if (world_rank != 1) {
            for (int i = 1; i <= world_rank - 1; i++) {
                MPI_Irecv(&t_prec, 1, MPI_INT, world_rank - 1, i, MPI_COMM_WORLD, &request);
                requests.push_back(request);
            }
            for (auto& request_transport : requests) {
                cout << "TEST" << endl;
                MPI_Wait(&request_transport, &status);
                cout << world_rank << ' ' << t_prec << endl;
                if (t_prec) {
                    for (int i = 0; i < l; i++) {
                        auto v = res.at(i) + t_prec;
                        res.at(i) = v % 10;
                        t_prec = v / 10;
                        if (!t_prec)
                            break;
                    }
                    cout << world_rank << ' ';
                    for (auto v: res) {
                        cout << v << ' ';
                    }
                    cout << endl;
                }
                if (t_prec) {
                    t = t_prec;
                }
                if (world_rank == p) {
                    MPI_Isend(&t, 1, MPI_INT, 0, index, MPI_COMM_WORLD, &request);
                    cout << "TRimit la sursa" << world_rank << " transport cu index-ul " << index << endl;
                } else {
                    MPI_Isend(&t, 1, MPI_INT, world_rank + 1, index, MPI_COMM_WORLD, &request);
                    cout << "TRimit " << world_rank << " transport cu index-ul " << index << endl;
                }
                index += 1;
            }
        }
        else {
            MPI_Isend(&t, 1, MPI_INT, world_rank + 1, index, MPI_COMM_WORLD, &request);
        }
        MPI_Isend(res.data(), end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    }
    MPI_Finalize();
    return 0;
}
