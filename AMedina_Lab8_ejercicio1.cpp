#include <iostream>
#include <fstream>
#include <string>
#include <limits> 
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <chrono>  // Para medir el tiempo

using namespace std;

const long int MAX = 1000; //tamaño máximo del arreglo

//Implementacion del algoritmo de seleccion (O(n^2))
void seleccion(int A[], int N) {
    for (int I = 0; I < N - 1; ++I) {
        int MENOR = A[I];  // Hacer MENOR <- A[I]
        int K = I;         // Hacer K <- I

        for (int J = I + 1; J < N; ++J) {
            if (A[J] < MENOR) {  //Si A[J] < MENOR entonces
                MENOR = A[J];    //hacer MENOR <- A[J]
                K = J;           //hacer K <- J
            }
        }
        // Intercambiar A[K] con A[I]
        A[K] = A[I];
        A[I] = MENOR;
    }
}

//Funcion que realiza la particion para Quicksort
int particion(int A[], int bajo, int alto) {
    int pivote = A[alto]; //Elegir el ultimo elemento como pivote
    int i = bajo - 1; //indice del elemento mas pequeño

    for (int j = bajo; j < alto; j++) {
        if (A[j] < pivote) {
            i++;
            swap(A[i], A[j]); //Intercambiar
        }
    }
    swap(A[i + 1], A[alto]); //Colocar el pivote en la posicion correcta
    return i + 1;
}

//Implementacion de Quicksort (O(n*log n))
void quicksort(int A[], int bajo, int alto) {
    if (bajo < alto) {
        int pivote = particion(A, bajo, alto);
        quicksort(A, bajo, pivote - 1); //Recursion en la parte izquierda
        quicksort(A, pivote + 1, alto);  //Recursion en la parte derecha
    }
}

//Funcion para mostrar el contenido del arreglo
void mostrarArreglo(int A[], int N) {
    for (int i = 0; i < N; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    int N;
    char VER;
    //Entrada del numero de elementos
    cout << "Ingrese el numero de elementos a ordenar (N, maximo " << MAX << "): ";
    cin >> N;

    if (N <= 0 || N > MAX) {
        cerr << "El valor de N debe ser positivo y menor o igual a " << MAX << "." << endl;
        return 1;
    }

    //Preguntar si el usuario desea mostrar los arreglos
    cout << "Desea ver los contenidos del arreglo antes y despues del ordenamiento? (S/N): ";
    cin >> VER;

    int A[MAX];

    //Inicializar el generador de numeros aleatorios
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        A[i] = rand() % 1000;  //genera numeros aleatorios
    }

    //mostrar el arreglo original si VER es 'S' o 's'
    if (VER == 'S' || VER == 's') {
        cout << "Arreglo original: ";
        mostrarArreglo(A, N);
    }

    //Copiar el arreglo original para usarlo en Quicksort
    int B[MAX];
    for (int i = 0; i < N; ++i) {
        B[i] = A[i];
    }

    //ordenar usando el algoritmo de seleccion
    auto start = chrono::high_resolution_clock::now(); // Inicio del tiempo
    seleccion(A, N);
    auto end = chrono::high_resolution_clock::now(); // Fin del tiempo
    chrono::duration<double> tiempoSeleccion = (end - start)*10000000000; // Tiempo en nanosegundos para que pueda salir un valor en pantalla

    //mostrar el arreglo ordenado si VER es 'S' o 's'
    if (VER == 'S' || VER == 's') {
        cout << "Arreglo ordenado por seleccion: ";
        mostrarArreglo(A, N);
    }
    cout << "Tiempo de ordenamiento por seleccion: " << tiempoSeleccion.count() << " ns" << endl;

    //se ordena usando el algoritmo de Quicksort
    start = chrono::high_resolution_clock::now(); //inicia del tiempo
    quicksort(B, 0, N - 1);
    end = chrono::high_resolution_clock::now(); //termina el tiempo
    chrono::duration<double> tiempoQuicksort = (end - start)*10000000000; //Tiempo en nanosegundos para que pueda salir un valor en pantalla

    //Mostrar el arreglo ordenado si VER es 'S' o 's'
    if (VER == 'S' || VER == 's') {
        cout << "Arreglo ordenado por Quicksort: ";
        mostrarArreglo(B, N);
    }//Mostrar el tiempo de ejecucion
    cout << "Tiempo de ordenamiento por Quicksort: " << tiempoQuicksort.count() << " ns" << endl;

    return 0;
}



