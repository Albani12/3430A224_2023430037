#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Definición de la estructura "Paciente"
struct Paciente {
    std::string nombre;
    int edad;
    double peso;   
    double altura; 
    double a1c;    // Nivel de azúcar en la sangre (A1C)
    double imc;    // Indice de Masa Corporal (IMC)
    int prioridad; // Valor de prioridad calculado
    Paciente* next; // Puntero al siguiente paciente en la lista


    // Constructor del paciente
    Paciente(const std::string& n, int e, double p, double a, double a1c_val)
        : nombre(n), edad(e), peso(p), altura(a), a1c(a1c_val), next(nullptr) {
        imc = peso / (altura * altura);
        prioridad = calcularPrioridad();
    }

    // Función para calcular la prioridad del paciente basado en A1C y IMC
    //El índice de prioridad se define multiplicando el valor de riesgo asignado a A1C (0, 1, 2) 
    //por el IMC del paciente, asi se da mayor prioridad a quienes tengan valores más altos de A1C e IMC.
    int calcularPrioridad() {
        int valorA1C = 0;

        // Asigna valores a A1C: 0 para normal, 1 para prediabetes, y 2 para diabetes
        if (a1c < 5.7) {
            valorA1C = 0; // Normal
        } else if (a1c <= 6.5) {
            valorA1C = 1; // Prediabetes
        } else {
            valorA1C = 2; // Diabetes
        }

        // Multiplica por el IMC para definir la prioridad, 
        //el que tenga un valor mas alto es el primero en tener mayor prioridad, 
        //como lo fue la sugerencia del profe :)
        return valorA1C * imc;
    }
};

// Función para insertar pacientes en la lista ordenada por prioridad
void insertarEnOrden(Paciente*& head, Paciente* nuevoPaciente) {
    // La lista esta vacia o el nuevo paciente tiene una prioridad mas alta que el primero de la lista.
    if (!head || nuevoPaciente->prioridad > head->prioridad) {
        nuevoPaciente->next = head;
        head = nuevoPaciente;
    } else { //Se inserta el nuevo paciente en su posición correcta en la lista.
        Paciente* current = head;
        //busca la posición correcta en la lista donde la prioridad 
        //del nuevo paciente sea mayor o igual que los siguientes
        while (current->next && current->next->prioridad >= nuevoPaciente->prioridad) {
            current = current->next;
        }
        //inserta el nuevo paciente en su posicion
        nuevoPaciente->next = current->next;
        current->next = nuevoPaciente;
    }
}

// Función para cargar pacientes desde un archivo CSV
void cargarDesdeArchivo(Paciente*& head) {
    std::string nombreArchivo = "pacientes.csv"; // Nombre del archivo CSV
    std::ifstream archivo(nombreArchivo);

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre;
        int edad;
        double peso, altura, a1c;

        //datos desde la línea
        std::getline(ss, nombre, ',');
        ss >> edad;
        ss.ignore(); // Ignorar la coma
        ss >> peso;
        ss.ignore(); // Ignorar la coma
        ss >> altura;
        ss.ignore(); // Ignorar la coma
        ss >> a1c;

    // Crear un nuevo paciente y añadirlo a la lista en orden de prioridad
        Paciente* nuevoPaciente = new Paciente(nombre, edad, peso, altura, a1c);
        insertarEnOrden(head, nuevoPaciente);
    }

    archivo.close();
}

// Funcion para mostrar la lista de pacientes ordenados por prioridad
void mostrarCola(Paciente* head) {
    Paciente* current = head;
    while (current) {
        std::cout << "Nombre: " << current->nombre << ", Edad: " << current->edad 
                  << ", IMC: " << current->imc << ", A1C: " << current->a1c 
                  << ", Prioridad: " << current->prioridad << std::endl;
        current = current->next;
    }
}

void buscarPorIMC(Paciente* head, double imc) {
    Paciente* current = head;
    while (current) {
        if (current->imc == imc) {
            std::cout << "Nombre: " << current->nombre << ", Edad: " << current->edad 
                      << ", IMC: " << current->imc << ", A1C: " << current->a1c 
                      << ", Prioridad: " << current->prioridad << std::endl;
        }
        current = current->next;
    }
}

void buscarPorA1C(Paciente* head, double a1c) {
    Paciente* current = head;
    while (current) {
        if (current->a1c == a1c) {
            std::cout << "Nombre: " << current->nombre << ", Edad: " << current->edad 
                      << ", IMC: " << current->imc << ", A1C: " << current->a1c 
                      << ", Prioridad: " << current->prioridad << std::endl;
        }
        current = current->next;
    }
}

// Funcion para liberar la memoria de la lista de pacientes
void liberarMemoria(Paciente*& head) {
    while (head) {
        Paciente* temp = head;
        head = head->next;
        delete temp;
    }
}

// Menu interactivo para gestionar los pacientes
void menu() {
    Paciente* colaPacientes = nullptr;
    int opcion;

    do {
        std::cout << "Menu de Gestion de Pacientes" << std::endl;
        std::cout << "1. Cargar pacientes desde archivo" << std::endl;
        std::cout << "2. Mostrar cola de pacientes segun prioridad" << std::endl;
        std::cout << "3. Buscar pacientes por IMC" << std::endl;
        std::cout << "4. Buscar pacientes por A1C" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion: "<< std::endl;
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                cargarDesdeArchivo(colaPacientes);
                std::cout << "Pacientes cargados exitosamente." << std::endl;
                break;
            case 2:
                mostrarCola(colaPacientes);
                break;
            case 3:
                double imcBuscado;
                std::cout << "Ingrese el IMC a buscar: ";
                std::cin >> imcBuscado;
                buscarPorIMC(colaPacientes, imcBuscado);
                break;
            case 4:
                double a1cBuscado;
                std::cout << "Ingrese el A1C a buscar: ";
                std::cin >> a1cBuscado;
                buscarPorA1C(colaPacientes, a1cBuscado);
                break;
            case 0:
                std::cout << "Saliendo del programa." << std::endl;
                break;
        }
    } while (opcion != 0);

    // Liberar la memoria al finalizar
    liberarMemoria(colaPacientes); 
}

int main() {
    menu();
    return 0;
}


