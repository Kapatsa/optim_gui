//
//  GradDesc.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef GradDesc_hpp
#define GradDesc_hpp

#include <stdio.h>
// ----------------
#include "Area.hpp"
#include "RectArea.hpp"
#include "Function.hpp"
#include "OptMethod.hpp"
#include "StopCriterion.hpp"
#include "opt_tools.hpp"
// ----------------

/**
 * Gradient Descent Class
 *
 * Instance of OptMethod class, with a virtual function optimize()
 **/
class GradDesc : public OptMethod {
public:
    GradDesc(){};
    /**
     * Constructor that sets the starting point and the dimension of method
    **/
    GradDesc(double long * xstart, int dimen);
    ~GradDesc(){delete [] x0; delete [] xFin;};
    long double optimize(Area * area, Function * function, StopCriterion * stopCrit) override;
    long double * getXFin() override { return xFin; };
    void SetLocalProb(double long num) override {;};
    
};


#endif /* GradDesc_hpp */
