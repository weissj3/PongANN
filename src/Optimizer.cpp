#include "Optimizer.h"
#include <limits>

Parameters::Parameters(unsigned int numParams, unsigned int id, float like) : m_values(numParams, 0), m_id(id), m_likelihood(like)
{
}

Parameters::Parameters(const std::vector <float> &other, unsigned int id, float like) : m_values(other), m_id(id), m_likelihood(like)
{
}

Optimizer::Optimizer(unsigned int populationSize, unsigned int numParams) : m_rd(), m_mt(m_rd()), m_dist(0.0, 1.0), m_currentResult(0), m_parameters(populationSize, Parameters(numParams, 0)), m_upperBound(numParams, 1.0), m_lowerBound(numParams, 0.0)
{
    for(int i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i].m_id = i;
        for( int j = 0; j < m_parameters[i].m_values.size(); j++ )
        {
            m_parameters[i].m_values[j] = m_dist(m_mt);
        }
    }
}

Optimizer::Optimizer(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower) : m_rd(), m_mt(m_rd()), m_dist(0.0, 1.0), m_currentResult(0), m_parameters(populationSize, Parameters(numParams, 0)), m_upperBound(upper), m_lowerBound(lower)
{
    
    for(int i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i].m_id = i;
        for( int j = 0; i < m_parameters[i].m_values.size(); j++ )
        {
            m_parameters[i].m_values[j] = m_dist(m_mt) * (m_upperBound[j] - m_lowerBound[j]) + m_lowerBound[j];
        }
    }
}

void Optimizer::insertParams(const Parameters &result)
{
    if(m_parameters[result.m_id].m_likelihood < result.m_likelihood)
    {
        m_parameters[result.m_id] = result;
    }
}

Parameters Optimizer::getParameter(unsigned int id)
{
    return m_parameters[id];
}

unsigned int Optimizer::getPopulationSize()
{ 
    return m_parameters.size();
}
