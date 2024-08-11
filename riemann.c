
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f1(double x) {
    return x * x; // Se define la funcion x^2
}

double f2(double x) {
    return 2 * x * x * x; // Se define la funcion 2x^3
}

double f3(double x) {
    return sin(x); // Se define la funcion sin(x)
}

// Funcion trapecios
double trapezoides(double a, double b, int n, double (*func)(double)) {
    double h = (b - a) / n; // Se calcula el ancho de cada trapecio
    double sum = 0.5 * (func(a) + func(b)); // Se calcula la suma de las alturas de los trapecios

    // Se calcula la suma de las alturas de los trapecios
    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += func(x);
    }

    // Se calcula el area total
    return h * sum;
}


int main(int argc, char* argv[]) {
    // Parámetros por defecto
    double a = 2.0;
    double b = 10.0;
    int n = 4;

    // Si se ingresan parámetros, se toman esos valores
    if (argc > 1) {
        a = atof(argv[1]);
        b = atof(argv[2]);
        n = atoi(argv[3]);
    }

    // Menú para seleccionar la función a integrar
    printf("Seleccione la función a integrar:\n");
    printf("1. x^2\n");
    printf("2. 2x^3\n");
    printf("3. sin(x)\n");

    int opcion;
    scanf("%d", &opcion);

    double result;

    // Selección de la función según la opción del usuario
    switch (opcion) {
        case 1:
            result = trapezoides(a, b, n, f1);
            printf("Para x^2: %.10lf\n", result);
            break;
        case 2:
            result = trapezoides(a, b, n, f2);
            printf("Para 2x^3: %.10lf\n", result);
            break;
        case 3:
            result = trapezoides(a, b, n, f3);
            printf("Para sin(x): %.10lf\n", result);
            break;
        default:
            printf("Opción inválida.\n");
            return 1;
    }

    return 0;
}
