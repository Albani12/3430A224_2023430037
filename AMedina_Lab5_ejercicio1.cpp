#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

#define TRUE 1
#define FALSE 0
enum {IZQUIERDO, DERECHO};

//Estrcutura del nodo en el arbol
struct Nodo {
    int dato;
    int FE; //factor de equilibrio FE
    Nodo* izquierdo;  //puntero al hijo izquierdo
    Nodo* derecho;    //puntero al hijo derecho
    Nodo* padre; 
};

typedef Nodo* pNodo; //puntero a un nodo de tipo Nodo
typedef Nodo* pArbol; //puntero a un nodo

//clase arbol 
class Arbol {
private:
    pNodo raiz; //puntero a la raiz del arbol

    //funcion para crear un nuevo nodo
    pNodo crearNodo(int dato) {
        pNodo nuevo = new Nodo(); //se reserva memoria para un nuevo nodo
        nuevo->dato = dato; //se asigna valor al nodo
        nuevo->FE = 0;
        nuevo->izquierdo = nullptr; //no tiene hijo izquierdo al crearse
        nuevo->derecho = nullptr;   //no tiene hijo derecho al crearse
        nuevo->padre = nullptr;
        return nuevo; 
    }

    // Funciones de equilibrado:
    void Equilibrar(pArbol a, pNodo nodo, int rama, int nuevo);
    void RotaDerechaDerecha(pArbol a, pNodo nodo);
    void RotaIzquierdaIzquierda(pArbol a, pNodo nodo);
    void RotaDerechaIzquierda(pArbol a, pNodo nodo);
    void RotaIzquierdaDerecha(pArbol a, pNodo nodo);
    void Elimina_balanceado(pNodo* nodo, bool& bo, int infor); // Prototipo de la función auxiliar
    void reestructura_der(pNodo* &nodo, bool &bo);
    void reestructura_izq(pNodo* &nodo, bool &bo);

/* Funciones auxiliares: */
public:
    Arbol() : raiz(nullptr) {} //Constructor inicializa el arbol vacio

    void Podar();
    void Insertar(int dat);
    void Modificar(int viejo, int nuevo);
    void GenerarGrafo();
    void PreOrden(std::ofstream &fp);
    void Elimina_balanceado(int value);
    void MenuPrincipal(); //Función del menú

    void setRaiz(pNodo nodo) {
        raiz = nodo;
    }

private:
    void Podar(pArbol* a);
    pNodo Buscar(int dat); //función para buscar un nodo
};


void Arbol::MenuPrincipal(){
    int opcion = 0;
    int valor, nuevoValor;

    while (opcion != 6) {
        cout << "\n";
        cout << "<1> Ingresar numero\n";
        cout << "<2> Buscar numero\n";
        cout << "<3> Eliminar numero\n";
        cout << "<4> Modificar elemento\n";
        cout << "<5> Generar Grafo\n";
        cout << "<6> Salir\n";
        cout << "\nIngrese su opcion: ";
        cin >> opcion;

        // Validación de la entrada
        if (cin.fail()) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar la entrada incorrecta
            cout << "Entrada no valida. Intentalo de nuevo." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese su numero: ";
                cin >> valor;
                Insertar(valor); // insertar elemento en el árbol
                break;
            case 2: { // Buscar número
                cout << "Ingrese el numero a buscar: ";
                cin >> valor;
                pNodo resultado = Buscar(valor);
                if (resultado) {
                    cout << "Numero " << valor << " encontrado." << endl;
                } else {
                    cout << "Numero " << valor << " no encontrado." << endl;
                }
                break;
            }
            case 3: // Eliminar numero
                cout << "Ingrese el numero a eliminar: ";
                cin >> valor;
                Elimina_balanceado(valor); // eliminar el numero
                break;
            case 4: // Modificar elemento
                cout << "Ingrese el numero a modificar: ";
                cin >> valor;
                cout << "Ingrese el nuevo numero: ";
                cin >> nuevoValor;
                Modificar(valor, nuevoValor); // modificar el elemento
                break;
            case 5:
                GenerarGrafo(); 
                break;
            case 6:
                Podar(); //liberar memoria al salir
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intentalo de nuevo." << endl;
                break;
        }
    }
}

