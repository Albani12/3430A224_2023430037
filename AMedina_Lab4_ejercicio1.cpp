#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

//estructura del nodo del árbol
struct Nodo {
    int dato;               //valor del nodo
    Nodo *izquierdo;       //puntero al hijo izquierdo
    Nodo *derecho;         //puntero al hijo derecho
};

class ArbolBinarioBusqueda {
    private:
    Nodo* raiz;  //puntero a la raiz del arbol

    //funcion para crear un nuevo nodo
    Nodo* crearNodo(int dato) {
        Nodo* nuevo = new Nodo();
        nuevo->dato = dato; //asigna el datoa l nuevo nodo
        nuevo->izquierdo = nuevo->derecho = nullptr; //inicializa hijos como nulos
        return nuevo; //devuelve el nuevo nodo
    }

    //funcion para buscar si ya existe un numero en el arbol
    bool buscar(Nodo* nodo, int dato) const {
    if (nodo == nullptr) {
        return false; //si el nodo es nulo, el dato no se encuentra
    }

    if (dato == nodo->dato) {
        return true; //si se encuentra el dato se retorna true
    }

    if (dato < nodo->dato) {
        return buscar(nodo->izquierdo, dato); //busca en el subarbol izquierdo
    } else {
        return buscar(nodo->derecho, dato); //busca en el subarbol derecho
    }
    }

    //funcion para insertar un nodo en el arbol
    Nodo* insertar(Nodo* nodo, int dato) {
    if (nodo == nullptr) {  //si el nodo esta vacio se crea uno nuevo
        return crearNodo(dato); 
    }
    if (buscar(nodo, dato)) {  //se verifica si el dato ya existe en el arbol
        cout << "El numero " << dato << " ya existe en el arbol. No se puede insertar." << endl;
        return nodo; //retorna el nodo actual sin cambios
    }
    if (dato < nodo->dato) { //si el dato es menor, se inserta en el subarbol izquierdo
        nodo->izquierdo = insertar(nodo->izquierdo, dato);
    } else { //si el dato es mayor, se inserta en el subarbol derecho
        nodo->derecho = insertar(nodo->derecho, dato);
    }
    return nodo;
    }

    //funcion para eliminar un nodo con un dato especifico
    Nodo* eliminar(Nodo* nodo, int dato) {
        if (nodo == nullptr) return nodo; //si el nodo es nulo no hay nada que eliminar
        if (dato < nodo->dato) {
            nodo->izquierdo = eliminar(nodo->izquierdo, dato); //busca en la parte izquierda del arbol
        } else if (dato > nodo->dato) {
            nodo->derecho = eliminar(nodo->derecho, dato);  //busca en la parte derecha del arbol
        } else {
            //nodo encontrado
            if (nodo->izquierdo == nullptr) { //Sin hijo izquierdo
                Nodo* temp = nodo->derecho; //Reemplaza con hijo derecho
                delete nodo; //libera nodo
                return temp; //retorna el nuevo nodo
            } else if (nodo->derecho == nullptr) { //Sin hijo derecho
                Nodo* temp = nodo->izquierdo; //reemplaza con hijo izquierdo
                delete nodo;
                return temp;
            }
            //Nodo con 2 hijos
            Nodo* temp = minValorNodo(nodo->derecho); //minimo valor del subarbol derecho
            nodo->dato = temp->dato; //reemplaza el dato del nodo a eliminar
            nodo->derecho = eliminar(nodo->derecho, temp->dato); //ahora elimina el nodo encontrado
        }
        return nodo;
    }

    //funcion para encontrar el nodo con el valor mínimo
    Nodo* minValorNodo(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual && actual->izquierdo != nullptr) //busca el minimo en el subarbol
            actual = actual->izquierdo;
        return actual; //devuelve el nodo minimo
    }

    // Metodo recursivo privado para imprimir el arbol en preorden
    void preorden(Nodo* nodo) const {
        if (nodo == nullptr) {
            return;
        }
        cout << nodo->dato << " "; //Imprimir el dato del nodo actual
        preorden(nodo->izquierdo); // Recorrer el subarbol izquierdo
        preorden(nodo->derecho);    //Recorrer el subarbol derecho  
    }

    //funcion para imprimir el arbol en inorden
    void inorden(Nodo* nodo) {
        if (nodo != nullptr) {
            inorden(nodo->izquierdo); // Recorrer al subarbol izquierdo
            cout << nodo->dato << " "; // Muestra el nodo actual
            inorden(nodo->derecho);    // Recorrer al subarbol derecho
        }
    }

    //funcion para mostrar el arbol en posorden
    void posorden(Nodo* nodo) {
        if (nodo != nullptr) {
            posorden(nodo->izquierdo); // Recorrer al subarbol izquierdo
            posorden(nodo->derecho);    // Recurre al subarbol derecho
            cout << nodo->dato << " "; // Muestra el nodo actual
        }
    }

    //funcion para generar el archivo de grafo
    void generarGrafo(Nodo* nodo, ofstream& archivo) {
        if (nodo != nullptr) {
            if (nodo->izquierdo != nullptr) { //si tiene hijo izquierdo
                archivo << nodo->dato << " -> " << nodo->izquierdo->dato << std::endl;
                generarGrafo(nodo->izquierdo, archivo); //recorre al hijo izquierdo
            } else {
                //si no tiene hijo izquierdo, crea un punto
                archivo << "\"" << nodo->dato << "i\" [shape=point];" << std::endl;
                archivo << nodo->dato << " -> \"" << nodo->dato << "i\";" << std::endl;
            }
            if (nodo->derecho != nullptr) { //si tiene hijo derecho
                archivo << nodo->dato << " -> " << nodo->derecho->dato << ";" << std::endl;
                generarGrafo(nodo->derecho, archivo); //recorre al hijo derecho
            } else {
                //si no tiene hijo derecho, crea un punto
                archivo << "\"" << nodo->dato << "d\" [shape=point];" << std::endl;
                archivo << nodo->dato << " -> \"" << nodo->dato << "d\";" << std::endl;
            }
        }
    }

