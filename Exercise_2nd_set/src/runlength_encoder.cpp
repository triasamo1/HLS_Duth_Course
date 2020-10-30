#include <exercise2_header.h>
#include <iostream>


void runlength_encode(ac_channel<ac_int<4,false> > &in, ac_channel<ac_int<4,false> > &out){

    int raw_data[10];
    int counter = 1; //counter for the consecutive same numbers

    int i=0;
    while (in.available(1)){
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
            if (i==9){ //write down the counter of the last element seen
                out.write(counter);
            }
        }
        i += 1;
        //=======================
    }
}
