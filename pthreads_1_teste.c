#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int m, n; // Supondo que m e n sejam variáveis globais.
double **A; // Matriz A[m][n].
double *x, *y; // Vetores x[n] e y[m].

int thread_count; // Número de threads.

void *Pth_mat_vect(void *rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0.0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    pthread_exit(NULL);
}

int main() {
    // Inicialização de m, n e thread_count.
    m = 4; // Exemplo: número de linhas da matriz A e elementos do vetor y
    n = 3; // Exemplo: número de colunas da matriz A e elementos do vetor x
    thread_count = 2; // Exemplo: número de threads

    // Alocação de memória para A, x e y.
    A = (double **) malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        A[i] = (double *) malloc(n * sizeof(double));
    }

    x = (double *) malloc(n * sizeof(double));
    y = (double *) malloc(m * sizeof(double));

    // Inicialização de A e x (exemplo).
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j; // Exemplo: valores aleatórios para A
        }
    }

    for (int i = 0; i < n; i++) {
        x[i] = i; // Exemplo: valores aleatórios para x
    }

    pthread_t *thread_handles;
    thread_handles = (pthread_t *) malloc(thread_count * sizeof(pthread_t));

    long thread;
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    // Exibindo o resultado da matriz-vetor.
    printf("Resultado do produto matriz-vetor:\n");
    for (int i = 0; i < m; i++) {
        printf("%f ", y[i]);
    }
    printf("\n");

    // Liberação de memória alocada.
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);
    free(thread_handles);

    return 0;
}