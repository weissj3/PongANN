#ifndef _PARTICLE_SWARM_H_
#define _PARTICLE_SWARM_H_

#include "Optimizer.h"
#include <vector>


class DifferentialEvolution : public Optimizer
{
public:
    DifferentialEvolution(unsigned int populationSize, unsigned int numParams);
    DifferentialEvolution(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower);
    void Print(std::string filename);
    virtual Parameters getNewParams();


};

#endif
