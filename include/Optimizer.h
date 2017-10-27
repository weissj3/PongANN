#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <vector>
#include <random>

struct Parameters
{
    unsigned int m_id;
    float m_likelihood;
    std::vector <float> m_values;

    Parameters(unsigned int numParams, unsigned int id, float like = 1);
    Parameters(const std::vector <float> &other, unsigned int id, float like = 1);
    Parameters() {}
};

class Optimizer
{
protected:
    unsigned int m_currentResult;
    std::random_device m_rd;
    std::mt19937 m_mt;
    std::uniform_real_distribution<float> m_dist;

    std::vector<Parameters> m_parameters;
    std::vector<float> m_upperBound;
    std::vector<float> m_lowerBound;

public:
    Optimizer(unsigned int populationSize, unsigned int numParams);
    Optimizer(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower);
    void insertParams(const Parameters &result);
    virtual Parameters getNewParams() = 0;
    Parameters getParameter(unsigned int id);
    unsigned int getPopulationSize();
};

#endif
