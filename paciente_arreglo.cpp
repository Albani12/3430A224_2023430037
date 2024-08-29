#include <iostream>

// Define una estructura nombre "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;
    double altura;
};

int main() {

    // Crea una matriz de 3 objetos tipo pacientes
    Paciente pacientes[3];

    // Inicializa la matriz de elementos
    pacientes[0].nombre = "Diana";
    pacientes[0].edad = 25;
    pacientes[0].peso = 40;
    pacientes[0].altura = 1.55;

    pacientes[1].nombre = "Emiliano";
    pacientes[1].edad = 37;
    pacientes[1].peso = 62.7;
    pacientes[1].altura = 1.85;

    pacientes[2].nombre = "Yonnathan";
    pacientes[2].edad = 30;
    pacientes[2].peso = 70.5;
    pacientes[2].altura = 1.70;

    // Accede e imprime la información desde la matriz
    for (int i = 0; i < 3; ++i) {
        std::cout << "Nombre: " << pacientes[i].nombre << std::endl;
        std::cout << "Edad: " << pacientes[i].edad << std::endl;
        std::cout << "Peso: " << pacientes[i].peso << std::endl;
        std::cout << "Altura: " << pacientes[i].altura << std::endl;
        std::cout << std::endl;
    }
    return 0;
}
