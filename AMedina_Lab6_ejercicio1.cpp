#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;
const int MAX_N = 5; //Numero maximo de nodos en el grafo

// Prototipos de funciones
void leer_matriz(int M[MAX_N][MAX_N], int n, string V[MAX_N]);
void inicializar_vector_D(int D[MAX_N], int M[MAX_N][MAX_N], int origen, int n);
void inicializar_vector_caracter(string vector[MAX_N], int n);
void aplicar_dijkstra(string V[MAX_N], string S[MAX_N], string VS[MAX_N], int D[MAX_N], int M[MAX_N][MAX_N], int origen, int n);
void actualizar_VS(string V[MAX_N], string S[MAX_N], string VS[MAX_N], int n);
int buscar_indice_caracter(string V[MAX_N], char caracter, int n);
void agrega_vertice_a_S(string S[MAX_N], char vertice, int n);
int elegir_vertice(string VS[MAX_N], int D[MAX_N], string V[MAX_N], int n);
void actualizar_pesos(int D[MAX_N], string VS[MAX_N], int M[MAX_N][MAX_N], string V[MAX_N], char v, int n);
int calcular_minimo(int dw, int dv, int mvw);
void imprimir_vector_caracter(string vector[MAX_N], string nomVector, int n);
void imprimir_vector_entero(int vector[MAX_N], int n);
void imprimir_matriz(int M[MAX_N][MAX_N], int n);
void imprimir_grafo(int M[MAX_N][MAX_N], string V[MAX_N], int n);

int main() {
    int n; //Numero de nodos
    char vertice_origen; //vertice de inicio para el algoritmo de Dijkstra
    //se solicita al usuario el numero de nodos
    cout << "Ingrese el numero de nodos (mayor que 2): "; 
    cin >> n;

    //Validacion de numero de nodos
    if (n < 2 || n > MAX_N) {
        cout << "El numero de nodos debe ser mayor a 2 y menor o igual a " << MAX_N << "." << endl;
        return 1;
    }

    int M[MAX_N][MAX_N]; // Matriz de distancias
    //Inicializa la matriz de distancias
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = (i == j) ? 0 : -1; //La distancia a si mismo es 0, y -1 indica que no hay conexion
        }
    }

    string V[MAX_N]; // Nodos representados como caracteres
    string S[MAX_N]; // Nodos seleccionados
    string VS[MAX_N]; // Nodos restantes
    int D[MAX_N]; // Vector de distancias mínimas desde el vertice origen

    //Inicialización de los vectores de nodos
    inicializar_vector_caracter(V, n);
    inicializar_vector_caracter(S, n);
    inicializar_vector_caracter(VS, n);

    //Leer los datos de la matriz de distancias desde la terminal
    leer_matriz(M, n, V);

    // Lectura del vertice origen
    cout << "Ingrese el vertice origen (un caracter entre 'A' y '" << char('A' + n - 1) << "'): "; 
    cin >> vertice_origen;

    // Validar que el vértice origen este dentro del rango
    int indice_origen = buscar_indice_caracter(V, vertice_origen, n);
    if (indice_origen == -1) {
        cout << "El vertice origen no es valido" << endl;
        return 1;
    }

    // Valores de prueba: Matriz de adyacencia
    //int M[N][N] = {{0, 4, 11, -1, -1},
      //             {-1, 0, -1, 6, 2},
        //           {-1, 3, 0, 6, -1},
          //         {-1, -1, -1, 0, -1},
            //       {-1, -1, 5, 3, 0}};

    //Aplicacion del algoritmo de Dijkstra
    aplicar_dijkstra(V, S, VS, D, M, indice_origen, n);

    //Genera el grafo resultante usando Graphviz
    imprimir_grafo(M, V, n);

    return 0;
}

