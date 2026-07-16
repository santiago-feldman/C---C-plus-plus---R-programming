/*
 * Orbital simulation
 *
 * 22.08 EDA
 * Copyright (C) 2022 Marc S. Ressl
 * 
 * orbitalSim.cpp
 * 
 * GRUPO 3 - LEVEL 1.B
 * Santiago Feldman 
 * Angeles Junco
 * 
 */

#include "orbitalSim.hpp"
#include "ephemerides.h"

#define GRAVITATIONAL_CONSTANT 6.6743*(pow(10,-11))
#define ASTEROIDS_MEAN_RADIUS 4E11F
#define ASTEROIDS_MEAN_WEIGHT 0X3B9ACA00

// Make an orbital simulation
OrbitalSim::OrbitalSim(float timeStep)
{
    this->timeStep=timeStep;
    timeElapsed=0;
    numberOfBodies=SOLARSYSTEM_BODYNUM+N_ASTEROID;

    bodies = new OrbitalBody[SOLARSYSTEM_BODYNUM+N_ASTEROID]; 

    for(size_t i=0 ; i<SOLARSYSTEM_BODYNUM ; ++i)
    {
        bodies[i].setName(solarSystem[i].name);
        bodies[i].setMass(solarSystem[i].mass);
        bodies[i].setRadius(solarSystem[i].radius);
        bodies[i].setColor(solarSystem[i].color);
        bodies[i].setPosition(solarSystem[i].position);
        bodies[i].setVelocity(solarSystem[i].velocity);
    }
    for(size_t j=SOLARSYSTEM_BODYNUM ; j<numberOfBodies ; ++j)
    {
        placeAsteroid(&bodies[j], bodies[0].getMass());
    }

}

// Gets a random value between min and max
float OrbitalSim::getRandomFloat(float min, float max)
{
    return min + (max - min) * rand() / (float)RAND_MAX;
}

// Places an asteroid
//
// centerMass: mass of the most massive object in the star system
void OrbitalSim::placeAsteroid(OrbitalBody *body, float centerMass)
{
    // Logit distribution
    float x = getRandomFloat(0, 1);
    float l = logf(x) - logf(1 - x) + 1;

    // https://mathworld.wolfram.com/DiskPointPicking.html
    float r = ASTEROIDS_MEAN_RADIUS * sqrtf(fabs(l));
    float phi = getRandomFloat(0, 2 * M_PI);

    // Surprise!
    //phi = 0;

    // https://en.wikipedia.org/wiki/Circular_orbit#Velocity
    float v = sqrtf(GRAVITATIONAL_CONSTANT * centerMass / r) * getRandomFloat(0.6F, 1.2F);
    float vy = getRandomFloat(-1E2F, 1E2F);

    // Fill in with your own fields:
    body->setMass(ASTEROIDS_MEAN_WEIGHT);  // Typical asteroid weight: 1 billion tons
    body->setRadius(ASTEROIDS_MEAN_RADIUS); // Typical asteroid radius: 2km
    body->setColor(GRAY);
    body->setPosition ({r * cosf(phi), 0, r * sinf(phi)});
    body->setVelocity ({-v * sinf(phi), vy, v * cosf(phi)});

}

// Simulates a timestep
void OrbitalSim::updateOrbitalSim()
{
    // Calculation of force and acceleration
    for(size_t i=0 ; i<(SOLARSYSTEM_BODYNUM+N_ASTEROID) ; ++i)
    {
        raylib::Vector3 resultantForce;
        resultantForce.x=0;
        resultantForce.y=0;
        resultantForce.z=0;

        for(size_t j=0;j<SOLARSYSTEM_BODYNUM;++j)
        {
            if(i!=j) 
            {
                raylib::Vector3 unitVector = ( this->bodies[i].getPosition() ) - ( this->bodies[j].getPosition() );
                float vectorMod = Vector3Length(unitVector);
                unitVector *= 1/Vector3Length(unitVector);

                resultantForce += (unitVector) * (-GRAVITATIONAL_CONSTANT*(this->bodies[j].getMass())/(vectorMod*vectorMod));
            }
        }

        raylib::Vector3 acceleration = resultantForce; //No se divide por la masa por la misma razón que en la parte A

        this->bodies[i].setVelocity( this->bodies[i].getVelocity() + (acceleration * (this->timeStep)) );
        this->bodies[i].setPosition( (this->bodies[i].getPosition()) + ((this->bodies[i].getVelocity())*(this->timeStep)) );
    }

    (this->timeElapsed)+=(this->timeStep);    // Time update
}

// Sets the name of an orbital body to a specified value
void OrbitalBody::setName(std::string name)
{
    this->name=name;
}

// Sets the mass of an orbital body to a specified value
void OrbitalBody::setMass(float mass)
{
    this->mass = mass;
}

// Gets the value of the mass of an orbital body
float OrbitalBody::getMass()   
{
    return mass;
}

// Sets the radius of an orbital body to a specified value
void OrbitalBody::setRadius(float radius)
{
    this->radius = radius;
}

// Gets the value of the radius of an orbital body
float OrbitalBody::getRadius()
{
    return radius;
}

// Sets the color of an orbital body
void OrbitalBody::setColor(Color color)
{
    this->color = color;
}

// Gets the color of an orbital body
Color OrbitalBody::getColor()
{
    return color;
}

// Sets the position of an orbital body to a specified value
void OrbitalBody::setPosition(raylib::Vector3 position)
{
    this->position = position;
}

// Gets the value of the position of an orbital body
raylib::Vector3 OrbitalBody::getPosition()
{
    return position;
}

// Sets the velocity of an orbital body to a specified value
void OrbitalBody::setVelocity(raylib::Vector3 velocity)
{
    this->velocity = velocity;
}

// Gets the value of the velocity of an orbital body
raylib::Vector3 OrbitalBody::getVelocity()
{
    return velocity;
}

// Gets the number of bodies of an orbital simulation
int OrbitalSim::getNumberOfBodies()
{
    return numberOfBodies;
}

// Gets the time elapsed since the beggining of an orbital simulation
float OrbitalSim::getTimeElapsed()
{
    return timeElapsed;
}

// Delete the simulation
OrbitalSim::~OrbitalSim()
{
    delete[] bodies;
}