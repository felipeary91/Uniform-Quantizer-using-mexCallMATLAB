#include "mex.h"
#include <stdio.h>
#include <tgmath.h>
#include <omp.h>


void MATLAB_main(double);

#include "mex.h"

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray *prhs[]) {
	
	double multiplier[1];	//multiplier is the array of scalar inputs

	//Verifying that we have one input and no outputs
	if (nrhs != 1) {
		mexErrMsgIdAndTxt("MATLAB:xtimesy:invalidNumInputs", "Invalid number of inputs.");
	}
	if (nlhs != 0) {
		mexErrMsgIdAndTxt("MATLAB:xtimesy:invalidNumOutputs", "Invalid number of outputs. Two are required.");
	}

	//Getting the number of bits
	multiplier[0] = mxGetScalar(prhs[0]);

	MATLAB_main(multiplier[0]);
}