void Arbol::Podar() {
    Podar(&raiz);
}

void Arbol::Podar(pArbol* a) {
    if (*a) {
        Podar(&(*a)->izquierdo);
        Podar(&(*a)->derecho);
        delete *a;
        *a = nullptr;
    }
}

void Arbol::Insertar(int dat) {
    pNodo padre = nullptr;
    pNodo actual = raiz;

    while (actual != nullptr && dat != actual->dato) {
        padre = actual;

        if (dat < actual->dato)
            actual = actual->izquierdo;
        else if (dat > actual->dato)
            actual = actual->derecho;
    }

    if (actual != nullptr)
        return; //El numero ya existe

    pNodo nuevo = crearNodo(dat); //Crear nuevo nodo

    if (padre == nullptr) {
        raiz = nuevo;
    } else if (dat < padre->dato) {
        padre->izquierdo = nuevo;
        nuevo->padre = padre;
        Equilibrar(raiz, padre, IZQUIERDO, TRUE);
    } else {
        padre->derecho = nuevo;
        nuevo->padre = padre;
        Equilibrar(raiz, padre, DERECHO, TRUE);
    }
}

pNodo Arbol::Buscar(int dat) {
    pNodo actual = raiz;
    while (actual != nullptr) {
        if (dat == actual->dato) {
            return actual; // Número encontrado
        } else if (dat < actual->dato) {
            actual = actual->izquierdo; // Buscar en el subárbol izquierdo
        } else {
            actual = actual->derecho; // Buscar en el subárbol derecho
        }
    }
    return nullptr; //Numero no encontrado
}

void Arbol::Modificar(int viejo, int nuevo) {
    Elimina_balanceado(viejo); // Eliminar el viejo
    Insertar(nuevo); // Insertar el nuevo
}

void Arbol::Equilibrar(pArbol a, pNodo nodo, int rama, int nuevo) {
    int salir = FALSE;

    while (nodo && !salir) {
        if (nuevo) {
            if (rama == IZQUIERDO) {
                nodo->FE -= 1;
            } else {
                nodo->FE += 1;
            }
        } else {
            if (rama == IZQUIERDO) {
                nodo->FE += 1;
            } else {
                nodo->FE -= 1;
            }
        }

        if (nodo->FE == 0) {
            salir = TRUE;
        } else if (nodo->FE == 2) {
            if (nodo->derecho->FE == 1) {
                RotaDerechaDerecha(a, nodo);
            } else {
                RotaDerechaIzquierda(a, nodo);
            }
            salir = TRUE;
        } else if (nodo->FE == -2) {
            if (nodo->izquierdo->FE == -1) {
                RotaIzquierdaIzquierda(a, nodo);
            } else {
                RotaIzquierdaDerecha(a, nodo);
            }
            salir = TRUE;
        }

        nodo = nodo->padre;
    }
}

//funciones de rotacion
// RotaDerechaDerecha, RotaIzquierdaIzquierda, RotaDerechaIzquierda, RotaIzquierdaDerecha

void Arbol::RotaDerechaDerecha(pArbol a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo B = Q->izquierdo;

    if (Padre) {
        if (Padre->derecho == P) {
            Padre->derecho = Q;
        } else {
            Padre->izquierdo = Q;
        }
    } else {
        //Si no tiene padre, se actualiza la raíz del arbol
        setRaiz(Q);
    }

    P->derecho = B;
    Q->izquierdo = P;

    P->padre = Q;
    
    if (B) {
        B->padre = P;
    } 
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}


void Arbol::RotaIzquierdaIzquierda(pArbol a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo B = Q->derecho;

    if (Padre){
        if (Padre->derecho == P){
            Padre->derecho = Q;
        }
        else {
            Padre->izquierdo = Q;
        }
    }
    else
        setRaiz(Q);

    P->izquierdo = B;
    Q->derecho = P;

    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    P->FE = 0;
    Q->FE = 0;
}

