/**
 * @file Hirschberg.cpp
 *
 * @copyright Copyright (C) 2022
 * @author Tomás Agustín Castro, Santiago Feldman
 *
 * @brief Implementación del algoritmo de Hirschberg para el ordenamiento de las secuencias
 *
 */

using namespace std;

#include "Hirschberg.h"

#include <vector>
#include <iostream>
#include <algorithm> // para std::max
#include <stdexcept>

enum operations
{
    INSERTION = 'I',
    DELETION = 'D',
    MATCH = '|',
    MISMATCH = '*',
    INDEL = '-'
};

vector<int> getNWRowScoresFront(const char *s, const char *t, unsigned int sizeS, 
                                unsigned int sizeT);
vector<int> getNWRowScoresReverse(const char *s, const char *t, unsigned int sizeS, 
                                  unsigned int sizeT);
void hirschbergRecursiveStep(const char *s, const char *t, unsigned int sizeS, unsigned int sizeT,
                             string &alignment);

/**
 * @brief Ejecuta el algoritmo de Hirschberg para alinear las dos secuencias ingresadas en la
 *        función y calcula el puntaje del algoritmo.
 *
 * @param s Puntero al string que contiene la primera secuencia
 * @param t Puntero al string que contiene la segunda secuencia
 * @return Puntaje obtenido al ejecutar el algoritmo de ordenamiento
 */
int findBestAlignment(string &s, string &t)
{
    string alignment;
    hirschbergRecursiveStep(s.data(), t.data(), s.size(), t.size(), alignment);

    string sOut, tOut, alignmentOut;
    int score = 0;
    unsigned int l = alignment.size(), k = 0;
    for (unsigned int i = 0, j = 0; k < l;)
    {
        switch (alignment[k])
        {
        case INSERTION:
            sOut.push_back(INDEL);
            tOut.push_back(t[j++]);
            alignmentOut.push_back(' ');
            score += INDEL_SCORE;
            break;
        case DELETION:
            sOut.push_back(s[i++]);
            tOut.push_back(INDEL);
            alignmentOut.push_back(' ');
            score += INDEL_SCORE;
            break;
        case MATCH:
            sOut.push_back(s[i++]);
            tOut.push_back(t[j++]);
            alignmentOut.push_back(MATCH);
            score += MATCH_SCORE;
            break;
        case MISMATCH:
            sOut.push_back(s[i++]);
            tOut.push_back(t[j++]);
            alignmentOut.push_back(MISMATCH);
            score += SUBST_SCORE;
            break;
        default:
            throw invalid_argument("Error: se encontró un caracter no permitido en alignment");
        }

        if (!(++k % 60))
        {
            cout << sOut << endl;
            cout << alignmentOut << endl;
            cout << tOut << endl
                 << endl;
            sOut.clear();
            alignmentOut.clear();
            tOut.clear();
        }
    }
    if ((k % 60))
    {
        cout << sOut << endl;
        cout << alignmentOut << endl;
        cout << tOut << endl
             << endl;
    }

    cout << "score = " << score;
    return score;
}

/**
 * @brief Paso recursivo del algoritmo de Hirschberg
 *
 * @param s Puntero al string de la primera secuencia
 * @param t Puntero al string de la segunda secuencia
 * @param sizeS Tamaño de la primera secuencia
 * @param sizeT Tamaño de la segunda secuencia
 * @param alignment Puntero al string que contiene todas las transformaciones a realizar
 */
