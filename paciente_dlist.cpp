#include <iostream>

// Define una estructura nombre "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;
    double altura;
    Paciente*next;
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

// Función para imprimir todas las personas en la lista.
void printPaciente(const Paciente* head) {
    const Paciente* current = head;
    while (current != nullptr) {
        std::cout << current->nombre << " is " << current->edad << " years old." << std::endl;
        current = current->next;
    }
}

int main() {
    Paciente* head = nullptr;

    // Agregar personas a la lista
    addPaciente(head, "Alice", 25, 50, 1.45);
    addPaciente(head, "Bob", 30, 60, 1.75);
    addPaciente(head, "Charlie", 28, 75, 1.60);

    // imprimir la lista
    printPaciente(head);

    // Eliminar una persona
    removePaciente(head, "Bob");

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



