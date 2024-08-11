#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void hello_thread(int thread_num, int thread_count);

int main(int argc, char* argv[]) {
    int threads_default = 10; // Valor predeterminado

    // Si se ingresa un valor en la línea de comandos, se utiliza como número de hilos
    if (argc > 1) {
        threads_default = strtol(argv[1], NULL, 10);
    }

    // Ejecuta la función en paralelo con el número de hilos especificado
    #pragma omp parallel num_threads(threads_default)
    hello_thread(omp_get_thread_num(), threads_default); // Imprime el número de hilo y la cantidad total de hilos

    return 0;
}

void hello_thread(int thread_num, int thread_count) {
    // Imprime un mensaje dependiendo de si el ID del hilo es par o impar
    if (thread_num % 2 == 0) {
        printf("Saludos del hilo %d\n", thread_num);
    } else {
        printf("Feliz cumpleaños número %d!\n", thread_count);
    }
}
