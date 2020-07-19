#include "EyerMath.hpp"

#include <stdio.h>
#include <stdlib.h>

namespace Eyer {
    EyerMat::EyerMat(int row, int col)
    {
        this->row = row;
        this->col = col;

        init(row, col);
    }

    EyerMat::EyerMat(const EyerMat &m)
    {
        this->row = m.row;
        this->col = m.col;

        init(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    EyerMat::~EyerMat()
    {
        if (mat != nullptr) {
            for (int i = 0; i < row; i++){
                if (mat[i]) {
                    delete[] mat[i];
                    mat[i] = nullptr;
                }
            }
            if (mat){
                delete[] mat;
            }   
            mat = nullptr;
        }
    }

    EyerMat & EyerMat::operator = (const EyerMat &m)
    {
        if (mat != nullptr) {
            for (int i = 0; i < row; i++){
                if (mat[i]) {
                    delete[] mat[i];
                    mat[i] = nullptr;
                }
            }
            if (mat){
                delete[] mat;
            }
            mat = nullptr;
        }

        row = m.row;
        col = m.col;

        init(row, col);
        for (int i = 0; i < row; i++){
            for (int j = 0; j < col; j++){
                mat[i][j] = m.mat[i][j];
            }
        }

        return *this;
    }

    EyerMat EyerMat::operator + (const EyerMat &m) {
        EyerMat res(m.row, m.col);
        if (row == m.row && col == m.col) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] + m.mat[i][j];
                }
            }
        } 
        else{

        }
        return res;
    }

    EyerMat EyerMat::operator - (const EyerMat &m)
    {
        EyerMat res(m.row, m.col);
        if (row == m.row && col == m.col) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] - m.mat[i][j];
                }
            }
        } 
        else{

        }

        return res;
    }

    EyerMat EyerMat::operator * (const EyerMat &m)
    {
        EyerMat res(row, m.col);
        
        for (int i = 0; i < res.row; i++) {
            for (int j = 0; j < res.col; j++) {
                res.mat[i][j] = 0.0f;
            }
        }

        if (m.row != col){

        }
        else {
            for (int i = 0; i < res.row; i++) {
                for (int j = 0; j < res.col; j++) {
                    for (int k = 0; k < res.row; k++) {
                        res.mat[i][j] += mat[i][k] * m.mat[k][j];
                    }
                }
            }
        }
            
        return res;
    }


    EyerMat EyerMat::operator * (const float a)
    {
        EyerMat res(row, col);
        // if (row == row && col == col) {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    res.mat[i][j] = mat[i][j] * a;
                }
            }
        // } 
        // else{

        // }

        return res;
    }

    EyerMat EyerMat::operator ~ ()
    {
        EyerMat res(row, col);
        // printf("\n");
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                // printf("[%d][%d] ", i, j);
                res.mat[i][j] = mat[j][i];
            }
            // printf("\n");
        }
        return res;
    }

    /*
    SvMat SvMat::operator ! ()
    {
        SvMat res(row, col);

        return res;
    }
    */

    void EyerMat::init(int row, int col)
    {
        if (row && col) {
            mat = new float*[row];
            for (int i = 0; i < row; i++) {
                mat[i] = new float[col];
                for (int j = 0; j < col; j++){
                    mat[i][j] = 0;
                    if(i == j){
                        mat[i][j] = 1;
                    }
                }
            }
        }
    }

    void EyerMat::output() {
        printf("output:(%d,%d)\n", row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++){
                printf(" %.2f ", mat[i][j]);
            }
            printf("\n");
        }
    }

    int EyerMat::Print()
    {
        output();
        return 0;
    }

    int EyerMat::GetMatLen()
    {
        return this->col * this->row * sizeof(float);
    }

    float * EyerMat::GetMat(float * matBuffer)
    {
        if(matBuffer == NULL) {
            matBuffer = (float *)malloc(GetMatLen());
        }

        // memset(matBuffer, 0, GetMatLen());

        int index = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++){
                matBuffer[index] = mat[i][j];
                index++;
            }
        }

        return matBuffer;
    }
}