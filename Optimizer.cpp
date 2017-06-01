#include "Optimizer.h"
#include <limits>

Parameters::Parameters(unsigned int numParams, bool setRandom=0) : m_id(std::numeric_limits<unsigned int>::max()), m_values(numParams, 0), m_likelihood(std::numeric_limits<float>::min())
{
    if(setRandom)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(0.0, 1.0);
        for(int i = 0; i < m_values.size(); ++i)
        {
            m_values[i] = dist(mt);
        }
    }
}

Parameters::Parameters(const std::vector <float> &other) : m_id(std::numeric_limits<unsigned int>::max()), m_values(other), m_likelihood(std::numeric_limits<float>::min())
{
}

Optimizer::Optimizer(unsigned int populationSize, unsigned int numParams) : m_currentResult(0), m_parameters(populationSize, Parameters(numParams, 1))
{
    for(int i = 0; i < m_parameters.size(); ++i)
    {
        m_parameters[i].id = i;
    }
}

void Optimizer::returnResult(const Parameters &result)
{
    m_parameters[result.id].likelihood = result.likelihood;
}


Parameters Optimizer::getNewParams()
{
    if(m_currentResult == m_parameters.size())
    {
        m_currentResult = 0;
        update();
    }
    ++m_currentResult;
    //Minus 1 so we can increment and return easier.
    return m_parameters[m_currentResult-1];
}
