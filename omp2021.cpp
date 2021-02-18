#include <iostream>
#include <omp.h>
using namespace std;

void avg_reduction();
void compare_cases();
void integral_reduction();


double G = 2.1;

int main()
{
    #pragma omp parallel
    {
        int thread_ID = omp_get_thread_num();
        cout << thread_ID << endl;
    }

    cout << "begin of the loop" << endl;
    #pragma omp parallel for
    for(int i=0;i<12;i++)
    {
        cout << i;
    }
    cout << endl;
    cout << "end of the loop" << endl;
    avg_reduction();
    compare_cases();
    integral_reduction();

    int i, N = 10;

    #pragma omp parallel for num_threads(2) schedule(static)
    for (i = 0; i < N; i++)
    {
        if (omp_get_thread_num() == 0)
        printf("Thread %d is doing iteration %d.\n", omp_get_thread_num( ), i);
    }
//    Thread 0 is doing iteration 0.
//    Thread 0 is doing iteration 1.
//    Thread 0 is doing iteration 2.
//    Thread 0 is doing iteration 3.
//    Thread 0 is doing iteration 4.
    return 0;
}


void avg_reduction()
{
    int N = 600000000;
    int j = 0;
    double tavg=0.0;

    double time_start = omp_get_wtime();
    omp_set_num_threads(4);

    #pragma omp parallel for reduction(+:tavg)
    for(j=0;j<N;j++)
    {
        tavg += j;
    }

    double time_elapsed = omp_get_wtime() - time_start;
    tavg = tavg / N;
    cout << tavg << "took" << time_elapsed << endl;
}


void compare_cases()
{
    int a=1, b=2, c=3, t=4;
    omp_set_num_threads(3);
    #pragma omp parallel private(a), firstprivate(b)
    {
        // a will be private and, but not be initialized
        // b will be private and initialized
        // c will be shared;
        // t will be local; that is it is private.
        int t = 5;

        static int s = 8; // will be shared.
        if (omp_get_thread_num() == 0)
            s = 2;//here is different from the below results

        printf("thread id: %d, a: %d, b: %d, c: %d, t: %d, s: %d, G: %f, \n", omp_get_thread_num(), a, b, c, t, s, G);
        a = 21;
        b = 22;
        c = 23;
        t = 24;
    }
    //out of the parallel region 
    printf("\nout of the parallel region\n");
    printf("thread id: %d, a: %d, b: %d, c: %d, t: %d, G: %f, \n", omp_get_thread_num(), a, b, c, t, G);

//    OUTPUT:
//    thread id: 0, a: 0, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//    thread id: 2, a: 32752, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//    thread id: 1, a: 32767, b: 2, c: 3, t: 5, s: 2, G: 2.100000,
//
//    out of the parallel region
//    thread id: 0, a: 1, b: 2, c: 23, t: 4, G: 2.100000,
}


void integral_reduction()
{
    int NTHREADS = 4;
    long num_steps = 100000000;
    double step = 0;
    double pi = 0.0;
    double sum = 0;
    int i = 0;

    step = 1.0 / (double) num_steps;

    omp_set_num_threads(NTHREADS);
    double timer_start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < num_steps; ++i) {
        double x = (i+0.5) * step;
        sum += 4.0 / (1.0 + x*x);
    }

    pi = sum * step;

    double timer_took = omp_get_wtime() - timer_start;
    cout << pi << " took " << timer_took << endl;
    // 1 threads  --> 0.55 seconds.
    // 4 threads  --> 0.24 seconds.
    // 24 threads --> 0.24 seconds.
    // 48 threads --> 0.23 seconds.
}









