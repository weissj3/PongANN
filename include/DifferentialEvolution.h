#ifndef _PARTICLE_SWARM_H_
#define _PARTICLE_SWARM_H_

#include "Optimizer.h"
#include <vector>


class DifferentialEvolution : public Optimizer
{
public:
    DifferentialEvolution();
    DifferentialEvolution(unsigned int populationSize, unsigned int numParams);
    DifferentialEvolution(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower);
    friend std::ostream& operator<<(std::ostream & ostr, const DifferentialEvolution &DE);
    friend std::istream& operator>>(std::istream & istr, DifferentialEvolution & DE);
    virtual Parameters getNewParams();

};

#endif
