// AOC 23 Día 2, primera parte
// Descripción: Dado un fichero en el que figuran varias partidas al juego en el
// que el elfo enseña en distintos sets diferente números de combinaciones en la
// cantidad de cubos de cada color, dicha cantidad de cubos no podrá superar la
// configuración: 12 rojos, 13 verdes y 14 azules. El objetivo es sumar los ID's
// de los juegos que cumplen con la condición de que la cantidad de cubos.

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::fstream ficherillo;
  ficherillo.open("input.txt");
  std::string linea;
  int id;
  int sumid = 0;
  while (getline(ficherillo, linea)) {
    int rojos = 0;
    int verdes = 0;
    int azules  = 0;
    bool valido = true;
    std::string palabras, numeros;
    for (int i = 0; i <= linea.size(); i++) {
      if (linea[i] != ' ') {
        palabras += linea[i];
        if (isdigit(linea[i])) {
          numeros += linea[i];
          palabras.clear();
        }
        if (linea[i] == ':') {
            id = stoi(numeros);
            numeros.clear();
            palabras.clear();
        }
        if (palabras == "red") {
          rojos = stoi(numeros);
          numeros.clear();
          palabras.clear();
        } else if (palabras == "green") {
          verdes = stoi(numeros);
          numeros.clear();
          palabras.clear();
        } else if (palabras == "blue") {
          azules = stoi(numeros);
          numeros.clear();
          palabras.clear();
        }
        if (rojos > 12 || verdes > 13 || azules > 14) {
            valido = false;
            break;
        }
        if (linea[i] == ';') {
            azules = 0;
            verdes = 0;
            rojos = 0;
        }
      }
    }
    if (valido) {
        sumid += id;
    }
  }
  std::cout << "Suma de ID's: " << sumid << std::endl;
}