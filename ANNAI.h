#ifndef _ANNAI_H_
#define _ANNAI_H_

#include "ANN.h"
#include "Player.h"

class ANNAI : public Player
{
private:

    ANN m_ANN;

    void Logic();

public:

    ANNAI(unsigned int playerNum, unsigned int n_layers = 2, unsigned int n_nodes = 3);


};

#endif
