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
 * PASOS SIGUIENTES
 * 
 * 1. Utilizamos float para representar las masas, velocidades, aceleraciones y distancias porque estas magnitudes físicas
 * toman valores continuos de los números reales. Float nos permite simular correctamente esa continuidad. Int, por ejemplo, 
 * hubiera tomado valores discretos para las magnitudes. Además utilizamos float y no double, que también permite simular
 * números reales, porque la precisión de float era la suficiente como para crear una simulación "convincente".
 * 
 * 3. La complejidad algorítmica de la simulación es O(n^2) debido a los "for" anidados de las líneas 106 y 113 (en este archivo),
 * que son la "estructura" más compleja del programa.
 * 
 * 4. Los cambios que se realizaron para poder simular sin problemas 1000 asteroides fue representar gráficamente a los 
 * asteroides como puntos y no como esferas, ya que graficarlos como esferas requería mucho más cálculo y se obtenía un resultado
 * muy similar al que se obtiene graficándolos como puntos (que es mucho más eficiente). 
 * 
 */

#include "orbitalSim.h"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743*(pow(10,-11))
#define ASTEROIDS_MEAN_RADIUS 4E11F
#define ASTEROIDS_MEAN_WEIGHT 0X3B9ACA00

// Gets a random value between min and max
float getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

// Places an asteroid
//
// centerMass: mass of the most massive object in the star system
void placeAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabs(l));
    float phi = getRandomFloat(0, 2 * M_PI);

    // Surprise!
    phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->mass = ASTEROIDS_MEAN_WEIGHT;  // Typical asteroid weight: 1 billion tons
    body->radius = ASTEROIDS_MEAN_RADIUS; // Typical asteroid radius: 2km
    body->color = GRAY;
    body->position = {r * cosf(phi), 0, r * sinf(phi)};
    body->velocity = {-v * sinf(phi), vy, v * cosf(phi)};

}

// Make an orbital simulation
OrbitalSim *makeOrbitalSim(float timeStep)
{
    // Memory allocation
    orbitalsim_t *sim = (orbitalsim_t*) malloc(sizeof(orbitalsim_t));
    if(sim==NULL)
    {
        return NULL;
    }
    sim->bodies= (orbitalbody_t*) malloc(sizeof(orbitalbody_t)*(SOLARSYSTEM_BODYNUM+N_ASTEROID));
    if(sim->bodies==NULL)
    {
        free(sim);
        return NULL;
    }

    // Information allocation
    sim->timeStep=timeStep;
    sim->timeElapsed=0;
    sim->numberOfBodies=SOLARSYSTEM_BODYNUM+N_ASTEROID;
    for(size_t i=0 ; i<SOLARSYSTEM_BODYNUM ; ++i)
    {
        (*sim).bodies[i].name= (solarSystem[i]).name;
        (*sim).bodies[i].mass= (solarSystem[i]).mass;
        (*sim).bodies[i].radius= (solarSystem[i]).radius;
        (*sim).bodies[i].color= (solarSystem[i]).color;
        (*sim).bodies[i].position= (solarSystem[i]).position;
        (*sim).bodies[i].velocity= (solarSystem[i]).velocity;
    }
    for(size_t j=SOLARSYSTEM_BODYNUM ; j<(sim->numberOfBodies) ; ++j)
    {
        placeAsteroid(&sim->bodies[j], sim->bodies[0].mass);
    }

    return sim;
}

// Simulates a timestep
void updateOrbitalSim(OrbitalSim *sim)
{
    // Calculation of force and acceleration
    for(size_t i=0 ; i<(SOLARSYSTEM_BODYNUM+N_ASTEROID) ; ++i)
    {
        Vector3 resultantForce;
        resultantForce.x=0;
        resultantForce.y=0;
        resultantForce.z=0;

        for(size_t j=0;j<SOLARSYSTEM_BODYNUM;++j)
        {
            if(i!=j) 
            {
                Vector3 unitVector=Vector3Subtract( sim->bodies[i].position ,sim->bodies[j].position);
                float vectorMod = Vector3Length(unitVector);
                unitVector=Vector3Scale(unitVector,1/vectorMod);

                Vector3 force=Vector3Scale(unitVector,-GRAVITATIONAL_CONSTANT*(sim->bodies[j].mass)/(vectorMod*vectorMod));
                resultantForce=Vector3Add(resultantForce,force);
            }
        }

        Vector3 acceleration;
        acceleration=resultantForce; // Se evita dividir por la masa ya que se simplifica en la sumatoria de fuerzas.
                                     // No incluir la masa en las líneas 127 y 133 evita cálculos inútiles.

        sim->bodies[i].velocity= Vector3Add(sim->bodies[i].velocity,Vector3Scale(acceleration,(sim->timeStep)));
        sim->bodies[i].position= Vector3Add(sim->bodies[i].position, Vector3Scale((sim->bodies[i].velocity),(sim->timeStep)));
    }

    (sim->timeElapsed)+=(sim->timeStep);    // Time update
}

// Frees the memory used for the simulation
void freeOrbitalSim(OrbitalSim *sim)
{
    free(sim->bodies);
    free(sim);
}
