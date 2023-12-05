// AOC 23 Día 2, segunda parte
// Descripción: Dado un fichero de texto en el que figura el esquema de un
// sistema (serie de números y símbolos en cada línea) cualquier número
// adayacente a un símbolo es "parte de un número" y se deberá añadir a la suma
// total. ('. no es un símbolo) Copyrigth (C) 2023 A.L.M Ver:
// https://adventofcode.com/2020/day/3 Versión: 1.00

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
  std::ifstream ficherillo("input.txt"); // Abre el archivo "input.txt" para lectura
  std::string linea, numero; // Variables para almacenar la línea actual y el número actual
  int sumatotal = 0, cont_vector = 2; // Variables para almacenar la suma total y el contador del vector
  int posicion_ultimo_simbolo = -99; // Variable para almacenar la posición del último símbolo encontrado
  std::vector<std::pair<int, int>> posible_partes, numero_cont; // Vectores para almacenar las posibles partes 
  // de un número y los números encontrados
  while (std::getline(ficherillo, linea)) { // Lee cada línea del archivo
    for (int j = 0; j < numero_cont.size(); j++) { // Recorre el vector de números encontrados
      auto &numero_ind = numero_cont[j]; // Referencia al número actual
      numero_ind.second--;          // Decrementa el contador del número actual
      if (numero_ind.second == 0) { // Si el contador llega a cero
        for (int w = 0; w <= posible_partes.size(); w++) { // Recorre el vector de posibles partes
          if (posible_partes[w].first == numero_ind.first) { // Si encuentra la parte correspondiente al número actual
            posible_partes[w].second = 99; // Marca la parte como encontrada
          }
        }
      }
    }
    for (int i = 0; i < linea.size(); i++) {  // Recorre cada caracter de la línea
      if (isdigit(linea[i])) { // Si el caracter es un dígito
        numero += linea[i];    // Agrega el dígito al número actual
      } else if (!isdigit(linea[i]) && numero.size() > 0) { // Si el caracter no es un dígito y el número actual no está vacío
        posible_partes.push_back(std::make_pair( std::stoi(numero), i - 1)); // Agrega la parte del número al vector de posibles partes
        numero_cont.push_back(std::make_pair(std::stoi(numero), cont_vector)); // Agrega el número al vector de números encontrados
        if (posicion_ultimo_simbolo != -99) { // Si se encontró un símbolo anteriormente
          int numero_encontrado = std::stoi(numero); // Convierte el número actual a entero
          for (int w = 0; w <= numero.size(); w++) { // Recorre el número actual
            if (i + w == posicion_ultimo_simbolo || i - w == posicion_ultimo_simbolo) { // Si el número está adyacente al símbolo anterior
              sumatotal += numero_encontrado; // Agrega el número a la suma total
              posible_partes.erase(posible_partes.begin() + posible_partes.size() - 1); // Elimina la parte del número del vector de posibles partes
            }
          }
        }
        numero.clear(); // Limpia el número actual
      } else if (linea[i] != '.' && !isdigit(linea[i])) { // Si el caracter no es un punto ni un dígito
        posicion_ultimo_simbolo = i; // Almacena la posición del último símbolo encontrado
        for (int j = 0; j < posible_partes.size(); j++) { // Recorre el vector de posibles partes
          auto numero_ind = posible_partes[j]; // Copia del número actual
          std::string numero2 = std::to_string(numero_ind.first); // Convierte el número a cadena
          for (int w = 0; w <= numero2.size(); w++) { // Recorre el número convertido a cadena
            if (numero_ind.second + w == i || numero_ind.second - w == i) { // Si el número está adyacente al símbolo actual
              sumatotal += numero_ind.first; // Agrega el número a la suma total
              posible_partes[j].second = 99; // Elimina la parte del número del vector de posibles partes
            }
          }
        }
      }
    }
  }
  std::cout << sumatotal << std::endl; // Imprime la suma total
  return 0; // Retorna 0 para indicar que el programa finalizó correctamente
}