public:
    //Constructor
    ArbolBinarioBusqueda() {
        raiz = nullptr; 
    }

    //funcion para insertar un dato en el arbol
    void insertar(int dato) {
        raiz = insertar(raiz, dato); 
    }

    //funcion para eliminar un dato del arbol
    void eliminar(int dato) {
        raiz = eliminar(raiz, dato);
    }

    //funcion para modificar un dato en el arbol
    void modificar(int valorViejo, int valorNuevo) {
        eliminar(valorViejo);
        insertar(valorNuevo); 
    }

    //funcion para mostrar el arbol en preorden
    void mostrarPreorden() {
        preorden(raiz); // aqui llama la funcion de recorrido en preorden
        cout << endl;
    }

    //funcion para mostrar el arbol en Inorden
    void mostrarInorden() {
        inorden(raiz); //aca llama a la funcion de recorrido en inorden
        cout << endl;
    }

    //funcion para mostrar el arbol en Posorden
    void mostrarPosorden() {
        posorden(raiz); //llama a la funcion de recorrido en Posorden
        cout << endl;
    }

    //metodo para generar el grafo en formato Graphviz
    void generarGrafo() {
        ofstream archivo("grafo.txt"); //crea el archivo de texto
        archivo << "digraph G {\nnode [style=filled fillcolor=yellow];" << std::endl;
        generarGrafo(raiz, archivo); //llama a la funcion que genera el grafo
        archivo << "}" << std::endl;
        archivo.close(); // Cierra el archivo
        system("dot -Tpng -ografo.png grafo.txt"); //genera la imagen del grafo
        system("start grafo.png"); //muestra la imagen generada
    }
};

int main() {
    ArbolBinarioBusqueda arbol; //crea una instancia del arbol
    int opcion, dato, viejo, nuevo;

    do {
        cout << "--- MENU ---" << std::endl;
        cout << "1. Insertar numero" << std::endl;
        cout << "2. Eliminar numero" << std::endl;
        cout << "3. Modificar numero" << std::endl;
        cout << "4. Mostrar Preorden" << std::endl;
        cout << "5. Mostrar Inorden" << std::endl;
        cout << "6. Mostrar Posorden" << std::endl;
        cout << "7. Generar grafo" << std::endl;
        cout << "8. Salir" << std::endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion; 

        switch (opcion) {
            case 1:
                cout << "Ingrese el numero a insertar: ";
                cin >> dato; // Lee el numero a insertar
                arbol.insertar(dato); // procede a llamar la función para insertar
                break;
            case 2:
                cout << "Ingrese el numero a eliminar: ";
                cin >> dato; // lee el numero a eliminar
                arbol.eliminar(dato); // llama a la funcion de eliminacion
                break;
            case 3:
                cout << "Ingrese el numero a modificar: ";
                cin >> viejo; //lee el número a modificar
                cout << "Ingrese el nuevo valor: ";
                cin >> nuevo; //Lee el nuevo valor
                arbol.modificar(viejo, nuevo); //Llama a la funcion de modificacion
                break;
            case 4:
                cout << "Recorrido en Preorden: ";
                arbol.mostrarPreorden(); // imprime el recorrido en Preorden
                break;
            case 5:
                cout << "Recorrido en Inorden: ";
                arbol.mostrarInorden(); // imprime el recorrido en Inorden
                break;
            case 6:
                cout << "Recorrido en Posorden: ";
                arbol.mostrarPosorden(); // imprime el recorrido en Posorden
                break;
            case 7:
                arbol.generarGrafo(); //genera el grafo
                break;
            case 8:
                cout << "Saliendo del programa..." << std::endl; //Mensaje de salida
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << std::endl; // Mensaje de opcion invalida
        }
    } while (opcion != 8); //continúa hasta que el usuario elija salir

    return 0; //Fin del programa
}
