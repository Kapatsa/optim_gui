//
//  opt_tools.cpp
//  optimization_console
//
//  Created by David Kapatsa on 13.11.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#include "opt_tools.hpp"

void eq(double long * x, double long * y, int dim){
    for (int i = 0; i < dim; ++i){
        x[i] = y[i];
    }
}

double long norm(double long *vector, int dim){
    double long dist = 0;
    for (int i = 0; i < dim; ++i){
        dist += vector[i]*vector[i];
    }
    return sqrt(dist);
};

double long terOpt(Function *f, double long *left, double long *right, double long eps){
    int dim = f -> dim;
    double long *lCur = new double long [dim];
    double long *rCur = new double long [dim];
    double long *lCand = new double long [dim];
    double long *rCand = new double long [dim];
    double long *diff = new double long [dim];
    
    for(int i = 0; i < dim; ++i){
        lCur[i] = left[i];
        rCur[i] = right[i];
        diff[i] = rCur[i] - lCur[i];
    }
    
    while ( norm(diff, dim) > eps) {
        
        //the interval is cut into three parts
        for(int i = 0; i < dim; ++i){
            lCand[i] = (2*lCur[i] + rCur[i])/3;
            rCand[i] = (lCur[i] + 2*rCur[i])/3;
        }
        
        /*
        cout << "intervals:" << endl;
        print(lCur, dim);
        print(lCand, dim);
        print(rCand, dim);
        print(rCur, dim);
        cout << endl;
        */
        
        //compare f values at new nodes, assign new nodes
        if( f->eval(lCand) < f->eval(rCand) ){
            //rCur = rCand, lCur stays the same
            for(int i = 0; i < dim; ++i){
                rCur[i] = rCand[i];
            }
        }
        else {
            //lCur = lCand, rCur stays the same
            for(int i = 0; i < dim; ++i){
                lCur[i] = lCand[i];
            }
        }
        
        //recalculate the difference for the current interval
        for(int i = 0; i < dim; ++i){
            diff[i] = rCur[i] - lCur[i];
        }
        
    }
    //out of the cycle, make some assignments
    //xCur is our new optimal point
    for (int i = 0; i < dim; ++i){
        left[i] = (lCur[i] + rCur[i])/2;
    }
    
    //cout << endl << "Candidate:";
    //print(left, dim);
    //cout << endl;
    
    delete [] lCur;
    delete [] rCur;
    delete [] lCand;
    delete [] rCand;
    delete [] diff; 
    return f -> eval(left);
};

double long lambdaMax(Area * rect, double long *xCur, double long *grad){
    int dim = rect -> dim;
    
    double long alphaCur{};
    double long alphaCand{};
    
    for (int i = 0; i < dim; ++i) {
        if (grad[i] > 0){
            alphaCand = ((rect->getRange()[2*i+1]) - xCur[i])/grad[i];
        }
        else if (grad[i] < 0) {
            alphaCand = ((rect->getRange()[2*i]) - xCur[i])/grad[i];
            //std::cout << " (" << (rect->getRange()[2*i]) << " - " << xCur[i] << ")/(" << grad[i] << ")" << endl;
            //std::cout << "Alpha now:" << alphaCand << endl;
        }
        
        if (i == 0) alphaCur = alphaCand;
        else if ( alphaCand < alphaCur ) alphaCur = alphaCand;
    }
    return alphaCur;
}

void print(double long *x, int dim){
    std::cout << " (";
    for (int i = 0; i < dim; ++i){
        std::cout << x[i];
        if (i != dim-1) std::cout << ", ";
    };
    std::cout << "), ";
}

/**
* rangeAroundEps Function
 * This function creates an array of ranges for the epsilon neighborhood (in infinity metric) of a specified point. It takes into account the global bounds if they are specified. It can be used to create areas.
 * @param epsRange is the array, which will store range values
 * @param point is the point
 * @param eps is the epsilon neighborhood of the
 * @param dim is the dimension
 * @param globalBounds is the global
*/
double long * rangeAroundEps(double long * epsRange, double long * point, double long eps, int dim, double long * globalBounds){
    for(int i = 0; i < dim; ++i){
        epsRange[2*i] = max(globalBounds[2*i], point[i] - eps);
        epsRange[2*i+1] = min(globalBounds[2*i+1], point[i] + eps);
    }
    return epsRange;
}





