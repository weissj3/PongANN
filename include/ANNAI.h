#ifndef _ANNAI_H_
#define _ANNAI_H_

#include "ANN.h"
#include "Player.h"
#include "DifferentialEvolution.h"

class ANNAI : public Player
{
private:
    
    ANN m_ANN;
    
    Parameters m_currentParams;
    unsigned int m_n_layers, m_n_nodes, m_n_inputs, m_n_outputs;
    
    void Logic();

public:

    ANNAI(unsigned int playerNum, unsigned int n_layers = 3, unsigned int n_nodes = 3);
    void updateParameters(const Parameters &newParams);
    Parameters& getParams();
    unsigned int GetNumParams();

};

#endif
