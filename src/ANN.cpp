#include "ANN.h"
#include <random>
#include <fstream>
#include <iostream>


//Matrix (row, col)

//Add 1 to layers for output layer
ANN::ANN(unsigned int inputs, unsigned int nodes, unsigned int hidden_layers, unsigned int outputs) : m_layers(hidden_layers+1, arma::Mat <float>(nodes,nodes))
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::normal_distribution<float> dist(0.0, 2.0);
    m_layers[0].resize(inputs, nodes);
    m_layers[m_layers.size()-1].resize(nodes, outputs);
    for(int i = 0; i < m_layers.size(); i++)
    {
        for(int j = 0; j < m_layers[i].n_cols; ++j)
        {
            for(int k = 0; k < m_layers[i].n_rows; ++k)
            {
                m_layers[i](k, j) = dist(mt);
            }
        }
    }
}

//Add 1 to layers for output layer
ANN::ANN(unsigned int inputs, unsigned int nodes, unsigned int hidden_layers, unsigned int outputs, const Parameters &params) : m_layers(hidden_layers+1, arma::Mat <float>(nodes,nodes))
{
    m_layers[0].resize(inputs, nodes);
    m_layers[m_layers.size()-1].resize(nodes, outputs);
    int count = 0;
    for(int i = 0; i < m_layers.size(); i++)
    {
        for(int j = 0; j < m_layers[i].n_rows; ++j)
        {
            if(count == params.m_values.size())
            {
                std::cerr << "Parameter Size doesn't match ANN Size.  Quitting." << std::endl;
                exit(-1);
            }
            for(int k = 0; k < m_layers[i].n_cols; ++k)
            {
                m_layers[i](j, k) = params.m_values[count];
                ++count;
            }
        }
    }
}

void ANN::Print(std::string filename)
{
    std::ofstream output;
    
    output.open(filename);
    if(!output.is_open())
    {
        std::cerr << "Failed to open save file" << std::endl;
    }
    
    //Print header
    output << "<ANN>\n";
    output << "<Layers>\n" << m_layers.size() << std::endl << "</Layers>\n"
            << "<Nodes>\n" << m_layers[0].n_rows << std::endl << "</Nodes>\n"
            << "<Outputs>\n" << m_layers[0].n_rows << std::endl << "</Outputs>\n";
    for(int i = 0; i < m_layers.size(); ++i)
    {
        output << "<Matrix>\n" << m_layers[i] << "</Matrix>\n";
    }
    output << "</ANN>\n";
}


//finish implementing this later
void ANN::Read(std::string filename)
{
    std::ifstream input;
    
    input.open(filename);
    std::string temp;
    
    while(input >> temp)
    {
        
    }
}

std::vector<float> ANN::Evaluate(std::vector<float> input)
{
    //Create input matrix from input
    arma::Mat <float> inputMat(1, input.size());
    for( unsigned int i = 0; i < inputMat.n_rows; ++i )
    {
        for( unsigned int j = 0; j < inputMat.n_cols; ++j )
        {
            inputMat(i, j) = input[j];
        }
    }

    //Run Feed Forward
    for( unsigned int i = 0; i < m_layers.size(); ++i )
    {       
        inputMat = tanh(inputMat * m_layers[i]);
    }

    //Create output vector
    std::vector <float> output(inputMat.n_rows, 0);
    for( unsigned int i = 0; i < inputMat.n_cols; ++i )
    {
        output[i] = inputMat(0, i);
    }
    return output;
}
