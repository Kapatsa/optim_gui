//
//  StopCriterion.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef StopCriterion_hpp
#define StopCriterion_hpp

#include <stdio.h>
/**
 * Stop Criterion Class
 *
 * Main objective of this class is to provide virtual functions stop() with different arguments, which currently is being overridden by the corresponding functions in Abs class
 **/
class StopCriterion {
public:
    double long eps = 1e-6; //minimal eps for gradient
    int N = 5000;
    int maxItersAfterLastSuccess = 500;
    int dim;
    char stopChoice;
    StopCriterion(){};
    ~StopCriterion(){};
    virtual bool stop(int numOfIter, double long *grad) = 0;
    virtual bool stop(double long * xCurrent, double long * xPrev, double long *grad, int numOfIter) = 0;
    virtual bool stop(int numOfIter, int itersAfterLastSuccess) = 0;
    virtual bool checkGrad(double long *grad) = 0;
    void SetDim(int num){dim = num;};
    void SetEps(double long num){eps = num;}
    void SetN(int num){N = num;}
    void SetMaxItersAfterLast(int num){maxItersAfterLastSuccess = num;}
    void SetStopChoice(char l){stopChoice = l;}
    char GetStopChoice(){return stopChoice;}
    //void SetMaxAfterLast();
    //void SetIter
};

#endif /* StopCriterion_hpp */
