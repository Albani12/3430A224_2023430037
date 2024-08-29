#include <iostream>
#include <string>

// Define una estructura nombre "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;   // en kilogramos
    double altura; // en metros
    Paciente* next;
};

// Función para agregar una nueva persona a la lista
void addPaciente(Paciente*& head, const std::string& nombre, int edad,double peso, double altura) {
    Paciente* newPaciente = new Paciente();
    newPaciente->nombre = nombre;
    newPaciente->edad = edad;
    newPaciente->peso = peso;
    newPaciente->altura = altura;
    newPaciente->next = head;
    head = newPaciente;
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

// Funcion para calcular y mostar IMC de cada paciente
void calcularIMC(const Paciente* head) {
    const Paciente* current = head;
    while (current != nullptr){
        double imc = current->peso / (current->altura * current->altura);
        std::cout << "El IMC de " << current->nombre << ":" << imc;
        if (imc < 18.5) {
            std::cout << " Bajo peso";
        } else if (imc >= 18.5 && imc < 24.9) {
            std::cout << " Peso normal"; 
        } else if (imc >= 25 && imc < 29.9) {
            std::cout << " Sobrepeso";
        } else {
            std::cout << " Obesidad";
        }
        std::cout << std::endl;
        current = current->next;
    }
}

int main() {
    Paciente* head = nullptr;

    // Agregar pacientes a la lista
    addPaciente(head, "Diana", 25, 40, 1.55);
    addPaciente(head, "Emiliano", 37, 100, 1.85);
    addPaciente(head, "Yonnathan", 30, 70.5, 1.70);

    // imprimir la lista
    printPaciente(head);

    // Calcular y mostrar los promedios
    double promedioEdad = 0;
    double promedioPeso = 0;
    calcularPromedios(head, promedioEdad, promedioPeso);
    std::cout << "Promedio de edad: " << promedioEdad << " anos" << std::endl;
    std::cout << "Promedio de peso: " << promedioPeso << std::endl;;

    // Calcular y mostrar el IMC de cada paciente
    std::cout << "Indice de Masa Corporal (IMC) de cada paciente: " << std::endl;
    calcularIMC(head);


    // Desasignar memoria
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}