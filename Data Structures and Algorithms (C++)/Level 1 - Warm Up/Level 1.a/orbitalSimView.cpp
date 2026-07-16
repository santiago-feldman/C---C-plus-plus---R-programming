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

#include <time.h>

#include "orbitalSimView.h"

#define SCALE pow(10,-11)

const char* getISODate(float currentTime) {
    // Epoch: 2022-01-01
    struct tm epoch_tm = { 0, 0, 0, 1, 0, 122 };
    time_t epoch = mktime(&epoch_tm);

    // Convert epoch time to local time
    time_t local_time = epoch + (time_t)currentTime;

    // Print ISO date for local time
    struct tm* local_tm = localtime(&local_time);
    return TextFormat("Date: %04d-%02d-%02d", 1900 + local_tm->tm_year, local_tm->tm_mon + 1, local_tm->tm_mday);
}

// Renders the orbital simulation on screen
void renderOrbitalSim3D(OrbitalSim *sim)
{
    for(size_t i=0 ; i<(sim->numberOfBodies-N_ASTEROID) ; ++i)
    {
        Vector3 scaledPos=Vector3Scale(sim->bodies[i].position, SCALE);
        DrawSphere(scaledPos, 0.005F*logf(sim->bodies[i].radius), sim->bodies[i].color);
        DrawPoint3D(scaledPos, sim->bodies[i].color);
    }
    for (size_t x=(sim->numberOfBodies-N_ASTEROID) ; x<(sim->numberOfBodies) ; ++x)
    {
        Vector3 scaledPos=Vector3Scale(sim->bodies[x].position, SCALE);
        DrawPoint3D(scaledPos, sim->bodies[x].color);
    }
}

// Shows the FPS counter and date on screen
void renderOrbitalSim2D(OrbitalSim *sim)
{
    DrawFPS(5,0);
    DrawText(getISODate(sim->timeElapsed), 5, 25, 20, WHITE); 
}
