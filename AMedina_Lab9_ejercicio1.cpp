#include <iostream>
#include <string>

const int TAMANO_TABLA = 20; //tamaño maximo de la tabla hash

//Funcion hash primaria
int funcionHash(int clave) {
    return clave % TAMANO_TABLA;
}

//Segunda funcion hash para el metodo de Doble Hashing
int segundaFuncionHash(int clave) {
    return 7 - (clave % 7);
}

class TablaHash {
private:
    int tabla[TAMANO_TABLA];
    std::string metodo;

public:
    TablaHash(const std::string& metodoColision) : metodo(metodoColision) {
        for (int i = 0; i < TAMANO_TABLA; i++) {
            tabla[i] = -1;  //inicializa la tabla en -1 para indicar posiciones vacias
        }
    }

    //Funcion para insertar una clave en la tabla hash segun el metodo de resolución de colisiones
    void insertar(int clave) {
        int indiceHash = funcionHash(clave);
        int indiceOriginal = indiceHash;
        int i = 0;

        while (tabla[indiceHash] != -1) {
            std::cout << "Colision en indice " << indiceHash << " para clave " << clave << "\n";
            if (metodo == "L") {
                indiceHash = (indiceOriginal + i) % TAMANO_TABLA; //prueba lineal
                std::cout << "Desplazamiento aplicado: +" << i << "\n";
            } else if (metodo == "C") {
                indiceHash = (indiceOriginal + i * i) % TAMANO_TABLA; //prueba cuadratica
                std::cout << "Desplazamiento cuadratico aplicado: +" << i * i << "\n";
            } else if (metodo == "D") {
                indiceHash = (indiceOriginal + i * segundaFuncionHash(clave)) % TAMANO_TABLA; //Doble direccion hash
                std::cout << "Desplazamiento doble direccion hash aplicado: +" << i * segundaFuncionHash(clave) << "\n";
            }
            i++;
            if (i >= TAMANO_TABLA) {
                std::cout << "Tabla llena. No se pudo insertar " << clave << ".\n";
                return;
            }
        }

        tabla[indiceHash] = clave;
        std::cout << "Clave " << clave << " insertada en indice " << indiceHash <<  " con desplazamiento final: +" << (indiceHash - indiceOriginal + TAMANO_TABLA) % TAMANO_TABLA << "\n";
        imprimirTabla();
    }

    //Funcion para buscar una clave en la tabla hash
    void buscar(int clave) {
        int indiceHash = funcionHash(clave);
        int indiceOriginal = indiceHash;
        int i = 0;

        while (tabla[indiceHash] != -1) {
            if (tabla[indiceHash] == clave) {
                std::cout << "Clave " << clave << " encontrada en indice " << indiceHash << " con desplazamiento final: +" << (indiceHash - indiceOriginal + TAMANO_TABLA) % TAMANO_TABLA << "\n";
                return;
            }
            std::cout << "Colision en indice " << indiceHash << " durante la busqueda de la clave " << clave << "\n";
            if (metodo == "L") {
                indiceHash = (indiceOriginal + i) % TAMANO_TABLA;
                std::cout << "Desplazamiento aplicado: +" << i << "\n";
            } else if (metodo == "C") {
                indiceHash = (indiceOriginal + i * i) % TAMANO_TABLA;
                std::cout << "Desplazamiento cuadratico aplicado: +" << i * i << "\n";
            } else if (metodo == "D") {
                indiceHash = (indiceOriginal + i * segundaFuncionHash(clave)) % TAMANO_TABLA;
                std::cout << "Desplazamiento doble hashing aplicado: +" << i * segundaFuncionHash(clave) << "\n";
            }
            i++;
            if (i >= TAMANO_TABLA) {
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

    int numClaves;
    std::cout << "Ingrese la cantidad de claves a insertar (maximo 100): ";
    std::cin >> numClaves;

    if (numClaves < 1 || numClaves > TAMANO_TABLA) {
        std::cerr << "Cantidad inválida. Debe ser entre 1 y " << TAMANO_TABLA << ".\n";
        return 1;
    }

    for (int i=0; i < numClaves; i++) {
        int clave;
        std::cout << "Ingresa la clave #" << (i+1) << ":";
        std::cin >> clave;
        tablaHash.insertar(clave);
    }

    int claveBuscar;
    std::cout << "Ingrese una clave para buscar (-1 para salir): ";
    while (std::cin >> claveBuscar && claveBuscar != -1) {
        tablaHash.buscar(claveBuscar);
        std::cout << "Ingrese otra clave para buscar (-1 para salir): ";
    }

    return 0;
}
