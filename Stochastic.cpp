//
//  Stochastic.cpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "Stochastic.hpp"
#include "opt_tools.hpp"

std::mt19937 gen;
std::uniform_real_distribution<> draw{0,1};
using namespace std;

/**
 * Stochastic constructor
 *
 * Constructor which sets the starting point and the dimension for the stochastic method
 * @param xstart is a starting point, @param dimen is the dimension
 **/
Stochastic::Stochastic(double long * xstart, int dimen, long double localProb, long double deltaIn, long double iterSc){
    dim = dimen;
    xFin = new double long [dim]{};
    x0 = new double long [dim];
    for (int i = 0; i < dim; ++i){
        x0[i] = xstart[i];
    }
    localProbability = localProb;
    deltaInit = deltaIn;
    iterScale = iterSc;
};

/**
 * Stochastic Optimization
 * Optimizes a given function inside a bounded area using the stochastic method.
 * @param area is a bounded area,
 * @param func is a function,
 * @param stopCrit is a chosen stop criterion,
 * @return Minimal value is returned, argmin is set inside class
 **/
double long Stochastic::optimize(Area * area, Function * func, StopCriterion * stopCrit) {
    
    gen.seed(1);
    nIter = 0;
    int itersAfterLastSuccess = 0;
    
    //INITIALIZATION
    
    int dim = func -> dim;
    
    //CREATING A DISTRIBUTION FOR THE GLOBAL AREA
    std::uniform_real_distribution<> ** uGlobal  = new std::uniform_real_distribution<>*[dim];
    for (int i = 0; i < dim; ++i){
        uGlobal[i] = new std::uniform_real_distribution<>{static_cast<double>(area -> getRange()[2*i]), static_cast<double>(area -> getRange()[2*i+1])} ;
    }
    //DISTRIBUTION FOR THE LOCAL AREA AND A POINTER FOR LOCAL RANGE ARRAY
    std::uniform_real_distribution<> ** uLocal  = new std::uniform_real_distribution<>*[dim];
    double long * rangeLocal = new double long [2*dim];
    
    //DISTRIBUTION FOR SWITCHING BETWEEN GLOBAL AND LOCAL SEARCH
    std::discrete_distribution<int> d {static_cast<double>(localProbability),static_cast<double>(1-localProbability)};
    
    // randInside TEST
    {
        //double long * pt = new double long [dim];
        //for (int i = 0; i < 100; ++i) randomInside(pt, dim, u, gen);
        //delete [] pt;
    }
    // rangeAroundEps TEST
    {
        //double long * localRange = new double long[2*dim];
        //print(rangeAroundEps(localRange, x0, 0.2, dim, area->getRange()), 2*dim);
        //delete [] localRange;
    }
    // discrete distribution TEST
    /*
    TODO: Check that discrete works properly from the beginning
    {
        std::cout << std::endl << d.probabilities()[1] << " diss 1 " << d(gen) << " " << d(gen) << std::endl;
    for (int i = 0; i < 100; ++i){
        std::cout << d(gen);
    }
    std::cout << std::endl;
    }
    */
    
    double long * xLocal = new double long [dim];
    for(int i = 0; i < dim; ++i) xLocal[i] = x0[i];
    double long * temp = new double long [dim];
    double long fTemp{};
    double long * xBest = new double long [dim];
    double long * xPrev = new double long [dim];
    for(int i = 0; i < dim; ++i) xBest[i] = x0[i];
    double long fBest = func -> eval(x0);
    //double long * grad = new double long [dim];
    //for(int i = 0; i < dim; ++i) grad[i] = func -> grad(x0, i);

    double long currentDelta = deltaInit;
    
    bool justImproved = 0;
    bool proceed = 1;
    
    rangeAroundEps(rangeLocal, xLocal, currentDelta, dim, area -> getRange());
    for (int i = 0; i < dim; ++i){
        uLocal[i] = new std::uniform_real_distribution<>{static_cast<double>(rangeLocal[2*i]), static_cast<double>(rangeLocal[2*i+1])} ;
    }
    
    
    for( ; proceed ; ++nIter){
        
        switch (d(gen)) {
            case 0: //LOCAL SEARCH
                for (int i = 0; i < dim; ++i) temp[i] = (*uLocal[i])(gen);
                fTemp = func -> eval(temp);
                //IF SEARCH IMPROVES APPROX, DECREASE DELTA FOR A MORE FOCUSED SEARCH.
                if (fTemp < fBest){
                    justImproved = 1;
                    currentDelta *= iterScale;
                }
                //IF SEARCH DOESN'T IMPROVE ANYTHING, NO CHANGE IS NEEDED
                break;
                
            case 1: //GLOBAL SEARCH
                for (int i = 0; i < dim; ++i) temp[i] = (*uGlobal[i])(gen);
                fTemp = func -> eval(temp);
                //IF SEARCH IMPROVES APPROX, DELTA IS BACK TO deltaInit AND LOCAL SEARCH STARTS FROM SCRATCH
                if (fTemp < fBest){
                    justImproved = 1;
                    currentDelta = deltaInit;
                }
                //IF SEARCH DOESN'T IMPROVE ANYTHING, NO CHANGE IS NEEDED
                break;
                
            default:
                std::cout << "Something is wrong";
                break;
        }
        
        if(justImproved){
        //made this to improve readability and not to repeat chunks of code
           //RECORD VALUES INTO BEST, DECREASE DELTA, & CREATE NEW DISTRIBUTION FOR THE NEW DELTA
           for (int i = 0; i < dim; ++i) xPrev[i] = xBest[i];
           for (int i = 0; i < dim; ++i) xBest[i] = temp[i];
           fBest = fTemp;
           for (int i = 0; i < dim; ++i) xLocal[i] = xBest[i];
           rangeAroundEps(rangeLocal, xLocal, currentDelta, dim, area -> getRange());
           //CHANGING LOCAL DISTRIBUTIONS
           for (int i = 0; i < dim;  ++i){
               delete uLocal[i];
           }
           for (int i = 0; i < dim; ++i){
               uLocal[i] = new std::uniform_real_distribution<>{static_cast<double>(rangeLocal[2*i]), static_cast<double>(rangeLocal[2*i+1])} ;
           }
            itersAfterLastSuccess = 0;
        }
        
        ++itersAfterLastSuccess;
        justImproved = 0;

        //STOP CRITERION
        if(stopCrit -> GetStopChoice() == 'i'){
            if (!stopCrit -> stop(nIter, itersAfterLastSuccess)) proceed = 0;
        }
        if (stopCrit -> GetStopChoice() == 'l'){
            if (!stopCrit -> stop(xBest, xPrev, /*doesn't matter what*/ xLocal /*is here*/, nIter)) proceed = 0;
        }
        
    }
    
    for (int i = 0; i < dim; ++i) xFin[i] = xBest[i];
    //cout << endl << "Num of iterations: " << nIter << endl;
    
    for (int i = 0; i < dim;  ++i){
        delete uGlobal[i];
    }
    delete [] uGlobal;
    
    for (int i = 0; i < dim;  ++i){
        delete uLocal[i];
    }
    delete [] uLocal;
    
    delete [] xLocal;
    delete [] temp;
    delete [] xBest;
    //delete [] grad;

    return fBest;
    
    
};

