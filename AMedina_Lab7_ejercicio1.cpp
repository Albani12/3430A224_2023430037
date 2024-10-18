#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;
const int MAX_N = 10; //Numero maximo de nodos en el grafo
const int INF = numeric_limits<int>::max(); // Definicion de infinito para representar la ausencia de conexion

class Grafo{
private:
    int matriz[MAX_N][MAX_N]; //Matriz de distancias
    int N; //numero de nodos

public:
    Grafo(int num_nodos) : N(num_nodos) {
        //inicializa la matriz con ceros, distancia 0 para cada nodo consigo mismo, infinito para los demás
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matriz[i][j] = (i==j) ? 0: INF; //evita conexiones directas
            }
        }
    }

    // Funcion para leer la matriz de distancias desde la terminal
    void leer_matriz() {
        cout << "Ingrese las conexiones entre los nodos:" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j) { //No preguntar sobre conexiones a si mismo
                    cout << "Pregunta... El nodo " << char('A' + i) << " se conecta con el nodo " << char('A' + j) << "? (1 para si, 0 para no): ";
                    int conexion; //Variable para almacenar la respuesta del usuario
                    cin >> conexion;
                    //Validacion de entrada
                    while (conexion != 0 && conexion != 1) {
                        cout << "Entrada invalida. Ingrese 1 para si o 0 para no: ";
                        cin >> conexion;
                    }
                    //Si hay conexión, solicitar el peso
                    if (conexion == 1) {
                        cout << "Ingrese el peso de la conexion: ";
                        cin >> matriz[i][j]; //Asigna el peso a la matriz
                    } else {
                        matriz[i][j] = INF; //No hay conexión
                    }
                } else {
                    matriz[i][j] = 0; //La distancia a sí mismo es 0
                }
            }   
        }
    }

    // Imprime una matriz de enteros
    void imprimir_matriz() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << "Matriz[" << i << "][" << j << "]: " << matriz[i][j] << " "; //Imprime cada elemento de la matriz
            }
            cout << endl;
        }
    }

    // Genera el archivo para el grafo original usando Graphviz y lo visualiza
    void imprimir_grafo_original() {
        ofstream archivo("grafo_original.txt"); // Crea el archivo de texto

        // Inicio del archivo DOT
        archivo << "digraph G {" << endl;
        archivo << "node [shape=circle, style=filled, fillcolor=green];" << endl;
        archivo << "rankdir=LR;" << endl;

        // Agrega las aristas a la representacion del grafo original
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matriz[i][j] != INF && i != j) { // Solo agregar aristas que existan
                    archivo << char('A' + i) << " -> " << char('A' + j) << " [label=\"" << matriz[i][j] << "\"];" << endl;
                }
            }
        }

        // Fin del archivo DOT
        archivo << "}" << endl;
        archivo.close(); // Cierra el archivo

        // Usa Graphviz para generar la imagen y luego la muestra
        system("dot -Tpng -ografo_original.png grafo_original.txt"); // Genera la imagen del grafo original en formato PNG
        system("start grafo_original.png"); // Muestra la imagen generada en Windows
    }

    // Genera el archivo para el grafo usando Graphviz y lo visualiza
    void imprimir_grafo(int padre[MAX_N]) {
        ofstream archivo("grafo.txt"); // Crea el archivo de texto

        // Inicio del archivo DOT
        archivo << "digraph G {" << endl;
        archivo << "node [shape=circle, style=filled, fillcolor=green];" << endl;
        archivo << "rankdir=LR;" << endl;

        // Agrega las aristas a la representación del grafo
        // Agrega las aristas a la representación del grafo
        for (int i = 1; i < N; i++) {
            archivo << char('A' + padre[i]) << " -> " << char('A' + i) << " [label=\"" << matriz[padre[i]][i] << "\"];" << endl;
        }

        //fin del archivo DOT
        archivo << "}" << endl;
        archivo.close(); //cierra el archivo

        //usa Graphviz para generar la imagen y luego la muestra
        system("dot -Tpng -ografo.png grafo.txt"); //genera la imagen del grafo en formato PNG
        system("start grafo.png"); //muestra la imagen generada en Windows
    }

    //implementacion del algoritmo de prim, el cual consiste en
    //encuentrar arbol abarcador de costo minimo de una grafica G de N vertices. U, V y L son
    //estructuras de datos -arreglos o listas- que permiten guardar los nombres de los vertices y las
    //aristas seleccionadas.

    void prim() {
        int padre[MAX_N]; //para almacenar el arbol de costo minimo
        int costo[MAX_N]; //para akmacenar el costo minimo de añadir cada nodo, las aristas
        bool incluido[MAX_N]; //para verificar si el nodo esta incluido en el arbol de costo minimo
            
        //inicializa los arreglos
        for (int i = 0; i < N; i++) {
            costo[i] = INF; //inicializa todos los pesos como infinitos 
            incluido[i] = false; //no se ha incluido ningun nodo en el arbol de costo minimo
            padre[i] = -1; //inicialmente ningun nodo tiene un padre asignado
        }

        //el primer nodo es el punto de partida
        costo[0] = 0; //el costo del primero nodo es 0
        padre[0] = -1; //el primer nodo es la raiz 

        //encuentra el arbol de costo minimo (ACM)
        //el algoritmo de prim selecciona los nodos uno por uno
        for (int conteo = 0; conteo < N-1; conteo++) {
            //encuentra el nodo con el costo minimo que no ha sido incluido en el ACM
            int u = minCosto(costo, incluido);
            incluido[u] = true; // añade el nodo al ACM y lo marca
            //actualiza los valores de costo y padre para los nodos adyacentes
            for (int v = 0; v < N; v++) {
                //actualiza el costo solo su la matriz [u][v] es menor que costo [v] y v no esta en el ACM, es decir
                //Solo actualiza si hay una arista y no ha sido incluido, y si el nuevo costo es menor
                if (matriz[u][v] != INF && !incluido[v] && matriz[u][v] < costo[v]) {
                    padre[v] = u; //actualiza padre
                    costo[v] = matriz[u][v]; //actualiza costo
                }

            }
        }
        //imprime el arbol de costo minimo
        cout << "Conjunto de L (aristas del Arbol de Costo Minimo): " << endl;
        for (int i = 1; i < N; i++) {
            cout << "Nodo " << (char)('A'+padre[i]) << "- Nodo" << (char)('A' +i) << ": Costo " << matriz[padre[i]][i] << endl;
        }

        //genera el grafo de costo minimo
        imprimir_grafo(padre);
    }

    //encuentra el nodo con el valor de costo minimo
    int minCosto(int costo[MAX_N], bool incluido[MAX_N]) {
        int min = INF, min_index; /// Inicializa el costo minimo como infinito
        //// Busca el nodo con el costo mas pequeño que aun no ha sido incluido
        for (int v = 0; v < N; v++) {
            if (!incluido[v] && costo[v] < min) {
                min = costo[v];
                min_index = v;
            }
        }
        return min_index;
    }
};

int main() {
    int N;
    cout << "Ingrese el numero de nodos (mayor que 2): "; 
    cin >> N;

    //Validacion de numero de nodos
    if (N < 2 || N > MAX_N) {
        cout << "El numero de nodos debe ser mayor a 2 y menor o igual a " << MAX_N << "." << endl;
        return 1;
    }
    //Se generan y visualizan el grafo original y el arbol de costo minimo usando Graphviz.
    Grafo grafo(N);
    grafo.leer_matriz();
    grafo.imprimir_matriz();
    grafo.imprimir_grafo_original();
    grafo.prim();

    return 0;
}
