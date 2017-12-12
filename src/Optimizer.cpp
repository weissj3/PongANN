#include "Optimizer.h"
#include <limits>
#include <iostream>
#include <cfloat>

Parameters::Parameters(unsigned int numParams, unsigned int id, float like) : m_values(numParams, 0), m_id(id), m_likelihood(like)
{
}

Parameters::Parameters(const std::vector <float> &other, unsigned int id, float like) : m_values(other), m_id(id), m_likelihood(like)
{
}

std::istream& operator>>(std::istream & istr, Parameters & param)
{
    while(!istr.eof())
    {
        std::string temp;
        istr >> temp;
        if(temp == "</parameters>")
        {
            break;
        }
        if(temp == "<id>")
        {
            istr >> param.m_id;
            istr >> temp;
        }
        if(temp == "<likelihood>")
        {
            istr >> param.m_likelihood;
            istr >> temp;
        }
        if(temp == "<values>")
        {
            while(!istr.eof())
            {
                istr >> temp;
                if(temp == "</values>")
                {
                    break;
                }
                param.m_values.push_back(std::stof(temp));
            }
        }
        
    }  
    return istr;
}

std::ostream& operator<<(std::ostream & ostr, const Parameters & param)
{
    ostr << "<parameters>" << std::endl;
    ostr << "<id>" << std::endl;
    ostr << "\t" << param.m_id << std::endl;
    ostr << "</id>" << std::endl;
    ostr << "<likelihood>" << std::endl;
    ostr << "\t" << param.m_likelihood << std::endl;
    ostr << "</likelihood>" << std::endl;
    ostr << "<values>" << std::endl;
    ostr << "\t";
    for(unsigned int i = 0; i < param.m_values.size(); ++i)
    {
        ostr << param.m_values[i] << "   ";
    }
    ostr << std::endl;
    ostr << "</values>" << std::endl;
    ostr << "</parameters>" << std::endl;
    return ostr;
}

Optimizer::Optimizer() :  m_rd(), m_mt(m_rd()), m_dist(0.0, 1.0), m_normDist(0.0, 2.0), m_currentResult(0), m_currentGeneration(0)
{
}

Optimizer::Optimizer(unsigned int populationSize, unsigned int numParams) : m_rd(), m_mt(m_rd()), m_dist(0.0, 1.0), m_normDist(0.0, 2.0), m_currentResult(0), m_currentGeneration(0), m_parameters(populationSize, Parameters(numParams, FLT_MIN)), m_upperBound(numParams, FLT_MAX), m_lowerBound(numParams, 0.0)
{
    for(int i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i].m_id = i;
        for( int j = 0; j < m_parameters[i].m_values.size(); j++ )
        {
            m_parameters[i].m_values[j] = m_normDist(m_mt);
        }
    }
}

Optimizer::Optimizer(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower) : m_rd(), m_mt(m_rd()), m_dist(0.0, 1.0), m_normDist(0.0, 2.0), m_currentResult(0), m_currentGeneration(0), m_parameters(populationSize, Parameters(numParams, 0)),  m_upperBound(upper), m_lowerBound(lower)
{
    
    for(int i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i].m_id = i;
        for( int j = 0; j < m_parameters[i].m_values.size(); j++ )
        {
            do
            {
                m_parameters[i].m_values[j] = m_normDist(m_mt);
            } while(m_parameters[i].m_values[j] < lower[j] || m_parameters[i].m_values[j] > upper[j]);
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
