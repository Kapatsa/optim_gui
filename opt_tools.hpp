//
//  opt_tools.hpp
//  optimization_console
//
//  Created by David Kapatsa on 13.11.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef opt_tools_hpp
#define opt_tools_hpp

#include <stdio.h>
#include <cmath>
#include <random>
#include "Function.hpp"
#include "Area.hpp"
#include "RectArea.hpp"

double long norm(double long *vector, int dim);
double long terOpt(Function *f, double long *left, double long *right, double long eps);
double long lambdaMax(Area * rect, double long *xCur, double long *grad);
void print(double long *x, int dim);
void eq(double long * x, double long * y, int dim);
double long * rangeAroundEps(double long * epsRange, double long * point, double long eps, int dim, double long * globalBounds = 0);

#endif /* opt_tools_hpp */
