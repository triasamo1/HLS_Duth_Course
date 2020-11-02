#include <exercise2_header.h>
#include <iostream>


void runlength_encode(ac_channel<ac_int<4,false> > &in, ac_channel<ac_int<4,false> > &out){

    ac_int<4,false> raw_data[10];
    ac_int<4,false> counter = 1; //counter for the consecutive same numbers

    if (in.available(10)){
        for(int i=0;i<10;i++) {
            //fill the raw_data array from the input stream
            raw_data[i] = in.read();
            //=========ENCODER========
            if (i - 1 < 0) {
                // for first element only
                out.write(raw_data[i]);
            } else {
                if (raw_data[i] == raw_data[i - 1]) {
                    // if same as the previous one
                    counter += 1;
                } else {
                    // not the same scenario..
                    // write down the current counter value
                    out.write(counter);
                    counter = 1;
                    // add the new element to the output stream
                    out.write(raw_data[i]);
                }
                if (i == 9) { //write down the counter of the last element seen
                    out.write(counter);
                }
            }
            //=======================
        }
    }
}

