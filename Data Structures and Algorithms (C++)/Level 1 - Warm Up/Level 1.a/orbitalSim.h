/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 * 
 * orbitalSim.cpp
 * 
 * GRUPO 3 - LEVEL 1.A
 * Santiago Feldman 
 * Angeles Junco
 * 
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#define _USE_MATH_DEFINES  /* Enable M_PI definition */

#include <stdlib.h>        /* rand() */
#include <math.h>          /* M_PI */

#include "raylib.h"
#include "raymath.h"

#define N_ASTEROID 1000

typedef struct OrbitalBody
{
    const char *name; // Name
    float mass;		  // [kg]
    float radius;	  // [m]
    Color color;	  // raylib color
    Vector3 position; // [m]
    Vector3 velocity; // [m/s]
    Vector3 acceleration;
} orbitalbody_t;

typedef struct OrbitalSim
{
    float timeStep;
    float timeElapsed;
    int numberOfBodies;
    OrbitalBody* bodies;
} orbitalsim_t;

OrbitalSim *makeOrbitalSim(float timeStep);
void updateOrbitalSim(OrbitalSim *sim);
void freeOrbitalSim(OrbitalSim *sim);

#endif
