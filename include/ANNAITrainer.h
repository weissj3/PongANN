#ifndef _ANNAITRAINER_H_
#define _ANNAITRAINER_H_
#include "ANNAI.h"
#include "DifferentialEvolution.h"

class ANNAITrainer
{
private:
    ANNAI *m_player1;
    ANNAI *m_player2;
    DifferentialEvolution m_DE;

public:

    ANNAITrainer(ANNAI* p1, ANNAI* p2, unsigned int populationSize = 20, unsigned int n_layers = 2, unsigned int n_nodes = 3);
    void Update();

};

#endif
