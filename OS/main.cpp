#include <stdio.h>
#include <pthread.h>
#include <random>
#include <math.h>
#include <iostream>

/*struct thread_args {
    double **a;
    double *b;
    int size;
    int thread_no;
    int threads_count;
};*/
 /*struct thread_args {
    double **a;
    double **b;
    double **c;
    int size;
    int thread_id;
    int threads_count;
};

void* calculate(void *_args) {
    thread_args *args = (struct thread_args *) _args;
    double **a = args->a;
    double **b = args->b;
    int size = args->size;
    int thread_no = args->thread_no;
    int threads_count = args->threads_count;

    int count = 0;

    for (int i = 2; i < size - 2; i++) {
        for (int j = 2; j < size - 2; j++) {
            if (((size-4)*i + j - 2) % threads_count == thread_no) {
                b[count] = a[i+2][j] + a[i-2][j] + a[i][j+2] + a[i][j-2] - 4*a[i][j];
                count++;
            }
        }
    }
    thread_args *args = (struct thread_args *) _args;
    double **a = args->a;
    double **b = args->b;
    double **c = args->c;
    int size = args->size;
    int threads_count = args->threads_count;
    int thread_id = args->thread_id;
    printf("thread id = %d\n", thread_id);
    for(int i=0;i<size;i++){
        if(i%threads_count!=thread_id){
            continue;
        }
        for(int j=0;j<size;j++){
            c[i][j] = a[i][j]+b[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    int threads_count = atoi(argv[2]);
    int size = atoi(argv[1]);

    if (threads_count < size/2 ) {
        threads_count = size/2 + 1;
        printf("Not enough threads to calculate, number set to %d\n", threads_count);
    }

    double **b = new double*[threads_count];
    for(int i = 0; i < threads_count; i++){
        b[i] = new double[2*size];
    }


    double **a = new double*[size];
    for(int i = 0; i < size; i++){
        a[i] = new double[size];
    }

    std::default_random_engine gen(0);
    std::uniform_real_distribution<> dist(1, 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            a[i][j] = floor(dist(gen));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", a[i][j]);
        }
        printf("\n");
    }

    thread_args args = thread_args();
    args.a = a;
    args.threads_count = threads_count;
    args.size = size;

    pthread_t threads[threads_count];
    pthread_t id;
    for (int i = 0; i < threads_count; i++) {
        args.thread_no = i;
        args.b = b[i];
        pthread_create(&id, NULL, &calculate, &args);
        threads[i] = id;
    }

    void* res;

    for(int i = 0; i < threads_count; i++){
        pthread_join(threads[i], &res);
    }

    for(int i = 2; i < size -2; i++){
        for(int j = 2 ;j < size - 2; j++){
            a[i][j] = b[j-2][i-2];
        }
    }

    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", a[i][j]);
        }
        printf("\n");
    }
    return 0;
   int threads_count = 10 ;//atoi(argv[2]);
    int size = 5; //atoi(argv[1]);


    double **c = new double*[size];
    for(int i = 0; i < size; i++){
        c[i] = new double[size];
    }
    double **b = new double*[size];
    for(int i = 0; i < size; i++){
        b[i] = new double[size];
    }


    double **a = new double*[size];
    for(int i = 0; i < size; i++){
        a[i] = new double[size];
    }

    std::default_random_engine gen(0);
    std::uniform_real_distribution<> dist(1, 10);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            a[i][j] = floor(dist(gen));
            b[i][j] = floor(dist(gen));
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", b[i][j]);
        }
        printf("\n");
    }
    thread_args* arg = new thread_args[threads_count];
    pthread_t* threads = new pthread_t[threads_count];
    for (int i = 0; i < threads_count; i++) {
        arg[i].a = a;
        arg[i].b=b;
        arg[i].c = c;
        arg[i].threads_count = threads_count;
        arg[i].size = size;
        arg[i].thread_id = i;
        pthread_create(&threads[i], NULL, &calculate, &arg[i]);
    }

    void* res;

    for(int i = 0; i < threads_count; i++){
        pthread_join(threads[i], nullptr);
    }

   for(int i = 2; i < size -2; i++){
        for(int j = 2 ;j < size - 2; j++){
            a[i][j] = b[j-2][i-2];
        }
    }

    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}*/
#include <stdio.h>
#include <pthread.h>
#include <random>
#include <math.h>
#include <iostream>

struct thread_args {
    double **a;
    double **b;
    double **c;
    int size;
    int thread_id;
    int threads_count;

    thread_args() {

    }

    thread_args(double **a, double **b, double **c, int size, int thread_id, int thread_count) {
        this->a = a;
        this->b = b;
        this->c = c;
        this->size = size;
        this->thread_id = thread_id;
        this->threads_count = thread_count;
    }

};

void *calculate(void *_args) {
    auto *args = (struct thread_args *) _args;
    double **a = args->a;
    double **b = args->b;
    double **c = args->c;
    int size = args->size;
    int threads_count = args->threads_count;
    int thread_id = args->thread_id;

    printf("Thread = %d starts working\n", thread_id);
    for (int i = 0; i < size; i++) {
        if (i % threads_count != thread_id) {
            continue;
        }
        for (int j = 0; j < size; j++) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
    printf("Thread = %d stops working\n", thread_id);
}
void printMatrix(double **a, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%7.2f", a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main(int argc, char *argv[]) {

    int threads_count = 7;
    int size = 5;

    auto **c = new double *[size];
    for (int i = 0; i < size; i++) {
        c[i] = new double[size];
    }
    auto **b = new double *[size];
    for (int i = 0; i < size; i++) {
        b[i] = new double[size];
    }

    auto **a = new double *[size];
    for (int i = 0; i < size; i++) {
        a[i] = new double[size];
    }

    std::default_random_engine gen(0);
    std::uniform_real_distribution<> dist(1, 10);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            a[i][j] = floor(dist(gen));
            b[i][j] = floor(dist(gen));
        }
    }

    printMatrix(a,size);
    printMatrix(b,size);

    pthread_t threads[threads_count];
    thread_args args[threads_count];

    for (int i = 0; i < threads_count; i++) {
        pthread_t id;
        args[i] = thread_args(a, b, c, size, i, threads_count);
        pthread_create(&id, NULL, &calculate, &args[i]);
        threads[i] = id;
    }

    for (int i = 0; i < threads_count; i++) {
        pthread_join(threads[i], nullptr);
    }

    printMatrix(c,size);
    return 0;
}



