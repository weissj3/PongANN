#include "ANNAITrainer.h"
#include <fstream>


ANNAITrainer::ANNAITrainer(ANNAI* p1, ANNAI* p2, unsigned int populationSize) : m_player1(p1), m_player2(p2), m_DE(populationSize, p1->GetNumParams())
{
    m_player1->updateParameters(m_DE.getParameter(0));
    m_player2->updateParameters(m_DE.getNewParams());
    m_generation = 0;
}


//Should be called at the end of every game
void ANNAITrainer::Update()
{
    m_player2->getParams().m_likelihood += m_player2->GetScore() * (m_player1->getParams().m_likelihood / (100.0));
    if(m_player1->getParams().m_id < m_DE.getPopulationSize() - 1)
    {
        m_player1->updateParameters(m_DE.getParameter(m_player1->getParams().m_id + 1));

    }
    else
    {
        std::cout << "Likelihood: " << m_player2->getParams().m_likelihood << std::endl;
        m_player1->updateParameters(m_DE.getParameter(0));
        m_DE.insertParams(m_player2->getParams());
        m_player2->updateParameters(m_DE.getNewParams());
        ++m_generation;
        std::ofstream output;
        output.open("DE_Iteration.xml");
        output << m_DE;
        output.close();
    }
}
