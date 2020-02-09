//
//  Stochastic.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Stochastic_hpp
#define Stochastic_hpp

#include <stdio.h>
#include <fstream>
#include <random>
#include <ctime>
// ----------------
#include "OptMethod.hpp"
// ----------------
/**
* \class Stochastic Class
* Instance of OptMethod class, with a virtual function optimize()
 * @name localProbability defines a discrete distribution, which directs algorithm to switch between global and local search with the specified probability
 * @name deltaInit is initial ball size for local search ,
 * @name iterScale is a scaling parameter for the local ball (0<iterScale<=1), which is used each time the local ball search gives a new better approximation
**/
class Stochastic : public OptMethod{
public:
    long double localProbability = 0.5;
    long double deltaInit = 0.1;
    long double iterScale = 0.9;
    Stochastic(){};
    Stochastic(double long * xstart, int dimen, long double localProb = 0.5, long double deltaIn = 0.1, long double iterSc = 0.9);
    ~Stochastic(){delete [] x0; delete [] xFin;};
    long double optimize(Area * area, Function * func, StopCriterion * stopCrit) override;
    long double * getXFin() override { return xFin;};
    void SetLocalProb(double long num) override {localProbability = num;}
};


#endif /* Stochastic_hpp */
