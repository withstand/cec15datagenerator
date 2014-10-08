/*==========================================================
 * jkiss.c - rand number generator JKISS
 *
 * ref: http://www0.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf
 *========================================================*/
/* $Revision: 1.1.10.2 $ */
#include "matrix.h"
#include "mex.h"

/* Public domain code for JKISS RNG */
static unsigned int x = 123456789,y = 987654321,z = 43219876,c = 6543217; /* Seed variables */
unsigned int JKISS()
{
    unsigned long long t;
    x = 314527869 * x + 1234567;
    y ^= y << 5; y ^= y >> 7; y ^= y << 22;
    t = 4294584393ULL * z + c; c = t >> 32; z = t;
    return x + y + z;
}




/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{
    double multiplier;              /* input scalar */
    double *inMatrix;               /* 1xN input matrix */
    mwSize ncols;                   /* size of matrix */
    double *outMatrix;              /* output matrix */
    
    /* check for proper number of arguments */
    if((nrhs!=0) && (nrhs!=4)) {
        mexErrMsgIdAndTxt("MyRandon:KISS:nrhs","ReSeed require 4 integer inputs.");
    }
    
    if (nrhs==4)
    {
        x = (unsigned int)mxGetScalar(prhs[0]);
        y = (unsigned int)mxGetScalar(prhs[1]);
        z = (unsigned int)mxGetScalar(prhs[2]);
        c = (unsigned int)mxGetScalar(prhs[3]);
        return;
    }
    
    /* create the output matrix */
    plhs[0] = mxCreateDoubleScalar(JKISS()/ 4294967296.0);
    
}







