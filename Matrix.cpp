#include "Matrix.h"
#include <cassert>
#include <iostream>
#include <cmath>


void MatrixTesting()
{
    Matrix a(4,2,2);
    Matrix b(2,3,2);
    std::cout << a.getVal(0,0) << " " << a.getVal(0,1) << std::endl
            << a.getVal(1,0) << " " << a.getVal(1,1) << std::endl << std::endl;
    Matrix c = a * b;
    std::cout << c.getVal(0,0) << " " << c.getVal(0,1) << std::endl
                << c.getVal(1,0) << " " << c.getVal(1,1) << std::endl << std::endl;
    a.setVal(0,0, 1.5);
    a.setVal(1,1, 3);
    c = a * b;
    std::cout << a.getVal(0,0) << " " << a.getVal(0,1) << std::endl
            << a.getVal(1,0) << " " << a.getVal(1,1) << std::endl
            << a.getVal(2,0) << " " << a.getVal(2,1) << std::endl
            << a.getVal(3,0) << " " << a.getVal(3,1) << std::endl << std::endl;
            
    std::cout << c.getVal(0,0) << " " << c.getVal(0,1) << " " << c.getVal(0,2) << std::endl
                << c.getVal(1,0) << " " << c.getVal(1,1) << " " << c.getVal(1,2) << std::endl
                << c.getVal(2,0) << " " << c.getVal(2,1) << " " << c.getVal(2,2) << std::endl
                << c.getVal(3,0) << " " << c.getVal(3,1) << " " << c.getVal(3,2) << std::endl << std::endl;
}

// "m" defines the number of rows, "n" defines the number of columns
Matrix::Matrix(unsigned int m, unsigned int n, float defaultVal) : m_values(m)
{
    std::vector <float> temp(n, defaultVal);
    for( unsigned int i = 0; i < m; ++i )
    {
        m_values[i] = temp;
    }
}


Matrix::Matrix(const std::vector < std::vector <float> > &vals) : m_values(vals)
{
}

Matrix::Matrix(const Matrix &a) : m_values(a.m_values)
{
}

void Matrix::operator=(const Matrix &a)
{
    m_values = a.m_values;
}

float Matrix::getVal(unsigned int m, unsigned int n)
{
    return m_values[m][n];
}

void Matrix::setVal(unsigned int m, unsigned int n, float val)
{
    m_values[m][n] = val;
}

unsigned int Matrix::getRows()
{
    return m_values.size();
}

unsigned int Matrix::getCols()
{
    return m_values[0].size();
}

//Maybe be cool and rewrite some of this in OpenCL/CUDA/openMP one day
Matrix operator*(const Matrix &a, const Matrix &b)
{
    assert(a.m_values[0].size() == b.m_values.size());
    Matrix result(a.m_values.size(), b.m_values[0].size(), 0);
    unsigned int m = a.m_values.size();
    unsigned int n = b.m_values[0].size();
    unsigned int u = a.m_values[0].size();
    for(unsigned int i = 0; i < m; ++i)
    {
        for(unsigned int j = 0; j < n; ++j)
        {
            float temp = 0;
            for(unsigned int k = 0; k < u; ++k)
            {
                temp += a.m_values[i][k] * b.m_values[k][j];
            }
            result.m_values[i][j] = temp;
        }
    }
    return result;
}

Matrix operator+(const Matrix &a, const Matrix &b)
{
    assert((a.m_values[0].size() == b.m_values[0].size()) && (a.m_values.size() == b.m_values.size()));
    Matrix result(a.m_values.size(), a.m_values[0].size(), 0);
    unsigned int m = a.m_values.size();
    unsigned int n = a.m_values[0].size();;
    for(unsigned int i = 0; i < m; ++i)
    {
        for(unsigned int j = 0; j < n; ++j)
        {
            result.m_values[i][j] = a.m_values[i][j] + b.m_values[i][j];
        }
    }
    return result;
}

Matrix tanh(const Matrix &a)
{
    Matrix result(a.m_values.size(), a.m_values[0].size(), 0);
    unsigned int m = a.m_values.size();
    unsigned int n = a.m_values[0].size();;
    for(unsigned int i = 0; i < m; ++i)
    {
        for(unsigned int j = 0; j < n; ++j)
        {
            result.m_values[i][j] = tanh(a.m_values[i][j]);
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix &a)
{
    for(int i = 0; i < a.m_values.size(); ++i)
    {
        for(int j = 0; j < a.m_values[i].size(); ++j)
        {
            os << a.m_values[i][j] << " ";
        }
        os << std::endl;
    }  
    return os;      
}
