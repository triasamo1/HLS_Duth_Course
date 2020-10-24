#include <exercise_header.h>

unsigned short int counter_ones(unsigned long &x){

    unsigned int result = 0; 
    while (x) { 
        result += (x & 1); //check the least significant bit if it's a one
        x >>= 1; //right shift (get rid of the last bit)
    }

    return result;
}
