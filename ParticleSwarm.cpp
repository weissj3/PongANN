#include "ParticleSwarm.h"

ParticleSwarm::ParticleSwarm(unsigned int populationSize, unsigned int numParams) : Optimizer(populationSize, numParams)
{
    int counter = 0;
    for(int i = 0; i < populationSize; ++i)
    {
        for(int j = 0; j < numParams; ++j)
        {
            m_particles[i].m_vel = 
}
