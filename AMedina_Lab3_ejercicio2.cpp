#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Contenedor {
    int numero;         //identificador del contenedor
    string empresa;     //empresa dueña del contenedor

    //inicializa un contenedor con un número y un nombre de empresa
    Contenedor(int num, string emp) : numero(num), empresa(emp) {}
};

class Puerto { //puerto con multiples pilas de contenedores
private:
    stack<Contenedor> *pilas; //Array de pilas de contenedores
    int maxPilas;       //max de pilas 
    int maxAltura;      //capacidad de cada pila

public:
    Puerto(int m, int n) : maxPilas(m), maxAltura(n) {   //m pilas y n altura
        pilas = new stack<Contenedor>[maxPilas]; //crear arreglo dinamico de pilas
    }

    void ingresarContenedor(int numero, string empresa) {
        //el ciclo recorre las pilas para encontar un espacio disponible
        for (int i = 0; i < maxPilas; ++i) {
            if (pilas[i].size() < maxAltura) {  //menos contenedores que la altura maxima
                pilas[i].push(Contenedor(numero, empresa));
                cout << "Contenedor " << numero << "/" << empresa << " ingresado en la pila " << i + 1 << std::endl;
                return;
            }
        }

        cout << "No hay espacio para ingresar mas contenedores. " << std::endl; //todas las pilas estan llenas
    }

    void retirarContenedor(int numero, string empresa) {
        for (int i = 0; i < maxPilas; ++i) {
            stack<Contenedor> temp; //pila temporal para mover contenedores mientras se busca
            bool encontrado = false; //para saber si se encontró el contenedor
            //recorre la pila y busca el contenedor
            while (!pilas[i].empty()) {
                Contenedor top = pilas[i].top();
                pilas[i].pop();
                if (top.numero == numero && top.empresa == empresa) {
                    cout << "Contenedor " << numero << "/" << empresa << " retirado de la pila " << i + 1 << std::endl;
                    encontrado = true;
                    break;
                } else {
                    temp.push(top); // si no es el que busca, lo mueve a la pila temporal
                }
            }
            //restaurar la pila original o mover los contenedores a otras pilas si fue encontrado
            if (encontrado) {
                restaurarContenedores(temp);
                return;
            } else {
                //mueve los contenedores de la pila temporal a las pilas originales
                restaurarContenedores(temp, i);
            }
        }
        cout << "Contenedor " << numero << "/" << empresa << " no encontrado. " << std::endl;
    }

    void restaurarContenedores(stack<Contenedor> &temp, int exclude = -1) {
        //mover contenedores desde la pila temporal a las pilas disponibles
        while (!temp.empty()) {
            Contenedor cont = temp.top();
            temp.pop();

            //Recorre todas las pilas para encontrar una con espacio disponible
            for (int i = 0; i < maxPilas; ++i) {
                if (i == exclude) continue;     //omite la pila excluida (de donde se retiro originalmente)
                if (pilas[i].size() < maxAltura) {
                    pilas[i].push(cont);
                    cout << "Moviendo contenedor " << cont.numero << "/" << cont.empresa << " a pila " << i + 1 << ".\n";
                    break;
                }
            }
        }
    }

    //estado actual de todas las pilas en el puerto
    void mostrarEstado() {
        cout << "Estado actual de las pilas: " << std::endl;
        //recorre todas las pilas y muestra sus contenedores
        for (int i = 0; i < maxPilas; ++i) {
            cout << "Pila " << i + 1 << ": ";
            stack<Contenedor> temp = pilas[i];
            //Muestra todos los contenedores de la pila actual
            while (!temp.empty()) {
                Contenedor cont = temp.top();
                cout << cont.numero << "/" << cont.empresa << " ";
                temp.pop();
            }
            cout << endl;
        }
    }
};

int main() {
    int m, n;
    cout << "Ingrese el numero de pilas (m): ";
    cin >> m;
    cout << "Ingrese la altura maxima de cada pila (n): ";
    cin >> n;

    Puerto puerto(m, n);

    //ejemplo de operaciones, ingreso manual
    puerto.ingresarContenedor(1, "EMP1"); //añade un contenedor con numero 1 y empresa "EMP1"
    puerto.ingresarContenedor(2, "EMP2");
    puerto.ingresarContenedor(3, "EMP3");
    puerto.mostrarEstado();
    puerto.retirarContenedor(1, "EMP1");
    puerto.mostrarEstado();

    return 0;
}
