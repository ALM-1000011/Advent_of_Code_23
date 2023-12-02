// AOC23 Día 1, Primera parte
// Dado un fichero de texto juntar el primer y último dígito encontrado para formar un número de dos cifras
// y sumar todos los números de dos cifras encontrados

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream inputFile;
    inputFile.open("input.txt");
    std::string line;
    int sum = 0;
    std::string numero;
    while (std::getline(inputFile, line)) {
    char primer_digito = ' ', ultimo_digito = ' ';
        int i = 0;
        while(primer_digito == ' ') {
            if (isdigit(line[i])) {
                primer_digito = line[i];
            }
            i++;
        } while (i != line.length()) {
            if (isdigit(line[i])) {
                ultimo_digito = line[i];
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