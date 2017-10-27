#include "DifferentialEvolution.h"

DifferentialEvolution::DifferentialEvolution(unsigned int populationSize, unsigned int numParams) : Optimizer(populationSize, numParams)
{
}

DifferentialEvolution::DifferentialEvolution(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower) : Optimizer(populationSize, numParams, upper, lower)
{
}

Parameters DifferentialEvolution::getNewParams()
{
    std::uniform_int_distribution <unsigned int> getRandomParam(0, m_parameters.size());
    Parameters newParameters = m_parameters[m_currentResult];
    newParameters.m_likelihood = 0;
    Parameters Parent = m_parameters[0];
    //Always using the best parameter set as the 
    for(int i = 0; i < m_parameters.size(); ++i)
    {
        if(m_parameters[i].m_likelihood > Parent.m_likelihood)
        {
            Parent = m_parameters[0];
        }
    }
    
    //Calculate differential and add to parent
    std::vector<float> u1, u2;
    u1 = m_parameters[getRandomParam(m_mt)].m_values;
    u2 = m_parameters[getRandomParam(m_mt)].m_values;
    for(int i = 0; i < u1.size(); i++)
    {
        Parent.m_values[i] += u1[i] - u2[i];
    }

    //Recombine
    for(int i = 0; i < u1.size(); i++)
    {
        if(m_dist(m_mt) > .5)
        {
            newParameters.m_values[i] = Parent.m_values[i];
        }
    }
    
    ++m_currentResult;
    return newParameters;
}

void DifferentialEvolution::Print(std::string filename)
{

}
