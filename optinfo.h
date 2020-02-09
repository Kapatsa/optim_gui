#ifndef OPTINFO_H
#define OPTINFO_H


class OptInfo
{
//TODO:: Make private and make setters/getters
public:
    double rangeX1 = 0, rangeX2 = 1, rangeY1 = 0, rangeY2 = 1;
    int dim = 2;
    int functionnumber = 0;
    int method = 0;
    int stop_grad_method = 0;
    int stop_stoc_method = 0;
    long double eps_grad = 0.0001;
    long double eps_diff = 0.0001;
    long double local_prob = 0.3;
    int maxIter = 4000;
    int maxIterAfterLastSuccess = 400;
    long double min;
    long double * argmin;
    int noOfIterations;
    long double * x_0;
    OptInfo(){
        x_0 = new long double[dim];
        argmin = new long double[dim];
    };
    ~OptInfo(){
        delete [] argmin;
        delete [] x_0;
    }
};

#endif // OPTINFO_H
