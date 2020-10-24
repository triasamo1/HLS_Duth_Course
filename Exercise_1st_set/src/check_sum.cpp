#include <exercise_header.h>
#include <iostream>

unsigned short int checksum(unsigned long &x ){
    
    bool flag = false;
    unsigned short int sum = 0;
    signed int pointer = 10;

    while( x != 0 ){       

        if (flag){  // x2 scenario

            if ((x % 10)*2 > 9 ){ //add the digits of the doubled number
                sum += (( ((x % 10)*2) / 10) + ( ((x % 10)*2) % 10));
            }else{
                sum += ((x % 10)*2);
            }
	    x = x / 10;
            flag = !flag; //change flag

        }else{  // just-add scenario

            sum += (x % 10);
	    x = x / 10;
	    flag = !flag;

        }
         
    }
    return sum;
}
