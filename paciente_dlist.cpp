#include <iostream>

// Define una estructura nombre "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;
    double altura;
    Paciente*next;
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
        std::cout << current->nombre << " tiene " << current->edad << " anos" << std::endl;
        current = current->next;
    }
}

int main() {
    Paciente* head = nullptr;

    // Agregar pacientes a la lista
    addPaciente(head, "Diana", 25, 40, 1.55);
    addPaciente(head, "Emiliano", 37, 62.7, 1.85);
    addPaciente(head, "Yonnathan", 30, 70.5, 1.70);

    // imprimir la lista
    printPaciente(head);

    // Eliminar un paciente
    removePaciente(head, "Emiliano");

    // Imprime la lista actualizada
    printPaciente(head);

    // Desasignar memoria
    while (head != nullptr) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}



