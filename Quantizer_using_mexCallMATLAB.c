/*
The implementation will change dramatically when using mexCallMATLAB
instead of Dislin. Start by declaring the arrays to be used for plotting
and use the "hold on" command.
*/

#include "Quantizer_using_mexCallMATLAB_header.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


//Prototype of uniform_quantization function
void uniform_quantization(double* input, double* error, double signal_max, double signal_min, double quantizer_length, double step_size);

//Prototype of function to fill the data vector for the sine
void fill(double* pr_input, double delta);

void MATLAB_main(double num_bits) {

    //Variables
    double signal_max = 1;
    double signal_min = -1;
    double dx = 2 * acos(-1) / 500;
    double quantizer_len = pow(2, num_bits);
    double step_size = fabs(signal_max - signal_min) / (quantizer_len - 1);
    mxArray* input_to_sine[1];
    mxArray* quantization_error[2];
    mxArray* result_sine[2];
    mxArray* hold[1];


    //Generating a sine wave
    input_to_sine[0] = mxCreateDoubleMatrix(500, 1, mxREAL);
    result_sine[0] = mxCreateDoubleMatrix(500, 1, mxREAL);
    quantization_error[0] = mxCreateDoubleMatrix(500, 1, mxREAL);
    fill(mxGetPr(input_to_sine[0]), dx);
    mexCallMATLAB(1, result_sine, 1, input_to_sine, "sin");

    //Plotting the sine wave in blue
    result_sine[1] = mxCreateString("blue");
    mexCallMATLAB(0, NULL, 2, result_sine, "plot");
    hold[0] = mxCreateString("on");
    mexCallMATLAB(0, NULL, 1, hold, "hold");

    //Quantizing the input
    uniform_quantization(mxGetPr(result_sine[0]), mxGetPr(quantization_error[0]), signal_max, signal_min, quantizer_len, step_size);

    //Plotting quantized signal in red
    result_sine[1] = mxCreateString("red");
    mexCallMATLAB(0, NULL, 2, result_sine, "plot");

    //Plotting quantization error in green
    quantization_error[1] = mxCreateString("green");
    mexCallMATLAB(0, NULL, 2, quantization_error, "plot");

    //Freeing memory
    mxDestroyArray(input_to_sine[0]);
    mxDestroyArray(quantization_error[0]);
    mxDestroyArray(quantization_error[1]);
    mxDestroyArray(result_sine[0]);
    mxDestroyArray(result_sine[1]);
    mxDestroyArray(hold[0]);
}


//Implementation of uniform_quantization function
void uniform_quantization(double* input, double* error, double signal_max, double signal_min, double quantizer_length, double step_size) {

    for (int i = 0; i < 500; i++) {
        double quantized_input = 0;
        double signum = (input[i] > 0) - (input[i] < 0);  //Signum function

        //Calculating the quantized input
        quantized_input = signum * step_size * floor((fabs(input[i]) / step_size) + 0.5);

        if (signum == 1 && quantized_input > signal_max) {
            quantized_input = 1 - step_size / 2;
        }
        else if (signum == -1 && quantized_input < signal_min) {
            quantized_input = -1 + step_size / 2;
        }
        error[i] = input[i] - quantized_input;
        input[i] = quantized_input;
    }
}

//Implementation of function to fill the data vector for the sine
void fill(double* pr_input, double delta) {
    for (int i = 0; i < 500; i++) {
        pr_input[i] = delta * i;
    }
}