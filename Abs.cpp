//
//  Abs.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "Abs.hpp"
#include "opt_tools.hpp"

/**
 * Abs constructor
 *
 * Constructor for the Abs class
 *
 * @param dimen for the dimension, @param epsilon for the acceptable tolerance for the stop criterion, @param maxIterations is the maximum acceptable number of iteratioons for the stop criterion.
 **/
Abs::Abs(int dimen, double epsilon, int maxIterations){
    dim = dimen;
    eps = epsilon;
    N = maxIterations;
};

/**
 * Stop Function (Gradient)
 *
 * Stop Criterion Function makes sure that the norm of the gradient at the current point is greater than epsilon and the number of iterations has not reached the maximum.
 *
 * @param numOfIter is the current number of iterations, @param grad is the current numerical value of gradient.
 * @return 0 if stop criterion is satisfied, 1 if not.
 **/
bool Abs::stop(int numOfIter, double long *grad){
    return ((numOfIter < N) && (norm(grad, dim) > eps)) ;
}

/**
 * Stop Function
 *
 * Stop Criterion Function makes sure that the stop criterion is satisfied so that the algorithm can stop
 *
 * @param xCurrent is the current point, @param xPrev is the previous chosen point, @param grad is the gradient value, @param numOfIter is the current number of iterations.
 * @return 0 if one of the stop criterions is satisfied, 1 if not.
 **/
bool Abs::stop(double long * xCurrent, double long * xPrev, double long *grad, int numOfIter) {
    bool ans{};
    double long * diff = new double long [dim]{};
    for (int i = 0; i < dim; ++i){
           diff[i] = abs(xCurrent[i] - xPrev[i]);
       }
    if(stopChoice == 'l' || stopChoice == 'x'){
        ans = (norm(diff, dim) > eps) && (numOfIter < N);
    }
    if(stopChoice == 'g'){
        ans = (norm(grad, dim) > eps) && (numOfIter < N);
    }
    
    delete [] diff;
    return ans;
};

/**
 * checkGrad Function
 *
 * @param grad is the gradient value
 * @return 1 if gradient is greater than eps, 0 if not
 *
 **/
bool Abs::checkGrad(double long *grad){
    return (norm(grad, dim) > eps) ? 1 : 0;
};

/**
* Stop Function
*
* Stop Criterion Function makes sure that the stop criterion is satisfied so that the algorithm can stop
*
* @param numOfIter is the current number of iterations,
 *@param itersAfterLastSuccess is the current number of iteration since the last success
* @return 0 if one of the stop criterions is satisfied, 1 if not.
**/
bool Abs::stop(int numOfIter, int itersAfterLastSuccess){
    return (numOfIter < N) || (itersAfterLastSuccess < maxItersAfterLastSuccess);
};
