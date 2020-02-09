//
//  RectArea.hpp
//  optimization_console
//
//  Created by David Kapatsa on 06.10.2019.
//  Copyright © 2019 David Kapatsa. All rights reserved.
//

#ifndef RectArea_hpp
#define RectArea_hpp

#include <stdio.h>
#include <iostream>
#include "Area.hpp"
/**
 * Rectangle Area Class
 *
 * This class is an instance of Area class. It allows to declare rectangular areas in an n-dimensional space.
 *
 **/
class RectArea : public Area {
protected:
    double long tolIn = 1e-10;
    double long *range; // [( , );( , );( , )]  // 4 when dim = 2, 6 when dim = 3
public:
    //int dim;
    RectArea(){};
    ~RectArea(){ delete [] range; };
    RectArea(double long *x, int dimen);
    /**
     * Is in function
     *
     * This function tells if a given point @param point lies inside the rectanlular area, defined bu the class
     * @return 0 if outside, 1 if inside
     **/
    bool isIn(double long *point) override;
    double long * getRange() override { return range; };
    void setRange(double long *x) override;
    void setDim(int dimen) override;
    void printExpr() override;
    
};

#endif /* RectArea_hpp */
