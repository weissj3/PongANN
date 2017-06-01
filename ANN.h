#ifndef _ANN_H_
#define _ANN_H_
#include <vector>
#include <string>
#include "Matrix.h"

class ANN
{
private:
    
    std::vector <Matrix> m_layers;    

public:
    ANN(unsigned int nodes, unsigned int layers, unsigned int outputs);
    
    void Print(std::string filename);
    void Read(std::string filename);
    std::vector<float> Evaluate(std::vector<float> input);
    
};

#endif
