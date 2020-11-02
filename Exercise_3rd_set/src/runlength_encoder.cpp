#include <exercise3_header.h>

typedef ac_int<4,false> dtype;

// constructor - init internal state
RunLengthEncoder::RunLengthEncoder() {
     counter=1;
     i=0;
}

// top-level interface
void RunLengthEncoder::run (ac_channel<dtype> &in, ac_channel<dtype> &out) {
    i=0;
    while (in.available(1)) {
        //fill the raw_data array from the input stream
        value_new = in.read();
        //=========ENCODER========
        if (i - 1 < 0) {
            // for first element only
            out.write(value_new);
        } else {
            if (value_new == value_old) {
                // if same as the previous one
                counter += 1;
            } else {
                // not the same scenario..
                // write down the current counter value
                out.write(counter);
                counter = 1;
                // add the new element to the output stream
                out.write(value_new);
            }
            if (i == 9) { //write down the counter of the last element seen
                out.write(counter);
            }
        }
        value_old = value_new;
        i += 1;
        //=======================
    }
}


