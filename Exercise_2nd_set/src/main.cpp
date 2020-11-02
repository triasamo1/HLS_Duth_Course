#include <iostream>
#include "ac_channel.h"
#include "ac_int.h"
#include "ac_fixed.h"
#include <exercise2_header.h>



int main(){

    std::cout << "\n==================EXERCISE 1=====================\n";
    ac_int<8,false> a, b; // 8−bit unsigned integer
    ac_int<9,true> c, d; // 9−bit signed integer
    ac_int<17,true> e; // How many bits?!
    ac_int<18,true> e1;
    ac_int<19,true> e2;

    a = 255; //highest 8-bit unsigned int
    b = 255;
    c = 255; //highest 9-bit signed int
    d = 255;
    e = a*b + c*d;
    e1 = a*b + c*d;
    e2 = a*b + c*d;

    std::cout << "Expected result: 130050" << std::endl;
    std::cout << "17-bit e= " << e << "  " << e.to_string(AC_BIN, true) << std::endl;
    std::cout << "18-bit e= " << e1 << "  " << e1.to_string(AC_BIN, true) << std::endl;
    std::cout << "19-bit e= " << e2 << "  " << e2.to_string(AC_BIN, true) << std::endl;
    std::cout << "So.. 18-bit is the minimum number of bits required to display the full result" << std::endl;

    std::cout << "-------------------------" << std::endl;
    ac_fixed<5,2,false> f; //5−bit unsigned fixed−point type with 2 integer bits
    ac_fixed<5,4,true> g; // 5−bit signed fixed−point type with 4 integer bits
    ac_fixed<10,5,true> h; // How many bits
    ac_fixed<10,6,true> h1; // How many bits
    ac_fixed<9,6,true> h2; // How many bits
    ac_fixed<11,6,true> h3; // How many bits

    f = 3.875; //highest 5-bit unsigned 11.111
    g = 7.5;   //highest 5-bit signed 0111.1
    h = f*g;  //29.0625
    h1 = f*g;
    h2 = f*g;
    h3 = f*g;

    std::cout << "Expected result: 29.0625" << std::endl;
    std::cout << "ac_fixed<10,5,true> h= " << h << "  " << h.to_string(AC_BIN, true) << std::endl;
    std::cout << "ac_fixed<10,6,true> h= " << h1 << "  " << h1.to_string(AC_BIN, true) << std::endl;
    std::cout << "ac_fixed<9,6,true> h= " << h2 << "  " << h2.to_string(AC_BIN, true) << std::endl;
    std::cout << "ac_fixed<11,6,true> h= " << h3 << "  " << h3.to_string(AC_BIN, true) << std::endl;
    std::cout << "So.. we need 10-bit length with 6-bits for integer part" << std::endl;


    std::cout << "\n==================EXERCISE 2=====================\n";
    ac_int<W,true> num = 29;
    CSD<W> num_csd = {
            0,  //x_p
            0,  //x_m
    };
    csd_encode(num, num_csd);

    std::cout << "---------------- \n" ;
    ac_int<W,true> num2 = 23;
    CSD<W> num_csd2 = {
            0,  //x_p
            0,  //x_m
    };
    csd_encode(num2, num_csd2);
    std::cout << "---------------- \n" ;
    std::cout << "=====MULTIPLICATION======\n" ;
    ac_int<W,true> N_cons = 12;
    CSD<W> N_cons_csd = {
            0,  //x_p
            0,  //x_m
    };

    //compute the csd of constant value
    csd_encode(N_cons, N_cons_csd);
    std::cout << "---------------- \n" ;
    ac_int<Wout,true> mult;
    mult = csd_mult(num2 ,N_cons_csd);
    std::cout << "Result:  \n" ;
    std::cout << num2 << " * " << N_cons <<" = " << mult<< std::endl;

    std::cout << "---------------- \n" ;
    // 2nd example
    ac_int<W,true> N_cons2 = 27;
    CSD<W> N_cons_csd2 = {
            0,  //x_p
            0,  //x_m
    };
    ac_int<W,true> num3 = 11;
    CSD<W> num_csd3 = {
            0,  //x_p
            0,  //x_m
    };
    //compute the csd of constant value
    csd_encode(N_cons2, N_cons_csd2);
    std::cout << "---------------- \n" ;
    ac_int<Wout,true> mult2;
    mult2 = csd_mult(num3 ,N_cons_csd2);
    std::cout << "Result:  \n" ;
    std::cout << num3 << " * " << N_cons2 <<" = " << mult2 << std::endl;

    std::cout << "\n==================EXERCISE 3=====================\n";
    // initialize ac_channels
    ac_channel<ac_int<4,false> > in;
    ac_channel<ac_int<4,false> > out;

    // initialize two arrays of 10 ac_int elements each
    ac_int<4,false> input_stream_1[10] = {3,2,2,2,2,2,1,1,1,4};
    ac_int<4,false> input_stream_2[10] = {5,8,13,13,11,12,9,4,4,4};

    std::cout << "Trying first input stream: {3,2,2,2,2,2,1,1,1,4} \n";
    std::cout << "Should be: {3,1,2,5,1,3,4,1} \n";
    for (int i=0;i<10;i++){
        in.write(input_stream_1[i]);
    }

    if(in.available(10)) {
        runlength_encode(in, out);
    }

    std::cout << "Waiting for data from the output channel..\n";

    int encoded_data[15];
    int iter; // iterator to write down the encoded data
    iter = 0;
    while(out.available(1)) {
        encoded_data[iter] = out.read();
        std::cout << encoded_data[iter] << " ";
        iter += 1;
    }
    std::cout << "\nSuccessfully received the data.\n";

    std::cout << "-----------------------------\n";

    std::cout << "Trying second input stream: {5,8,13,13,11,12,9,4,4,4} \n";
    std::cout << "Should be: {5,1,8,1,13,2,11,1,12,1,9,1,4,3} \n";
    for (int i=0;i<10;i++){
        in.write(input_stream_2[i]);
    }
    if(in.available(10)) {
        runlength_encode(in, out);
    }
    std::cout << "Waiting for data from the output channel..\n";

    iter = 0;
    while(out.available(1)) {
        encoded_data[iter] = out.read();
        std::cout << encoded_data[iter] << " ";
        iter += 1;
    }
    std::cout << "\nSuccessfully received the data.\n";

    return 0;

}

