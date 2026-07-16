/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 * 
 * orbitalSimView.hpp
 * 
 * GRUPO 3 - LEVEL 1.B
 * Santiago Feldman 
 * Angeles Junco
 * 
 */

#ifndef ORBITALSIMVIEW_H
#define ORBITALSIMVIEW_H

#include "orbitalSim.hpp"

class OrbitalView
{
public:
    void renderOrbitalSim3D(OrbitalSim *sim);
    void renderOrbitalSim2D(OrbitalSim *sim);

private:
    const char* getISODate(float currentTime);
};

#endif
