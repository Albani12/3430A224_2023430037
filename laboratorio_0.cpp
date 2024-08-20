#include <iostream>
#include <string>

//Funcion que determina si un numero es par
bool par(int numero) {
    return numero % 2 == 0;  // % Calcula el residuo de la división de dos números enteros
}

//Funcion que determina la longitud de una cadena
int longitudCadena(const std::string& str) {
    return str.length();
}

int main() {
    //Leer un numero desde la entrada estandar
    int numero;
    std::cout << "Ingresa un numero: "; //salida estandar en consola
    std::cin >> numero;   //lee los datos de la entrada de la consola ingresado por el usuario
                          //se almacena en la variable numero

    //Imprimir el numero ingresado
    std::cout << "Numero ingresado: " << numero <<std::endl;

    //Usar la funcion "par" para el numero ingreso
    if (par(numero)) {
        std::cout << "El numero " <<numero << " es par" <<std::endl;
    } else {
        std::cout << "El numero " <<numero << " es impar" <<std::endl;
    }

    //usar la funcion par para todos los numeros del 1 al 10
    for (int i=1; i <=10; ++i) {
        if (par(i)) {
            std::cout << "El numero " <<i << " es par" << std::endl;
        } else {
            std::cout << "El numero " <<i << " es impar" << std::endl;
        }
    }

    //Solicitar una cadena de texto al usuario
    std::string cadenaUsuario;
    std::cout << "Ingresa una cadena de texto: ";
    std::cin.ignore(); //Limpiar buffer de entrada
    std::getline(std::cin, cadenaUsuario);

    //Usar la funcion longitudCadena para la cadena ingresada por el usuario
    int longitudUsario = longitudCadena(cadenaUsuario);
    std::cout << "La longitud de la cadena de texto ingresada por el usuario es: " <<longitudUsario<< std::endl;

    // //Cadena almacenada en el codigo
    std::string cadenaFija= "Cadena de ejemplo";
    int longitudFija = longitudCadena(cadenaFija);
    std::cout << "La longitud de la cadena fija es: " <<longitudFija<< std::endl;

    std::cout << "La longitud de la cadena fija es: " <<longitudFija<< std::endl;


    return 0;
}