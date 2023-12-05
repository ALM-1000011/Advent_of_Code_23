// AOC 23 Día 3, segunda parte
// Descripción: Dado un fichero de texto en el que se muestran distintas cartas,
// cada carta contiene los números ganadores de una rifa separados de los
// números que has obtenido en dicha rifa. Por cada número ganador que coincida
// con el tuyo, obtienes un punto, muliplicandose por dos consecutivamente.
// Copyrigth (C) 2023 A.L.M Ver:
// https://adventofcode.com/2020/day/3 Versión: 1.00

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream fichero("input.txt");
  std::string linea, numero;
  int resultado_final = 0;
  while (std::getline(fichero, linea)) {
    int resultado = 0;
    std::vector<int> cartas_ganadoras, mis_cartas;
    bool segunda_tanda = false, numero_carta = true;
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
    for (int i = 0; i < cartas_ganadoras.size(); i++) {
      for (int j = 0; j < mis_cartas.size(); j++) {
        if (cartas_ganadoras[i] == mis_cartas[j]) {
          if (resultado == 0) {
            resultado = 1;
          } else {
            resultado = resultado * 2;
          }
        }
      }
    }
    resultado_final += resultado;
  }
  std::cout << "Resultado: " << resultado_final << std::endl;
  fichero.close();
}