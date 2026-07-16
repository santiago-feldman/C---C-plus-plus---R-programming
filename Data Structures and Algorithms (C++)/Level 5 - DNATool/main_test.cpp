/**
 * DNA Tool tests
 *
 * @copyright Copyright (C) 2022
 * @author Tomás Agustín Castro, Santiago Feldman
 *
 * @brief Main de pruebas para verificar el correcto funcionamiento del programa.
 * 
 * OBSERVACIÓN: Los tests se hicieron para un sistema de puntuación que otorgue 1 y -1 puntos
 * para coincidencias y sustituciones/inserciones/deleciones respectivamente. Modificar el sistema
 * de puntuación puede hacer que el alineamiento óptimo sea diferente y por lo tanto sea necesario
 * volvera a analizar cuál es la cantidad óptima de inserciones/deleciones y sustituciones al
 * momento de definir la variable expectedScore
 */

using namespace std;

#include <iostream>
#include <string>

#include "Hirschberg.h"

/**
 * @brief Indica si el programa alínea las secuencias correctamente
 *
 * @param s Puntero al string de la primera secuencia
 * @param t Puntero al string de la segunda secuencia
 * @param expectedScore Puntaje que debería dar el algoritmo una vez ejecutado
 */
void test(string &s, string &t, int expectedScore)
{
  cout << "Prueba:" << endl;
  cout << "s = " << s << endl;
  cout << "t = " << t << endl;
  cout << "expectedScore = " << expectedScore << endl
       << endl;

  int score = findBestAlignment(s, t);
  cout << endl
       << (score == expectedScore ? "PASS" : "FAIL") << endl
       << endl;
}

/**
 * @brief Main de las pruebas. Contiene los strings y puntajes de las pruebas a realizar
 *
 */
int main()
{
  string s, t;
  int expectedScore;

  s = "GATTACA";
  t = "CGATACG";
  expectedScore = 5 * MATCH_SCORE + 2 * INDEL_SCORE + 1 * SUBST_SCORE;
  test(s, t, expectedScore);

  t.clear();
  expectedScore = 7 * INDEL_SCORE;
  test(s, t, expectedScore);

  t = "C";
  expectedScore = 6 * INDEL_SCORE + 1 * MATCH_SCORE;
  test(s, t, expectedScore);

  t = "G";
  expectedScore = 6 * INDEL_SCORE + 1 * MATCH_SCORE;
  test(s, t, expectedScore);

  t = "CGATACG";
  s.clear();
  expectedScore = 7 * INDEL_SCORE;
  test(s, t, expectedScore);

  s = "G";
  expectedScore = 6 * INDEL_SCORE + 1 * MATCH_SCORE;
  test(s, t, expectedScore);

  s = "C";
  expectedScore = 6 * INDEL_SCORE + 1 * MATCH_SCORE;
  test(s, t, expectedScore);

  s = "ATGCGTGCGACTGCGTCACGTGCGACGTGCTGCACGTCACGTGCACGTCACGTGTGCACAAACGTGCACG";
  t = "ACGTGGTGCACGTGCACACGTGTGTGCAGTGCAAACGTGCACGTGAACGTGCACCCGTGCACGTCACGTC";
  expectedScore = 54 * MATCH_SCORE + 22 * INDEL_SCORE + 5 * SUBST_SCORE;
  test(s, t, expectedScore);
}