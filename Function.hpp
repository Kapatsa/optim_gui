//
//  Function.hpp
//  optimization_console
//
//  Created by David Kapatsa on 08.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

//TODO:: transfer all definitions to the cpp file

/**
 * Abstract Function Class
 * 
 * In order to add a function just create an instance of the Function class, input dimension and add the evaluate function, just as in examples provided.
 **/
class Function {
public:
    int dim;
    long double h = 1e-9;
    Function(){};
    ~Function(){};
    virtual std::string getExpr() = 0;
    virtual long double eval(long double *x) = 0;
    long double grad(long double *x, int varInd);
};

class f1: public Function{
public:
    f1(){
        dim = 2;
    };
    ~f1(){};
    std::string getExpr() override {
        return " f(x,y) = 0.1*cos(10*(x^2 + y^2)) ";
    };
    long double eval(long double *x) override {
        return 0.10 * cos(10*(x[0]*x[0] + x[1]*x[1]));
    };
    
};

class f2: public Function{
public:
    f2(){
        dim = 3;
    };
    ~f2(){};
    long double eval(long double *x) override {
        return ((x[0]-0.5)*(x[0]-0.5) + x[1]*x[1] + x[2]*x[2] + 1);
    };
    std::string getExpr() override {
        return " f(x, y, z) = (x-0.5)^2 + y^2 + z^2 + 1 ";
    };
};


class f3: public Function{
public:
    f3(){
        dim = 2;
    };
    ~f3(){};
    std::string getExpr() override {
        return " f(x,y) = x + y ";
    };
    long double eval(long double *x) override {
        return x[0]+x[1];
    };
    
};

class f4: public Function{
public:
    f4(){
        dim = 2;
    };
    ~f4(){};
    std::string getExpr() override {
        return " f(x,y) = (1-x)^2 + 100 * (y-x^2)^2 ";
    };
    long double eval(long double *x) override {
        return (1 - x[0])*(1 - x[0]) + 100 * (x[1]-x[0]*x[0])*(x[1]-x[0]*x[0]);
    };
    
};


#endif /* Function_hpp */
