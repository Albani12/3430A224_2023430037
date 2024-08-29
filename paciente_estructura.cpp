#include <iostream>

// Define una estructura nombre "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;
    double altura;
};

int main() {

    //Crear ejemplos de pacientes
    Paciente paciente1 = {"Diana", 25, 40, 1.55};
    Paciente paciente2 = {"Emiliano", 37, 62.7, 1.85};
    Paciente paciente3 = {"Yonnathan", 30, 70.5, 1.70};

    //Muestra informacion de cada paciente
    //Peso en kg
    //Altura en cm
    
    std::cout << "Paciente 1: " << std::endl;
    std::cout << "Nombre: " << paciente1.nombre << std::endl;
    std::cout << "Edad: " << paciente1.edad << std::endl;
    std::cout << "Peso: " << paciente1.peso << std::endl;
    std::cout << "Altura: " << paciente1.altura << std::endl;
    std::cout << std::endl;

    std::cout << "Paciente 2: " << std::endl;
    std::cout << "Nombre: " << paciente2.nombre << std::endl;
    std::cout << "Edad: " << paciente2.edad << std::endl;
    std::cout << "Peso: " << paciente2.peso << std::endl;
    std::cout << "Altura: " << paciente2.altura << std::endl;
    std::cout << std::endl;

    std::cout << "Paciente 3: " << std::endl;
    std::cout << "Nombre: " << paciente3.nombre << std::endl;
    std::cout << "Edad: " << paciente3.edad << std::endl;
    std::cout << "Peso: " << paciente3.peso << std::endl;
    std::cout << "Altura: " << paciente3.altura << std::endl;
    std::cout << std::endl;

    return 0;
}
