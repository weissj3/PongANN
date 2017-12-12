#include "DifferentialEvolution.h"
#include <iostream>


DifferentialEvolution::DifferentialEvolution() : Optimizer()
{
}

DifferentialEvolution::DifferentialEvolution(unsigned int populationSize, unsigned int numParams) : Optimizer(populationSize, numParams)
{
}

DifferentialEvolution::DifferentialEvolution(unsigned int populationSize, unsigned int numParams, const std::vector <float> &upper, const std::vector <float> &lower) : Optimizer(populationSize, numParams, upper, lower)
{
}

Parameters DifferentialEvolution::getNewParams()
{
    std::uniform_int_distribution <unsigned int> getRandomParam(0, m_parameters.size()-1);
    Parameters newParameters = m_parameters[m_currentResult];
    newParameters.m_likelihood = 0;
    Parameters Parent = m_parameters[0];
    //Always using the best parameter set as the 
    for(int i = 0; i < m_parameters.size(); ++i)
    {
        if(m_parameters[i].m_likelihood > Parent.m_likelihood)
        {
            Parent = m_parameters[i];
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
        bool runAgain = false;
        int count = 0;
        do {
            runAgain = false; 
            if (newParameters.m_values[i] < m_lowerBound[i]) 
            {
	            newParameters.m_values[i] = m_lowerBound[i] + (m_lowerBound[i] - newParameters.m_values[i]);
                runAgain = true;
                ++count;
            }
            if (newParameters.m_values[i] > m_upperBound[i]) 
            {
                newParameters.m_values[i] = m_upperBound[i] + (m_upperBound[i] - newParameters.m_values[i]);
                runAgain = true;
                ++count;
            }
            if (count > 20) 
            {
                std::string error; 
                error = "ERROR: bound_parameters has looped >20 times.  Infinite loop detected.";
                throw error;
            }
        } while(runAgain);
    }
    
    ++m_currentResult;
    if(m_currentResult == m_parameters.size())
    {
        m_currentResult = 0;
        ++m_currentGeneration;
    }
    return newParameters;
}

std::ostream& operator<<(std::ostream & ostr, const DifferentialEvolution &DE)
{
    ostr << "<DifferentialEvolution>" << std::endl;
    ostr << "\t<CurrentResult>" << std::endl;
    ostr << "\t\t" << DE.m_currentResult<< std::endl;
    ostr << "\t</CurrentResult>" << std::endl;
    ostr << "\t<CurrentGeneration>" << std::endl;
    ostr << "\t\t" << DE.m_currentGeneration<< std::endl;
    ostr << "\t</CurrentGeneration>" << std::endl;
    ostr << "\t<ParameterList>" << std::endl;
    for(unsigned int i = 0; i < DE.m_parameters.size(); ++i)
    {
        ostr << DE.m_parameters[i];
    }
    ostr << "\t</ParameterList>" << std::endl;
    ostr << "</DifferentialEvolution>" << std::endl;
}

std::istream& operator>>(std::istream & istr, DifferentialEvolution & DE)
{
    DE.m_parameters.clear();
    while(!istr.eof())
    {
        std::string temp;
        istr >> temp;
        if(temp == "</DifferentialEvolution>")
        {
            break;
        }
        if(temp == "<CurrentResult>")
        {
            istr >> DE.m_currentResult;
            istr >> temp;
        }
        if(temp == "<CurrentGeneration>")
        {
            istr >> DE.m_currentGeneration;
            istr >> temp;
        }
        if(temp == "<ParameterList>")
        {
            while(!istr.eof())
            {
                istr >> temp;
                if(temp == "</ParameterList>")
                {
                    break;
                }
                if(temp == "<parameters>")
                {
                    Parameters tempParam;
                    istr >> tempParam;
                    DE.m_parameters.push_back(tempParam);
                }
            }
        }
        
    }  
    return istr;
}
