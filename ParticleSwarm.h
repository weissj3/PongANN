#ifndef _PARTICLE_SWARM_H_
#define _PARTICLE_SWARM_H_

#include "Optimizer.h"
#include <vector>


class ParticleSwarm : public Optimizer
{
private:
    struct Particle
    {
        unsigned int m_id;
        vector<float> m_vel;
        vector<float> m_localBest;
    };
    
    vector<Particle> m_particles;
    Parameters m_globalBest;
    

    virtual void update();

public:
    ParticleSwarm(unsigned int populationSize, unsigned int numParams);
    void Print(std::string filename);


};

#endif
