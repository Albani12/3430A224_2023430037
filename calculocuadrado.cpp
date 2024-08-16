#include <iostream>

//Funcion que calcula el cuadrado de un numero

double square(double x){ // eleva al cuadrado un número de punto flotante de precisión doble

return x*x;
}

//Funcion que imprime el cuadrado de un numero
void print_square(double x)
{
std::cout << "el cuadrado de " << x << " es " << square(x) << '\n';
}

int main()
{
print_square(1.234); // print: el cuadrado de 1.234 es 1.52276
print_square(5.555); // print: el cuadrado de 5.555 es 30.858
}