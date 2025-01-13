#pragma once
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>

using namespace std;

template<typename Type>
class Matrix {


    size_t cols;
    size_t rows;


public:
    vector<Type> data;
    tuple<size_t, size_t> shape;
    int nume1 = rows * cols;

    /* Constructors */
    Matrix(size_t rows, size_t cols)
        : cols(cols), rows(rows), data({}){

            data.resize(cols * rows, Type()); // init empty vector for data
            shape = {rows, cols};

        }
    Matrix() : cols(0), rows(0), data({}) { shape = {rows, cols};  };



    // shape printer for debugging, PyTorch style formatting

    void print_shape(){
        cout << "Matrix Size ([" << rows << ", " << cols << "])" << endl;
    }

    void print() {
        for (size_t r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                cout << (*this)(r, c) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // Accessing Matrix Elements
    Type& operator()(size_t row, size_t col){
        return data[row * cols + col];
    }

    //O(rows^2 * cols) time | O(rows*cols) space
    Matrix matmul(Matrix &target) {
        assert(cols == target.rows);
        Marix output(rows, target.cols);


        for (size_t r =0; r < output.rows; ++r){
            for (size_t c =0; c < output.cols; ++c){
                for (size_t k = 0; k < target.rows; ++k)
                    output(r, c) += (*this)(r, k) * target(k, c);
            }
        }

        return output;
    }

    // O(rows*cols) time | O(rows*cols) space
    Matrix multiply_elementwise(Matrix &target){

        assert(shape == target.shape);
        Matrix output((*this));
            for (size_t r =0; r < output.rows; ++r){
                for (size_t c = 0; c < output.cols; ++c){
                    output(r, c) = target(r,c) * (*this)(r, c);
                }
            }
            return output;
    }

    // O(rows*cols) time | O(rows*cols) space
    Matrix square() {
        Matrix output((*this));
        output = multiply_elementwise(output);
        return output;
    }

    // O(rows*cols) time | O(rows*cols) space
    MAtrix multiply_scalar(Type scalar) {
        Matrix output((*this));
        for (size_t r = 0; r < output.rows; ++r){
            for (size_t c = 0; c < output.cols; ++c){
                output(r, c) = scalar * (*this)(r, c);
            }
        }
        return output;
    }

};