#ifndef _ANN_H_
#define _ANN_H_
#include <vector>
#include <string>
#include <armadillo>
#include "Optimizer.h"


class ANN
{
private:
    
    std::vector <arma::Mat <float> > m_layers;    

public:
    ANN(unsigned int nodes, unsigned int layers, unsigned int outputs);
    ANN(unsigned int nodes, unsigned int hidden_layers, unsigned int outputs, const Parameters &params);    
    
    void Print(std::string filename);
    void Read(std::string filename);
    std::vector<float> Evaluate(std::vector<float> input);
    
};

#endif
