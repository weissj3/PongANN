#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <iostream>

class Matrix
{
private:
    std::vector < std::vector <float> > m_values;
    
public:

    friend std::ostream& operator<<(std::ostream& os, const Matrix &a);
    friend Matrix tanh(const Matrix &a);
    friend Matrix operator*(const Matrix &a, const Matrix &b);
    friend Matrix operator+(const Matrix &a, const Matrix &b);
    Matrix(unsigned int m, unsigned int n, float defaultVal);
    Matrix(const std::vector < std::vector <float> > &vals);
    Matrix(const Matrix &a);
    float getVal(unsigned int m, unsigned int n);
    void setVal(unsigned int m, unsigned int n, float val);
    void operator=(const Matrix &a);
    unsigned int getRows();
    unsigned int getCols();

};

void MatrixTesting();

#endif
