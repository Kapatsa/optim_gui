//
//  Function.cpp
//  optimization_console
//
//  Created by David Kapatsa on 08.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "Function.hpp"

long double Function::grad(long double *x, int varInd){
    long double gr;
    long double * x_h = new long double [dim];
    for(int i = 0; i < dim; ++i) {i == varInd ? (x_h[i] = x[i] + h) : (x_h[i] = x[i]);}
    gr = (eval(x_h) - eval(x))/h;
    delete [] x_h;
    return gr;
    };
