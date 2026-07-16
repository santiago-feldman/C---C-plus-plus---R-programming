/**
 * DNA Tool tests
 *
 * @copyright Copyright (C) 2022
 * @author Tomás Agustín Castro, Santiago Feldman
 *
 * @brief Programa principal para la comparación de similitud de cadenas de ADN a partir del
 * algoritmo de Hirschberg. El programa recibe mediante argumentos de consola los archivos en
 * formato GenBank a comparar e imprime en consola la mejor alineación y el puntaje óptimo,
 * basado en el criterio de puntuación escogido (definido en Hirschberg.h)
 *
 * Referencia: http://blog.piotrturski.net/2015/04/hirschbergs-algorithm-explanation.html
 */

using namespace std;

#include <fstream>
#include <string>
#include <iostream>

#include "Hirschberg.h"

const string allowedChars = "acgtACGT";

void getSequencefromFile(ifstream &file, string &s);

/**
 * @brief Main del programa. Recibe los archivos en formato GetBank mediante argumentos de
 * consola.
 *
 * @param argc 
 * @param argv Ruta de los archivos que contienen las secuencias
 */
int main(int argc, char *argv[])
{
    ifstream file1(argv[1]), file2(argv[2]);

    if (!file1.is_open())
    {
        cerr << "Error al abrir el archivo " << argv[1] << endl;
        return 1;
    }

    if (!file2.is_open())
    {
        cerr << "Error al abrir el archivo " << argv[2] << endl;
        return 1;
    }

    string s1, s2;

    getSequencefromFile(file1, s1);
    getSequencefromFile(file2, s2);

    cout << "Archivos a comparar:" << endl
         << endl;

    cout << argv[1] << endl;
    cout << argv[2] << endl
         << endl;

    findBestAlignment(s1, s2);
}

/**
 * @brief Convierte la secuencia de los archivos ingresados en la terminal a strings
 *
 * @param file Archivo del que se obtiene la secuencia
 * @param s Referencia al string en el que se copia la secuencia
 */
void getSequencefromFile(ifstream &file, string &s)
{
    try
    {
        string line;
        while (getline(file, line) && (line.find("ORIGIN") == string::npos))
            ;
        
        // Se borra todo lo que está antes de la palabra ORIGIN
        size_t pos = line.find("ORIGIN");
        line.erase(0, pos + 6);


        // Se agregan los caracteres que están después de la palabra ORIGIN
        for (auto c : line)
        {
            if (allowedChars.find(c) != string::npos)
            {
                s.push_back(tolower(c));
            }
        }

        line.clear();

        while (getline(file, line, ' ') && (line.find("//") == string::npos))
        {
            for (auto c : line)
            {
                if (allowedChars.find(c) != string::npos)
                {
                    s.push_back(tolower(c));
                }
            }
        }

        // Se agregan los caracteres que están antes de las barras
        for (auto c : line)
        {
            if (allowedChars.find(c) != string::npos)
            {
                s.push_back(tolower(c));
            }
            else if (c == '/')
            {
                break;
            }
        }
    }

    catch (const ifstream::failure &e)
    {
        cerr << "Excepción mientras se leía un archivo:" << endl
            << e.code().value() << ' ' << e.what();
    }

}