/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 * 
 * orbitalSim.hpp
 * 
 * GRUPO 3 - LEVEL 1.B
 * Santiago Feldman 
 * Angeles Junco
 * 
 */

#ifndef ORBITALSIM_H
#define ORBITALSIM_H

#define _USE_MATH_DEFINES  /* Enable M_PI definition */

#include <stdlib.h>        /* rand() */
#include <math.h>          /* M_PI */
#include <string>

#include "raylib-cpp.hpp"
#include "Vector3.hpp"
#include "raymath.h"

#define N_ASTEROID 1000

class OrbitalBody
{
public:
    
    void setName(std::string name);

    void setMass(float mass);
    float getMass();
    void setRadius(float radius);
    float getRadius();
    void setColor(Color color);
    Color getColor();
    void setPosition(raylib::Vector3 position);
    raylib::Vector3 getPosition();
    void setVelocity(raylib::Vector3 velocity);
    raylib::Vector3 getVelocity();

private:
    std::string name; // Name
    float mass;		  // [kg]
    float radius;	  // [m]
    Color color;	  // raylib color
    raylib::Vector3 position; // [m]
    raylib::Vector3 velocity; // [m/s]
    raylib::Vector3 acceleration;

};

class OrbitalSim
{
public:
    OrbitalSim(float timeStep);
    ~OrbitalSim();

    void updateOrbitalSim();
    void renderOrbitalSim3D();
    void renderOrbitalSim2D();
    int getNumberOfBodies();
    float getTimeElapsed();

    OrbitalBody* bodies;

private:
    float getRandomFloat(float min, float max);
    void placeAsteroid(OrbitalBody* body, float centerMass);

    float timeStep;
    float timeElapsed;
    int numberOfBodies;

};


#endif
