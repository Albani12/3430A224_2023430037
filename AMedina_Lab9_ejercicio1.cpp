#include <iostream>
#include <string>

const int TAMANO_TABLA = 100; //tamaño maximo de la tabla hash

//Funcion hash primaria que calcula el indice a partir de una clave
int funcionHash(int clave) {
    return clave % TAMANO_TABLA;
}

//Segunda funcion hash para el metodo de Doble Hash
int segundaFuncionHash(int clave) {
    return 7 - (clave % 7); // 7, numero primo
}

class TablaHash {
private:
    int tabla[TAMANO_TABLA];
    std::string metodo;

public:
    //constructor que inicializa la table y selecciona el metodo de solucion de colision
    TablaHash(const std::string& metodoColision) : metodo(metodoColision) {
        for (int i = 0; i < TAMANO_TABLA; i++) {
            tabla[i] = -1;  //inicializa la tabla en -1 para indicar posiciones vacias
        }
    }

    //Funcion para insertar una clave en la tabla hash segun el metodo de solucion de colisiones especificado
    void insertar(int clave) {
        int indiceHash = funcionHash(clave); //calcula el indice inicial usando la funcion hash
        int indiceOriginal = indiceHash;    //guarda el indice original para referencia
        int i = 0;  //contador de intentos en cason de colision

        //ciclo para menjar colisiones segun cada metodo
        while (tabla[indiceHash] != -1) {   //mientras el indice este ocupado se aplica desplazamiento
            std::cout << "Colision en indice " << indiceHash << " para clave " << clave << "\n";
            if (metodo == "L") {    //prueba lineal
                indiceHash = (indiceOriginal + i) % TAMANO_TABLA; //prueba lineal
                std::cout << "Desplazamiento aplicado: +" << i << "\n";
            } else if (metodo == "C") {     //prueba cuadratica
                indiceHash = (indiceOriginal + i * i) % TAMANO_TABLA; //prueba cuadratica
                std::cout << "Desplazamiento cuadratico aplicado: +" << i * i << "\n";
            } else if (metodo == "D") {     //doble direccion hash
                indiceHash = (indiceOriginal + i * segundaFuncionHash(clave)) % TAMANO_TABLA; //Doble direccion hash
                std::cout << "Desplazamiento doble direccion hash aplicado: +" << i * segundaFuncionHash(clave) << "\n";
            }
            i++;
            if (i >= TAMANO_TABLA) {    //verifica si se ha recorrido toda la tabla
                std::cout << "Tabla llena. No se pudo insertar " << clave << ".\n";
                return;
            }
        }

        //ahora inserta la clave en la posicion libre
        tabla[indiceHash] = clave;
        std::cout << "Clave " << clave << " insertada en indice " << indiceHash <<  " con desplazamiento final: +" << (indiceHash - indiceOriginal + TAMANO_TABLA) % TAMANO_TABLA << "\n";
        imprimirTabla();
    }

    //Funcion para buscar una clave en la tabla hash
    void buscar(int clave) {
        int indiceHash = funcionHash(clave);    //clacula el indice inicial con la funcion hash
        int indiceOriginal = indiceHash;    //guarda el indice original
        int i = 0;  //contador de intentos en caso de cada colision

        //ciclo para buscar la clave aplicando desplazamientos si hay colisiones
        while (tabla[indiceHash] != -1) {   //mientras el indice no este vacio
            if (tabla[indiceHash] == clave) {   //si la clave se encuentra, se muestra el indice
                std::cout << "Clave " << clave << " encontrada en indice " << indiceHash << " con desplazamiento final: +" << (indiceHash - indiceOriginal + TAMANO_TABLA) % TAMANO_TABLA << "\n";
                return;
            }
            std::cout << "Colision en indice " << indiceHash << " durante la busqueda de la clave " << clave << "\n";
            if (metodo == "L") {    //prueba lineal
                indiceHash = (indiceOriginal + i) % TAMANO_TABLA;
                std::cout << "Desplazamiento aplicado: +" << i << "\n";
            } else if (metodo == "C") {     //prueba cuadratica
                indiceHash = (indiceOriginal + i * i) % TAMANO_TABLA;
                std::cout << "Desplazamiento cuadratico aplicado: +" << i * i << "\n";
            } else if (metodo == "D") {     //doble direccion hash
                indiceHash = (indiceOriginal + i * segundaFuncionHash(clave)) % TAMANO_TABLA;
                std::cout << "Desplazamiento doble hashing aplicado: +" << i * segundaFuncionHash(clave) << "\n";
            }
            i++;
            if (i >= TAMANO_TABLA) {    //si se recorre toda la tabla sin encntrarla entonces la clave no esta
                std::cout << "Clave " << clave << " no encontrada.\n";
                return;
            }
        }
        
        std::cout << "Clave " << clave << " no encontrada.\n";
    }

    //funcion para imprimir el contenido de la tabla hash
    void imprimirTabla() const {
        std::cout << "Tabla Hash:\n";
        for (int i = 0; i < TAMANO_TABLA; i++) {
            std::cout << i << ": " << (tabla[i] == -1 ? "vacio" : std::to_string(tabla[i])) << "\n";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) { 
        std::cerr << "Uso: ./hash {L|C|D}\n";
        return 1;
    }

    //verificacion del metodo ingresado en pantalla
    std::string metodo = argv[1];
    if (metodo != "L" && metodo != "C" && metodo != "D") {
        std::cerr << "Metodo invalido. Use 'L' para Prueba Lineal, 'C' para Prueba Cuadratica o 'D' para Doble direccion Hash.\n";
        return 1;
    }

    TablaHash tablaHash(metodo);

    //probando con el arreglo de 20 elementos dado en la guia:
    // int claves[] = {23, 42, 5, 66, 14, 43, 59, 81, 37, 49, 28, 55, 94, 80, 64};
    // int numClaves = sizeof(claves) / sizeof(claves[0]);

    // std::cout << "Insertando claves:\n";
    // for (int i = 0; i < numClaves; i++) {
    //     tablaHash.insertar(claves[i]);
    // }

    //el usuario ingresa el numero de claves a insertar
    int numClaves;
    std::cout << "Ingrese la cantidad de claves a insertar (maximo 100): ";
    std::cin >> numClaves;

    if (numClaves < 1 || numClaves > TAMANO_TABLA) {
        std::cerr << "Cantidad inválida. Debe ser entre 1 y " << TAMANO_TABLA << ".\n";
        return 1;
    }

    //inserta cada clave ingresada por el usuario
    for (int i=0; i < numClaves; i++) {
        int clave;
        std::cout << "Ingresa la clave #" << (i+1) << ":";
        std::cin >> clave;
        tablaHash.insertar(clave);
    }

    //solicita al usuario una clave para buscar en la tabla hash
    int claveBuscar;
    std::cout << "Ingrese una clave para buscar (-1 para salir): ";
    while (std::cin >> claveBuscar && claveBuscar != -1) {
        tablaHash.buscar(claveBuscar);
        std::cout << "Ingrese otra clave para buscar (-1 para salir): ";
    }

    return 0;
}