// Funcion para leer la matriz de distancias desde la terminal
void leer_matriz(int M[MAX_N][MAX_N], int n, string V[MAX_N]) {
    cout << "Ingrese las conexiones entre los nodos:" << endl;
    for (int i = 0; i < n; i++) {
        V[i] = char('A' + i); //Inicializa los nodos con letras A, B, C...
        for (int j = 0; j < n; j++) {
            if (i != j) { //No preguntar sobre conexiones a si mismo
                cout << "Pregunta... El nodo " << V[i] << " se conecta con el nodo " << V[j] << "? (1 para si, 0 para no): ";
                int conexion; //Variable para almacenar la respuesta del usuario
                cin >> conexion;
                //Validacion de entrada
                while (conexion != 0 && conexion != 1) {
                    cout << "Entrada inválida. Ingrese 1 para sí o 0 para no: ";
                    cin >> conexion;
                }
                //Si hay conexión, solicitar el peso
                if (conexion == 1) {
                    cout << "Ingrese el peso de la conexion: ";
                    cin >> M[i][j]; //Asigna el peso a la matriz
                } else {
                    M[i][j] = -1; //No hay conexión
                }
            } else {
                M[i][j] = 0; //La distancia a sí mismo es 0
            }
        }
    }
}

// Inicializa el vector D[] con los valores de la primera fila de la matriz de adyacencia M[][]
void inicializar_vector_D(int D[MAX_N], int M[MAX_N][MAX_N], int origen, int n) {
    for (int col = 0; col < n; col++) {
        D[col] = M[origen][col];  // Copia la fila del origen a D[]
    }
}

// Inicializa los vectores de caracteres con espacios vacios
void inicializar_vector_caracter(string vector[MAX_N], int n) {
    for (int col = 0; col < n; col++) {
        vector[col] = " "; // Inicializar con un espacio
    }
}

// Aplica el algoritmo de Dijkstra para encontrar las distancias mínimas desde el vértice origen
//Dijkstra es un algoritmo para la determinación del camino más corto dado un vértice origen al resto de los vértices en un grafo con pesos en cada arista
void aplicar_dijkstra(string V[MAX_N], string S[MAX_N], string VS[MAX_N], int D[MAX_N], int M[MAX_N][MAX_N], int origen, int n) {
    // Inicializa D[] según la primera fila de la matriz de adyacencia M[][]
    inicializar_vector_D(D, M, origen, n);

    // Imprime los estados iniciales de la matriz, S[], VS[], y D[]
    cout << "--------- Estados iniciales ---------------------------------------\n";
    imprimir_matriz(M, n);
    imprimir_vector_caracter(S, "S", n);
    imprimir_vector_caracter(VS, "VS", n);
    imprimir_vector_entero(D, n);
    cout << "------------------------------------------------------------------\n\n";

    // Agrega el primer vértice a S[] y actualiza VS[]
    agrega_vertice_a_S(S, V[origen][0], n);
    actualizar_VS(V, S, VS, n);
    imprimir_vector_caracter(S, "S", n);
    imprimir_vector_caracter(VS, "VS", n);
    imprimir_vector_entero(D, n);

    // Itera para procesar todos los vértices
    for (int i = 1; i < n; i++) {
        // Elige el vértice con el menor peso en VS[] según los valores en D[]
        int v = elegir_vertice(VS, D, V, n);

        // Agrega el vértice seleccionado a S[] y actualiza VS[]
        agrega_vertice_a_S(S, V[v][0], n);
        actualizar_VS(V, S, VS, n);
        actualizar_pesos(D, VS, M, V, V[v][0], n);  // Actualiza los pesos en D[] con el vértice seleccionado
    }
}

// Elige el vértice con el menor peso en VS[]
int elegir_vertice(string VS[MAX_N], int D[MAX_N], string V[MAX_N], int n) {
    int menor = numeric_limits<int>::max(); //Inicializa el menor con el máximo valor posible
    int vertice = -1; //Inicializa el índice del vértice seleccionado
    for (int i = 0; i < n; i++) {
        //Verifica si el vértice está en VS y tiene un valor válido en D
        if (VS[i] != " " && D[i] != -1 && D[i] < menor) {
            menor = D[i]; //Actualiza el menor
            vertice = i; // Guarda el indice del vertice
        }
    }
    return vertice;
}

