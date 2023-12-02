// AOC23 Día 1, Segunda Parte
// Dado un fichero de texto juntar el primer y último dígito encontrado para
// formar un número de dos cifras y sumar todos los números de dos cifras
// encontrados Parte dos: Se deberán tener en cuenta los números escritos con
// letras. P.ej = one, two, three, etc.

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
int main() {
  std::ifstream inputFile;
  inputFile.open("input.txt");
  std::string line;
  int sum = 0;
  std::map<std::string, char> numero_letras = {
      {"zero", '0'}, {"one", '1'},   {"two", '2'},   {"three", '3'},
      {"four", '4'},  {"five", '5'},  {"six", '6'},
      {"seven", '7'}, {"eight", '8'}, {"nine", '9'}};
  std::string numero;
  while (std::getline(inputFile, line)) {
    char primer_digito = ' ', ultimo_digito = ' ';
    std::string letra = "";
    int i = 0;
    while (primer_digito == ' ') {
      letra += line[i];
      if (isdigit(line[i])) {
        primer_digito = line[i];
      }
      for (const auto &pair : numero_letras) {
        if (letra.find(pair.first) != std::string::npos) {
          primer_digito = pair.second;
          letra = "";
          letra += line[i];
        }
      }
      i++;
    }
    while (i != line.length()) {
      letra += line[i];
      if (isdigit(line[i])) {
        ultimo_digito = line[i];
      }
      for (const auto &pair : numero_letras) {
        if (letra.find(pair.first) != std::string::npos) {
          ultimo_digito = pair.second;
          letra = "";
          letra += line[i];
        }
      }
      i++;
    }
    if (ultimo_digito == ' ') {
      ultimo_digito = primer_digito;
    }
    numero = std::string(1, primer_digito) + std::string(1, ultimo_digito);
    std::cout << "Numero encontrado: " << numero << std::endl;
    sum += std::stoi(numero);
  }
  std::cout << sum << std::endl;
  return 0;
}