void hirschbergRecursiveStep(const char *s, const char *t, unsigned int sizeS, unsigned int sizeT,
                             string &alignment)
{
    if (sizeS > 1 && sizeT > 1)
    {
        unsigned int i = sizeS / 2;
        unsigned int j;

        // Se obtiene el índice de columna y se destruyen los arreglos para que no se acumulen
        // en el call stack
        {
            vector<int> upperRow = getNWRowScoresFront(s, t, i, sizeT);
            vector<int> lowerRow = getNWRowScoresReverse(s + i, t, sizeS - i, sizeT);
            transform(upperRow.begin(), upperRow.end(), lowerRow.begin(), 
                      upperRow.begin(), plus<int>());
            j = max_element(upperRow.begin(), upperRow.end()) - upperRow.begin();
        }

        hirschbergRecursiveStep(s, t, i, j, alignment);
        hirschbergRecursiveStep(s + i, t + j, sizeS - i, sizeT - j, alignment);
    }
    else if (sizeS == 1 && sizeT > 0)
    {
        bool found = false;
        unsigned int j = 0;
        for (; j < sizeT - 1; j++)
        {
            if (!found && s[0] == t[j])
            {
                found = true;
                alignment.push_back(MATCH);
            }
            else
            {
                alignment.push_back(INSERTION);
            }
        }

        // Si se terminó de leer t, hay que analizar entre si ya se había encontrado coincidencia
        // del caracter de s.

        if (found)
        {
            alignment.push_back(INSERTION);
        }
        else if (s[0] == t[j])
        {
            alignment.push_back(MATCH);
        }
        else
        {
            alignment.push_back(MISMATCH);
        }
    }
    else if (sizeT == 1 && sizeS > 0)
    {
        bool found = false;
        unsigned int i = 0;
        for (; i < sizeS - 1; i++)
        {
            if (!found && s[i] == t[0])
            {
                found = true;
                alignment.push_back(MATCH);
            }
            else
            {
                alignment.push_back(DELETION);
            }
        }

        // Si se terminó de leer s, hay que analizar entre si ya se había encontrado coincidencia
        // del caracter de t.

        if (found)
        {
            alignment.push_back(DELETION);
        }
        else if (s[i] == t[0])
        {
            alignment.push_back(MATCH);
        }
        else
        {
            alignment.push_back(MISMATCH);
        }
    }
    else if (sizeS == 0)
    {
        for (unsigned int j = 0; j < sizeT; j++)
        {
            alignment.push_back(INSERTION);
        }
    }
    else if (sizeT == 0)
    {
        for (unsigned int i = 0; i < sizeS; i++)
        { 
            alignment.push_back(DELETION);
        }
    }
}

/**
 * @brief Ejecuta el algoritmo de Needleman-Wunsch de arriba a abajo (forma 'normal')
 *
 * @param s Puntero al string de la primera secuencia
 * @param t Puntero al string de la segunda secuencia
 * @param sizeS Tamanño de la primera secuencia
 * @param sizeT Tamaño de la segunda secuencia
 * @return Puntajes de la última fila (la fila de más abajo)
 */
vector<int> getNWRowScoresFront(const char *s, const char *t, unsigned int sizeS, 
                                unsigned int sizeT)
{
    vector<int> upperRow(sizeT + 1), lowerRow(sizeT + 1);
    upperRow[0] = 0;

    for (unsigned int j = 1; j <= sizeT; j++) 
    {
        upperRow[j] = upperRow[j - 1] + INDEL_SCORE;
    }

    for (unsigned int i = 1; i <= sizeS; i++)
    {
        lowerRow[0] = upperRow[0] + INDEL_SCORE;
        for (unsigned int j = 1; j <= sizeT; j++)
        {
            int upSum = upperRow[j] + INDEL_SCORE;
            int leftSum = lowerRow[j - 1] + INDEL_SCORE;
            int diagSum = upperRow[j - 1] + (s[i - 1] == t[j - 1] ? MATCH_SCORE : SUBST_SCORE);
            lowerRow[j] = max({upSum, leftSum, diagSum});
        }
        upperRow = lowerRow;
    }

    return lowerRow;
}

/**
 * @brief Ejecuta el algoritmo de Needleman-Wunsch de manera inversa (es decir, de abajo hacia 
 *        arriba)
 *
 * @param s Puntero al string de la primera secuencia
 * @param t Puntero al string de la segunda secuencia
 * @param sizeS Tamaño de la primera secuencia
 * @param sizeT Tamaño de la segunda secuencia
 * @return Puntajes de la última fila (la fila de más arriba)
 */
vector<int> getNWRowScoresReverse(const char *s, const char *t, unsigned int sizeS, 
                                  unsigned int sizeT)
{
    vector<int> upperRow(sizeT + 1), lowerRow(sizeT + 1);
    lowerRow[sizeT] = 0;

    for (unsigned int j = sizeT; j > 0; j--)
    {
        lowerRow[j - 1] = lowerRow[j] + INDEL_SCORE;
    }

    for (unsigned int i = sizeS; i > 0; i--)
    {
        upperRow[sizeT] = lowerRow[sizeT] + INDEL_SCORE;
        for (unsigned int j = sizeT; j > 0; j--)
        {
            int downSum = lowerRow[j - 1] + INDEL_SCORE;
            int rightSum = upperRow[j] + INDEL_SCORE;
            int diagSum = lowerRow[j] + (s[i - 1] == t[j - 1] ? MATCH_SCORE : SUBST_SCORE);
            upperRow[j - 1] = max({downSum, rightSum, diagSum});
        }
        lowerRow = upperRow;
    }

    return upperRow;
}