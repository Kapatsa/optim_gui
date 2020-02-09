//
//  Abs.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef Abs_hpp
#define Abs_hpp

#include <stdio.h>
#include <cmath>

//-------------
//#include "stuff.hpp"
#include "StopCriterion.hpp"
//-------------


/**
 * Abs Class
 *
 * Instance of StopCriterion, which overrides virtual functions stop()
 **/
class Abs : public StopCriterion {
public:
    Abs(){};
    Abs(int dimen){
        dim = dimen;
    };
    Abs(int dimen, double epsilon, int iterations);
    ~Abs(){};
    bool stop(int numOfIter, double long *grad) override;
    bool stop(double long * xCurrent, double long * xPrev,/*, double long *fCurr, double long *fPrev,*/ double long *grad ,int numOfIter) override;
    bool stop(int numOfIter, int itersAfterLastSuccess) override;
    bool checkGrad(double long *grad) override;
};

#endif /* Abs_hpp */