void Arbol::RotaDerechaIzquierda(pArbol a, pNodo nodo) {
    pNodo Padre = nodo->padre;
    pNodo P = nodo;
    pNodo Q = P->derecho;
    pNodo R = Q->izquierdo;
    pNodo B = R->izquierdo;
    pNodo C = R->derecho;

    if (Padre){
        if (Padre->derecho == nodo){
            Padre->derecho = R;
        } else {
            Padre->izquierdo = R;
        }
    }
    else
        setRaiz(R);

    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    switch (R->FE) {
        case -1: P->FE = 0; Q->FE = 1; break;
        case 0: P->FE = 0; Q->FE = 0; break;
        case 1: P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

void Arbol::RotaIzquierdaDerecha(pArbol a, pNodo nodo) {
    pNodo P = nodo;
    pNodo Q = P->izquierdo;
    pNodo R = Q->derecho;
    pNodo A = R->izquierdo;
    pNodo B = R->derecho;

    P->izquierdo = B;
    Q->derecho = A;

    if (B) {
        B->padre = P;
    }
    if (A) {
        A->padre = Q;
    }
    
    R->izquierdo = P;
    R->derecho = Q;

    if (P->padre) {
        if (P->padre->derecho == P) {
            P->padre->derecho = R;
        } else {
            P->padre->izquierdo = R;
        }
    } else {
        setRaiz(R);
    }

    Q->padre = R;
    P->padre = R;
    R->padre = P->padre;

    Q->FE = 0;
    P->FE = 0;
}

// Función auxiliar
void Arbol::Elimina_balanceado(pNodo* nodo, bool& bo, int infor) {
    if (*nodo == nullptr) {
        std::cout << "La información no se encuentra en el árbol" << std::endl;
        bo = false; // Cambiado para que 'bo' sea falso si no se encuentra el nodo
        return;
    }

    if (infor < (*nodo)->dato) {
        Elimina_balanceado(&((*nodo)->izquierdo), bo, infor);
        if (bo) {
            reestructura_der(nodo, bo);
        }
    } else if (infor > (*nodo)->dato) {
        Elimina_balanceado(&((*nodo)->derecho), bo, infor);
        if (bo) {
            reestructura_izq(nodo, bo);
        }
    } else {
        // Nodo encontrado, proceder con la eliminación
        pNodo temp = *nodo;
        bool aux = true;

        if ((*nodo)->izquierdo == nullptr) {
            *nodo = (*nodo)->derecho; // Tomamos el derecho si no hay izquierdo
            bo = true;
            delete temp;
        } else if ((*nodo)->derecho == nullptr) {
            *nodo = (*nodo)->izquierdo; // Tomamos el izquierdo si no hay derecho
            bo = true;
            delete temp;
        } else {
            // Encontrar el nodo más a la izquierda del subárbol derecho
            temp = (*nodo)->derecho;
            while (temp->izquierdo != nullptr) {
                temp = temp->izquierdo;
            }

            (*nodo)->dato = temp->dato; // Reemplazar el dato
            Elimina_balanceado(&(*nodo)->derecho, bo, temp->dato);
            if (bo) {
                reestructura_izq(nodo, bo);
            }
        }
    }
}

// Función pública
void Arbol::Elimina_balanceado(int infor) {
    bool bo = false; // Bandera para indicar si se eliminó un nodo
    Elimina_balanceado(&raiz, bo, infor); // Llama a la función auxiliar
}

// Funciones auxiliares de reestructuracin para mantener el balance
void Arbol::reestructura_izq(pNodo *&nodo, bool &bo) {
    if (bo) {
        if ((*nodo)->FE == 0) {
            (*nodo)->FE = -1;
            bo = false;
        } else if ((*nodo)->FE == 1) {
            (*nodo)->FE = 0;
        } else {
            //Reestructuracion del arbol
            Nodo* nodo1 = (*nodo)->derecho;
            if (nodo1->FE >= 0) { //Rotacion DD
                (*nodo)->derecho = nodo1->izquierdo;
                nodo1->izquierdo = *nodo;
                if (nodo1->FE == 0) {
                    (*nodo)->FE = 1;
                    nodo1->FE = -1;
                    bo = false;
                } else {
                    (*nodo)->FE = 0;
                    nodo1->FE = 0;
                }
                *nodo = nodo1;
            } else { // Rotación DI
                Nodo* nodo2 = nodo1->izquierdo;
                nodo1->izquierdo = nodo2->derecho;
                nodo2->derecho = nodo1;
                (*nodo)->derecho = nodo2->izquierdo;
                nodo2->izquierdo = *nodo;
                
                if (nodo2->FE == 1) {
                    (*nodo)->FE = -1;
                } else {
                    (*nodo)->FE = 0;
                }

                if (nodo2->FE == -1) {
                    nodo1->FE = 1;
                } else {
                    nodo1->FE = 0;
                }
                *nodo = nodo2;
                nodo2->FE = 0;
            }
        }
    }
}

//Función de reestructuración derecha
void Arbol::reestructura_der(pNodo *&nodo, bool &bo) {
    if (bo) {
        if ((*nodo)->FE == 0) {
            (*nodo)->FE = 1;
            bo = false;
        } else if ((*nodo)->FE == -1) {
            (*nodo)->FE = 0;
        } else {
            // Reestructuración del árbol
            Nodo* nodo1 = (*nodo)->izquierdo;
            if (nodo1->FE <= 0) { // Rotación II
                (*nodo)->izquierdo = nodo1->derecho;
                nodo1->derecho = *nodo;
                if (nodo1->FE == 0) {
                    (*nodo)->FE = -1;
                    nodo1->FE = 1;
                    bo = false;
                } else {
                    (*nodo)->FE = 0;
                    nodo1->FE = 0;
                }
                *nodo = nodo1;
            } else { // Rotación ID
                Nodo* nodo2 = nodo1->derecho;
                nodo1->derecho = nodo2->izquierdo;
                nodo2->izquierdo = nodo1;
                (*nodo)->izquierdo = nodo2->derecho;
                nodo2->derecho = *nodo;

                if (nodo2->FE == -1) {
                    (*nodo)->FE = 1;
                } else {
                    (*nodo)->FE = 0;
                }

                if (nodo2->FE == 1) {
                    nodo1->FE = -1;
                } else {
                    nodo1->FE = 0;
                }
                *nodo = nodo2;
                nodo2->FE = 0;
            }
        }
    }
}


void Arbol::GenerarGrafo() {
    std::ofstream fp("grafo1.txt"); // Archivo donde se generará el grafo
    if (fp.is_open()) {
        fp << "digraph Arbol {\n";
        PreOrden(fp); // Generar el grafo en formato DOT
        fp << "}\n";
        fp.close();

        // Comando para generar la imagen del grafo usando Graphviz
        system("dot -Tpng grafo.dot -o grafo.png");
        cout << "Grafo generado en 'grafo.png'." << endl;
    } else {
        cout << "No se pudo crear el archivo de grafo." << endl;
    }
}

void Arbol::PreOrden(std::ofstream &fp) {
    if (raiz) {
        fp << raiz->dato << ";\n";
        if (raiz->izquierdo) {
            fp << raiz->dato << " -> " << raiz->izquierdo->dato << ";\n";
            Arbol::PreOrden(fp); // Llamada recursiva al hijo izquierdo
        }
        if (raiz->derecho) {
            fp << raiz->dato << " -> " << raiz->derecho->dato << ";\n";
            Arbol::PreOrden(fp); // Llamada recursiva al hijo derecho
        }
    }
}

int main() {
    Arbol arbol; // Crear instancia del árbol
    arbol.MenuPrincipal(); //Ejecutar el menu principal
    return 0; // Salir
}