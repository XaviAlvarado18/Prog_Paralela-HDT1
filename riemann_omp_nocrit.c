#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Definición de las funciones a integrar
double f1(double x) {
    return x * x; // x^2
}

double f2(double x) {
    return 2 * x * x * x; // 2x^3
}

double f3(double x) {
    return sin(x); // sin(x)
}

// Arreglo global para almacenar la suma local de cada thread
double global_integral[1000]; // Ajusta el tamaño según el número máximo de threads esperado

// Función para calcular la integral usando la regla del trapecio en paralelo
void trapezoides_parallel(double a, double b, int n, double (*func)(double), int threads) {
    double h = (b - a) / n; // Ancho de cada trapecio
    int n_local = n / threads; // Número de trapezoides que cada thread manejará

    #pragma omp parallel num_threads(threads)
    {
        int id_thread = omp_get_thread_num(); // ID del thread
        double a_local = a + id_thread * n_local * h; // Valor inicial local del rango
        double b_local = a_local + n_local * h; // Valor final local del rango
        double sum_local = 0.5 * (func(a_local) + func(b_local)); // Suma inicial de las alturas de los trapecios

        // Ciclo for no paralelizado para calcular la suma local
        for (int i = 1; i < n_local; ++i) {
            double x = a_local + i * h;
            sum_local += func(x);
        }

        // Almacenar la suma local en el arreglo global
        global_integral[id_thread] = h * sum_local;
    }

    // Sumar los resultados locales de cada thread para obtener la integral total
    double total_integral = 0.0;
    for (int i = 0; i < threads; i++) {
        total_integral += global_integral[i];
    }

    // Actualizar el valor de la integral global
    global_integral[0] = total_integral;
}

int main(int argc, char* argv[]) {
    // Parámetros por defecto
    double a = 2.0;
    double b = 10.0;
    int n = 500; // Número total de trapezoides
    int threads = 4; // Número de threads a utilizar

    // Si se ingresan parámetros, se toman esos valores
    if (argc > 1) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        threads = atoi(argv[3]);
    }

    // Verificar que el número de trapezoides sea múltiplo del número de threads
    if (n % threads != 0) {
        printf("El número de trapezoides debe ser múltiplo del número de threads.\n");
        return 1;
    }

    // Menú para seleccionar la función a integrar
    printf("Seleccione la función a integrar:\n");
    printf("1. x^2\n");
    printf("2. 2x^3\n");
    printf("3. sin(x)\n");

    int opcion;
    scanf("%d", &opcion);

    double (*func)(double);

    // Selección de la función según la opción del usuario
    switch (opcion) {
        case 1:
            func = f1;
            break;
        case 2:
            func = f2;
            break;
        case 3:
            func = f3;
            break;
        default:
            printf("Opción inválida.\n");
            return 1;
    } 

    // Llamada a la función paralelizada
    trapezoides_parallel(a, b, n, func, threads);

    // Se imprime el resultado final
    printf("Con n = %d trapezoides, nuestra aproximación de la integral de %.6lf a %.6lf es: %.10lf\n",
           n, a, b, global_integral[0]);

    return 0;
}
