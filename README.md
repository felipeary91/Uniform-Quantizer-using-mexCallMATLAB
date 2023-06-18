# Uniform Quantizer using mexCallMATLAB

Quantization is a discretization process in which the continuous range of all possible values of a signal are replaced by a discrete range of values. In other words, a quantizer function $Q:R→Γ$, assigns a value $Q(a)∈Γ$ to each signal value. A formal definition of a quantizer is :

```math
Q(n) = sign(a) * \Delta * \lfloor \frac{|a|}{\Delta} + \frac{1}{2} \rfloor
```

From the quantizer equation it can be inferred that most of the times quantization simply means to round off or truncate an analog value. This implementation corresponds to a uniform quantizer, which has a quantization step size $(Δ)$ that spaces the quantization levels equally.

In this implementation mexCallMATLAB is used, a sine signal is simulated by calling the MATLAB command $sin()$, and then quantized using the equation above. The quantization error, difference between $m(t) - m_q(t)$, is computed as well.  Finally, the results are plotted using the MATLAB command $plot()$.

A MEX function can be created by using the command: <br />
`mex -R2018a Quantizer_using_mexCallMATLAB.c`

This function needs no output and takes only one argument, which is the number of bits used by the quantizer: <br />
`Quantizer_using_mexCallMATLAB(3)`
