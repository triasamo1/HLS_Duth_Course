#include <exercise2_header.h>
#include <iostream>


void csd_encode(ac_int<W,true> &num, CSD<W> &num_csd){
    // num is the input number to be encoded in CSD
    // x_p and x_m are the two bit vectors that represent the CSD number

    std::cout << "Number: " << num << std::endl;
    //binary representation
    std::cout << "Original binary form: " << num.to_string(AC_BIN, true) << std::endl;

    //======ENCODER======
    int carry = 0;
    ac_int<2,false> slice;
    for(int i=0;i<W;i++){
        slice = num.slc<2>(i);
        //std::cout << "slice is " << slice.to_string(AC_BIN, false) << std::endl;
        if (carry == 0){
            if( (slice == 0) || (slice == 2) ){
                num_csd.x_p[i] = 0;
                carry = 0;
            }else if( slice == 1){
                num_csd.x_p[i] = 1;
                carry = 0;
            }else{
                carry = 1;
                num_csd.x_m[i] = 1;  //negative one
            }
        }else{
            if( (slice == 1) || (slice == 3) ){
                num_csd.x_p[i] = 0;
                carry = 1;
            }else if( slice == 0){
                num_csd.x_p[i] = 1;
                carry = 0;
            }else{
                carry = 1;
                num_csd.x_m[i] = 1;  //negative one
            }
        }

    }
    std::cout << "x_p = " << num_csd.x_p.to_string(AC_BIN, false) << std::endl;
    std::cout << "x_m = " << num_csd.x_m.to_string(AC_BIN, false) << std::endl;
    std::cout <<  num_csd.x_p << " - " << num_csd.x_m << std::endl;
}