// Actualiza el vector VS[] eliminando los vértices que ya están en S[]
void actualizar_VS(string V[MAX_N], string S[MAX_N], string VS[MAX_N], int n) {
    inicializar_vector_caracter(VS, n); //Inicializa VS[]
    int k = 0;
    for (int j = 0; j < n; j++) {
         //Solo agrega nodos que no están en S[]
        if (S[j] == " ") {
            VS[k] = V[j]; //Agrega el nodo a VS[]
            k++;
        }
    }
}

// Busca el indice de un caracter en el vector V[]
int buscar_indice_caracter(string V[MAX_N], char caracter, int n) {
    for (int i = 0; i < n; i++) {
        if (V[i][0] == caracter) return i; //devuelve el indice si se encuentra el carácter
    }
    return -1; //Devuelve -1 si no se encuentra
}

//Agrega un vertice al conjunto S[]
void agrega_vertice_a_S(string S[MAX_N], char vertice, int n) {
    for (int i = 0; i < n; i++) {
        //busca el primer espacio vacio en S[] y agrega el vertice
        if (S[i] == " ") {
            S[i] = vertice; //asigna el vértice a S[]
            break;
        }
    }
}

// Actualiza los pesos en el vector D[] para los vértices adyacentes al vértice 'v'
void actualizar_pesos(int D[MAX_N], string VS[MAX_N], int M[MAX_N][MAX_N], string V[MAX_N], char v, int n) {
    int indice_v = buscar_indice_caracter(V, v, n); //busca el índice del vertice
    for (int i = 0; i < n; i++) {
         //Actualiza D[] solo para los vértices en VS[]
        if (VS[i] != " " && D[i] != -1) {
            D[i] = calcular_minimo(D[i], D[indice_v], M[indice_v][i]); //calcula el nuevo peso
        }
    }
}

// Calcula el valor mínimo entre dw, dv y mvw (distancia directa e indirecta)
int calcular_minimo(int dw, int dv, int mvw) {
    int min = 0;

     //caso donde dw es -1 (no hay camino anterior)
    if (dw == -1) {
        if (dv != -1 && mvw != -1)
            min = dv + mvw; //suma de distancias
        else
            min = -1; //no hay camino
    } else {
        if (dv != -1 && mvw != -1) {
             //compara el camino directo con el indirecto
            if (dw <= (dv + mvw))
                min = dw; //mantiene el camino directo
            else
                min = (dv + mvw);  //usa el camino indirecto
        }
        else
            min = dw; //mantiene el camino directo
    }
    cout << "dw: " << dw << " dv: " << dv << " mvw: " << mvw << " min: " << min << endl;
    return min;
}

// Imprime un vector de caracteres
void imprimir_vector_caracter(string vector[MAX_N], string nomVector, int n) {
    for (int i = 0; i < n; i++) {
        cout << nomVector << "[" << i << "]: " << vector[i] << endl;
    }
}

// Imprime un vector de enteros
void imprimir_vector_entero(int vector[MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        cout << vector[i] << " ";  //imprime cada elemento del vector
    }
    cout << endl;
}

// Imprime una matriz de enteros
void imprimir_matriz(int M[MAX_N][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Matriz[" << i << "][" << j << "]: " << M[i][j] << " "; //Imprime cada elemento de la matriz
        }
        cout << endl;
    }
}

// Genera el archivo para el grafo usando Graphviz y lo visualiza
void imprimir_grafo(int M[MAX_N][MAX_N], string V[MAX_N], int n) {
    ofstream archivo("grafo.txt"); // Crea el archivo de texto

    // Inicio del archivo DOT
    archivo << "digraph G {" << endl;
    archivo << "node [shape=circle, style=filled, fillcolor=yellow];" << endl;
    archivo << "rankdir=LR;" << endl;

    // Agrega las aristas a la representación del grafo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M[i][j] != -1 && M[i][j] != 0) {
                archivo << V[i] << " -> " << V[j] << " [label=\"" << M[i][j] << "\"];" << endl;
            }
        }
    }

    //fin del archivo DOT
    archivo << "}" << endl;
    archivo.close(); //cierra el archivo

    //usa Graphviz para generar la imagen y luego la muestra
    system("dot -Tpng -ografo.png grafo.txt"); //genera la imagen del grafo en formato PNG
    system("start grafo.png"); //muestra la imagen generada en Windows
}
