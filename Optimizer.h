#ifndef _OPTIMIZER_H_
#define _OPTIMIZER_H_

#include <vector>

struct Parameters
{
    float m_likelihood;
    std::vector <float> m_values;
    unsigned int m_id;

    Parameters(unsigned int numParams, bool setRandom=0);
    Parameters(const std::vector <float> &other);
};

class Optimzer
{
private:

    unsigned int m_currentResult;

    virtual void update() = 0;

protected:

    std::vector<Parameters> m_parameters;

public:
    Optimizer(unsigned int populationSize, unsigned int numParams);
    
    void returnResult(const Parameters &result);
    Parameters getNewParams();
    
};

#endif
