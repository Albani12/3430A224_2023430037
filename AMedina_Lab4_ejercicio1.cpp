#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// Estructura del nodo del árbol
struct Nodo {
    int dato;               // Valor del nodo
    Nodo *izquierdo;       // Puntero al hijo izquierdo
    Nodo *derecho;         // Puntero al hijo derecho
};