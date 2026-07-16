/**
 * @file NedWunsch.h
 *
 * @copyright Copyright (C) 2022
 * @author Tomás Agustín Castro, Santiago Feldman
 *
 * @brief Header del código fuente del algoritmo de Hirschberg
 */

#ifndef NED_WUNSCH_H
#define NED_WUNSCH_H

#include <string>

#define MATCH_SCORE 1
#define SUBST_SCORE -1
#define INDEL_SCORE -1

int findBestAlignment(std::string &s, std::string &t);

#endif