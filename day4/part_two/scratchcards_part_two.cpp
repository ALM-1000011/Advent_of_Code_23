// AOC 23 Día 4, segunda parte
// Descripción: Dado un fichero de texto en el que se muestran distintas cartas,
// cada carta contiene los números ganadores de una rifa separados de los
// números que has obtenido en dicha rifa. Por cada número ganador que coincida
// con el tuyo, obtienes una copia de las siguientes cartas por debajo de la estudiada.
// P. ej: Si estudias la carta dos y obtienes 3 coincidencias, obtienes una copia de las cartas 3, 4 y 5.
// El programa muestra la suma de todas las cartas que obtienes.
// Copyrigth (C) 2023 A.L.M Ver:
// https://adventofcode.com/2023/day/4#part2 Versión: 1.00

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>



int main() {
  std::ifstream fichero("input.txt");
  std::string linea, numero;
  int resultado_final = 0;
  int numero_cartas = 1;
  std::vector<int> vec_copias_cartas;
  vec_copias_cartas.push_back(0); // Para indexar el vector desde 1 (ya que el fichero empieza en 1)
  vec_copias_cartas.push_back(1); // La carta 1 siempre tendrá una copia

  while (std::getline(fichero, linea)) {
    int coincidencias = 0;
    std::vector<int> cartas_ganadoras, mis_cartas;
    bool segunda_tanda = false, numero_carta = true;

    // Leer los números ganadores y las cartas del jugador
    for (int i = 0; i <= linea.length(); i++) {
      if (isdigit(linea[i]) && !numero_carta) {
        numero += linea[i];
      } else if (linea[i] == ' ' && !segunda_tanda && !numero_carta && numero.length() >= 1) {
        cartas_ganadoras.push_back(std::stoi(numero));
        numero.clear();
      } else if (linea[i] == '|') {
        segunda_tanda = true;
      } else if (linea[i] == ' ' && segunda_tanda && !numero_carta && numero.length() >= 1) {
        mis_cartas.push_back(std::stoi(numero));
        numero.clear();
      } else if (linea[i] == ':') {
        numero_carta = false;
      } else if (i == linea.length() && numero.length() >= 1) {
        mis_cartas.push_back(std::stoi(numero));
        numero.clear();
      }
    }

    // Contar las coincidencias entre los números ganadores y las cartas del jugador
    for (int i = 0; i < cartas_ganadoras.size(); i++) {
      for (int j = 0; j < mis_cartas.size(); j++) {
        if (cartas_ganadoras[i] == mis_cartas[j]) {
          coincidencias++;
        }
      }
    }

    // Obtener copias de las cartas siguientes si hay coincidencias
    if (coincidencias > 0) {
      for (int i = 1; i <= coincidencias; i++) {
        int posicion = numero_cartas + i;
        if (posicion + i > 0 && posicion < vec_copias_cartas.size()) {
          vec_copias_cartas[posicion] += vec_copias_cartas[numero_cartas];
        } else {
          vec_copias_cartas.push_back(1);
          vec_copias_cartas[posicion] += vec_copias_cartas[numero_cartas];
        }
      }
    }

    numero_cartas++;
    if (numero_cartas > 0 && numero_cartas > vec_copias_cartas.size()) {
      vec_copias_cartas.push_back(1);
    }
  }

  //Calcular el resultado final sumando las copias de las cartas
  for (int i = 1; i < vec_copias_cartas.size(); i++) {
    resultado_final += vec_copias_cartas[i];
  }
  std::cout << "Resultado: " << resultado_final << std::endl;

  fichero.close();
}