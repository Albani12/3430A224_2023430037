#include <iostream>

class Pila {
private:
    int max;            //Capacidad maxima de la pila
    int tope;           //indice del elemento superior de la pila
    int datos[100];     //arreglo estatico para almacenar los elementos
    bool band;          //indica el estado de la pila

public:
    //constructor que inicializa la pila con el tamaño maximo especificado
    Pila(int maximo) {
        max = maximo;
        tope = -1;      //La pila inicialmente vacia
        band = false;   //indica que la pila no esta en un estado de error
    }
    //Metodo para verificar si la pila esta vacia
    bool pila_vacia() {
        return tope == -1;
    }

    //metodo para verificar si la pila está llena
    bool pila_llena() {
        return tope == max - 1;
    }

    //metodo para apilar (push) un elemento en la pila
    void push(int dato) {
        if (pila_llena()) {
            std::cout << "Error: la pila ya esta llena" << std::endl;
            band = true; //Indica que hubo un error al intentar apilar
        } else {
            datos[++tope] = dato;
            std::cout << "Elemento " << dato << " apilado "<< std::endl;
            band = false; //Apila correctamente
        }
    }

    //Metodo para desapilar (pop) un elemento de la pila
    void pop() {
        if (pila_vacia()) {
            std::cout << "Error: la pila esta vacia"<< std::endl;
            band = true; // Indicamos que hubo un error al intentar desapilar
        } else {
            std::cout << "Elemento eliminado: " << datos[tope] << std::endl;
            tope--;
            band = false; //No hay error al desapilar
        }
    }

    //Metodo para mostrar todos los elementos de la pila
    void mostrar() {
        if (pila_vacia()) {
            std::cout << "La pila está vacia" << std::endl;
        } else {
            std::cout << "Elementos en la pila:" << std::endl;
            for (int i = tope; i >= 0; --i) {
                std::cout << datos[i] << std::endl;
            }
        }
    }
};

int main() {
    int maximo;
    std::cout << "Ingrese tamano Maximo de la Pila: ";
    std::cin >> maximo;

    //crea la pila con el tamaño máximo ingresado por el usuario
    Pila pila(maximo);

    int opcion = -1; //Inicializar con un valor que no es de salida
    int valor;

    //while para el ciclo del menu
    while (opcion != 0) {
        //menu de opciones
        std::cout << "Agregar/push [1] " << std::endl;
        std::cout << "Remover/pop [2] " << std::endl;
        std::cout << "Ver pila [3] " << std::endl;
        std::cout << "Salir [0] " << std::endl;
        std::cout << "Opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: //agregar/push
                if (!pila.pila_llena()) {
                    std::cout << "Ingrese valor: ";
                    std::cin >> valor;
                    pila.push(valor);
                } else {
                    std::cout << "Error: la pila está llena. " << std::endl;
                }
                break;

            case 2: //Remover/pop
                pila.pop();
                break;

            case 3: //ver pila
                pila.mostrar();
                break;

            case 0: //Salir
                std::cout << "Saliendo del programa..." << std::endl;
                break;

            default:
                std::cout << "Opción no válida. " << std::endl;
        }
    }

    return 0;
}