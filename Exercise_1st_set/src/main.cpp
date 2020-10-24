#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <exercise_header.h>



int main(){

    // Initialize random seed
    std::srand(time(0));
    std::rand();

    std::cout << "==================EXERCISE 1=====================\n";
    // Take random number between 1 and 20
    unsigned long x = std::rand() % 20 + 1;

    // Call function
    std::cout << "Number of ones in binary form of number: " << x << " is : " << counter_ones(x) << " \n";
    std::cout << "\n";
    

    std::cout << "==================EXERCISE 2=====================\n";

    // Take random number between one and eight thousand 
    
    unsigned long y = std::rand() % 8000 + 1;

    // Call function
    std::cout << "Checksum of number: " << y << " is : " << checksum(y) << " \n";

    std::cout << "\n";

    return 0;
}
