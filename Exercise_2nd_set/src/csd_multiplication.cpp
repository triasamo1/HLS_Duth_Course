#include <exercise2_header.h>
#include <iostream>

ac_int<Wout,true> csd_mult (ac_int<W,true> &in, const CSD<W> &constant_csd){
    // in is the input value (non constant)
    // constant_csd is the CSD representation of a constant
    ac_int<Wout,true> result;
    CSD<W> in_csd = {
            0,  //x_p
            0,  //x_m
    };
    // create the CSD representation of the input number
    csd_encode(in, in_csd);

    //===========MULTIPLICATION============
    int sum_in = 0;
    int sum_cons = 0;

    //initialisation based on 2^0
    if (in_csd.x_p[0]){
        sum_in += 1;
    }else if (in_csd.x_m[0]){
        sum_in -= 1;
    }
    if (constant_csd.x_p[0]){
        sum_cons += 1;
    }else if (constant_csd.x_m[0]){
        sum_cons -= 1;
    }

    for (int i=1;i<W;i++){
        //calculate the sum of powers-of-2 of INPUT NUMBER
        if (in_csd.x_p[i]){
            sum_in += (2<<(i-1));
        }else if (in_csd.x_m[i]){
            sum_in -= (2<<(i-1));
        }
        //calculate the sum of powers-of-2 of CONST NUMBER
        if (constant_csd.x_p[i]){
            sum_cons += (2<<(i-1));
        }else if (constant_csd.x_m[i]){
            sum_cons -= (2<<(i-1));
        }
    }
    result = sum_in * sum_cons;

    return result;
}
