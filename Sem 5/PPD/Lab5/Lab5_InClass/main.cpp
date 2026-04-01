#include <iostream>
#include <omp.h>

using namespace std;

const int MAX = 20;
int a[MAX], b[MAX], m[MAX][MAX], c[MAX];

int produsScalar(int a[MAX], int b[MAX])
{
    int s = 0;

    for (int i = 0; i < MAX; i++)
    {
        s += a[i] * b[i];
    }

    return s;
}

int produsScalarParallel(int a[MAX], int b[MAX])
{
    int sum = 0;
    int partial_sum = 0;

#pragma omp parallel firstprivate(partial_sum) num_threads(16)
    // de fiecare data cand avem ceva paralel, se defineste parallel
    // public este prin referinta si este varianta default
    // private este copie locala
    // firstprivate salveaza valoarea daca este initializat
    // lessprivate salveaza ultima valoare (valoarea din ultimul thread care si-a terminat executia)
    {
#pragma omp for
        for (int i = 0; i < MAX; i++)
        {
            partial_sum += a[i] * b[i];
        }

#pragma omp critical
        {
            sum += partial_sum;
        }
    }

    return sum;
}

int produsScalarParallel2(int a[MAX], int b[MAX])
{
    int sum = 0;

#pragma omp parallel for reduction(+:sum)
    // reducere
    // fiecare primeste un firstprivate si aplica operatia
    // la final se aduna rezultatele
    for (int i = 0; i < MAX; i++)
    {
        sum += a[i] * b[i];
    }

    return sum;
}

void addVectors(int a[MAX], int b[MAX], int c[MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        c[i] = a[i] + b[i];
    }
}

void multiplyVectors(int a[MAX], int b[MAX], int c[MAX])
{
    for (int i = 0; i < MAX; i++)
    {
        c[i] = a[i] * b[i];
    }
}

int main()
{
    //     // Seteaza numarul de thread-uri (p-ul din celelalte lab-uri), seteaza numarul default
    //     omp_set_num_threads(4);
    //
    //     cout << "Thread num1: " << omp_get_num_threads() << endl;
    //
    // #pragma omp parallel num_threads(16) // care paralelizeaza un body de cod
    //     {
    //         cout << "Thread num2: " << omp_get_num_threads() << endl;
    //
    // #pragma omp critical // mutex
    //         {
    //             cout << "Hello from: " << omp_get_thread_num() << endl;
    //             cout << "Thread num3: " << omp_get_num_threads() << endl;
    //         }
    //
    //         cout << "Thread num4: " << omp_get_num_threads() << endl;
    //
    // #pragma omp for schedule(static, 2) nowait
    //         // nowait, ignora bariera default
    //         // pragma pentru fiecare for
    //         for (int i = 0; i < MAX; i++) {
    //             a[i] = omp_get_thread_num();
    //             b[i] = i;
    //         }
    //
    // #pragma omp for schedule(static, 2) collapse(2)
    //         // ia cate for-uri ii dai si le linearizeaza
    //         for (int i = 0; i < MAX; i++) {
    //             for (int j = 0; j < MAX; j++) {
    //                 m[i][j] = omp_get_thread_num();
    //             }
    //         }
    //     }
    //
    //     for (int i = 0; i < MAX; i++) {
    //         cout << a[i] << " ";
    //     }
    //
    //     cout << endl;
    //
    //     for (int i = 0; i < MAX; i++) {
    //         for (int j = 0; j < MAX; j++) {
    //             cout << m[i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    //
    //     cout << produsScalar(a, b) << endl;
    //     cout << produsScalarParallel(a, b) << endl;
    //     cout << produsScalarParallel2(a, b) << endl;
    //
    // #pragma omp parallel num_threads(8)
    //     {
    // #pragma omp sections
    //         /// mai mute sectiuni
    //         {
    // #pragma omp section // un section == un thread
    //             {
    //                 addVectors(a, b, c);
    // #pragma omp critical
    //                 {
    //                     cout << "Section add: " << omp_get_thread_num() << endl;
    //                 }
    //             }
    // #pragma omp section
    //             {
    //                 multiplyVectors(a, b, c);
    // #pragma omp critical
    //                 {
    //                     cout << "Section multiply: " << omp_get_thread_num() << endl;
    //                 }
    //             }
    // #pragma omp section
    //             {
    //                 produsScalar(a, b);
    // #pragma omp critical
    //                 {
    //                     cout << "Section produs: " << omp_get_thread_num() << endl;
    //                 }
    //             }
    //         }
    //     }
    //
    // #pragma omp single
    //     /// doar un thread poate rula (gen numai el va executa acest cod si altele nu pot)
    //     {
    //         cout << "Doar eu execut: " << omp_get_thread_num() << endl;
    //     }

    // Setăm numărul de thread-uri la 4
    omp_set_num_threads(3);

    // Regiune paralelă
#pragma omp parallel
    {
        // Preluăm ID-ul thread-ului curent
        int id = omp_get_thread_num();
        printf("Hello from thread %d\n", id);
    }

    return 0;
}
