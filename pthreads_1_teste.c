#include <stdio.h>
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
    // Inicialização e alocação de memória para A, x e y.

    // Inicialização de m, n, A, x e y.

    // Inicialização de thread_count.

    pthread_t *thread_handles;
    thread_handles = malloc(thread_count * sizeof(pthread_t));

    long thread;
    for (thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *) thread);
    }

    for (thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    // Liberar memória e outros recursos alocados.

    free(thread_handles);

    return 0;
}