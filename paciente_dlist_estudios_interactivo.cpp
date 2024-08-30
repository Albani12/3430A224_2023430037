#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Definición de la estructura "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;   // en kilogramos
    double altura; // en metros
    Paciente* next;
};

// Función para agregar un nuevo paciente a la lista
void addPaciente(Paciente*& head, const std::string& nombre, int edad,double peso, double altura) {
    Paciente* newPaciente = new Paciente();
    newPaciente->nombre = nombre;
    newPaciente->edad = edad;
    newPaciente->peso = peso;
    newPaciente->altura = altura;
    newPaciente->next = head;
    head = newPaciente;
}

// Función para eliminar a una persona de la lista por su nombre
void removePaciente(Paciente*& head, const std::string& nombre) {
    Paciente* current = head;
    Paciente* previous = nullptr;

    while (current != nullptr && current->nombre != nombre) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous == nullptr) {
            head = current->next;
        } else {
            previous->next = current->next;
        }
        delete current;
    }
}

// Función para imprimir todas los pacientes en la lista.
void printPaciente(const Paciente* head) {
    const Paciente* current = head;
    while (current != nullptr) {
        std::cout << "Nombre: "<< current->nombre << ",edad " << current->edad << " anos, Peso: " << current->peso << "kg, Altura: "<< current -> altura << std::endl;
        current = current->next;
    }
}

// Funcion para calcular el promedio de edad y peso del grupo de pacientes
void calcularPromedios(const Paciente* head, double& promedioEdad, double& promedioPeso) {
    const Paciente* current = head;
    int contador =0;
    double sumaEdad = 0;
    double sumaPeso = 0;

    while (current != nullptr) {
        sumaEdad += current -> edad;
        sumaPeso += current->peso;
        contador ++;
        current = current -> next;
    }

    if (contador > 0){
        promedioEdad = sumaEdad/contador;
        promedioPeso = sumaPeso/contador;
    } else {
        promedioEdad = 0;
        promedioPeso = 0;
    }
}

// Función para calcular y mostrar el IMC de cada paciente
void calcularIMC(const Paciente* head) {
    const Paciente* current = head;
    while (current != nullptr) {
        double imc = current->peso / (current->altura * current->altura);
        std::cout << "IMC de " << current->nombre << ": " << imc;
        if (imc < 18.5) {
            std::cout << " (Bajo peso)";
        } else if (imc >= 18.5 && imc < 24.9) {
            std::cout << " (Peso normal)";
        } else if (imc >= 25 && imc < 29.9) {
            std::cout << " (Sobrepeso)";
        } else {
            std::cout << " (Obesidad)";
        }
        std::cout << std::endl;
        current = current->next;
    }
}

// Función para cargar datos de pacientes desde un archivo de texto plano
void cargarDesdeArchivo(Paciente*& head) {
    std::string nombreArchivo = "pacientes.txt"; // Nombre del archivo codificado
    std::ifstream archivo(nombreArchivo);

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre;
        int edad;
        double peso, altura;

        std::getline(ss, nombre, ',');
        ss >> edad;
        ss.ignore(); // Ignorar la coma
        ss >> peso;
        ss.ignore(); // Ignorar la coma
        ss >> altura;

        addPaciente(head, nombre, edad, peso, altura);
    }

    archivo.close();
}

// Menú interactivo para gestionar pacientes
void menu() {
    Paciente* head = nullptr;
    int opcion;
    std::string nombre;
    int edad;
    double peso; 
    double altura;

    do {
        std::cout << "Menu de Gestion de Pacientes" << std::endl;
        std::cout << "1. Agregar paciente" << std::endl;
        std::cout << "2. Eliminar paciente" << std::endl;
        std::cout << "3. Mostrar lista de pacientes" << std::endl;
        std::cout << "4. Calcular promedios de edad y peso" << std::endl;
        std::cout << "5. Calcular IMC de cada paciente" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion: "<< std::endl;
        std::cin >> opcion;

        //Ingreso manual por el usuario
        switch (opcion) {
            case 1:
                std::cout << "Ingrese nombre: ";
                std::cin >> nombre;
                std::cout << "Ingrese edad: ";
                std::cin >> edad;
                std::cout << "Ingrese peso: ";
                std::cin >> peso;
                std::cout << "Ingrese altura: ";
                std::cin >> altura;
                addPaciente(head, nombre, edad, peso, altura);
                break;
            case 2:
                std::cout << "Ingrese nombre del paciente a eliminar: ";
                std::cin >> nombre;
                removePaciente(head, nombre);
                break;
            case 3:
                printPaciente(head);
                break;
            case 4:
                double promedioEdad, promedioPeso;
                calcularPromedios(head, promedioEdad, promedioPeso);
                std::cout << "Promedio de Edad: " << promedioEdad << " anos"<< std::endl;
                std::cout << "Promedio de Peso: " << promedioPeso << " kg"<< std::endl;
                break;
            case 5:
                calcularIMC(head);
                break;
            case 0:
                std::cout << "Saliendo del programa" << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 0);

    // Liberar la memoria asignada
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    menu();
    return 0;
}