/// exercise3_header.h
#include "ac_int.h"
#include "ac_channel.h"
#include <iostream>

typedef ac_int<4,false> dtype;
typedef ac_int<4,false> Card;


// declare all classes 
class RunLengthEncoder {
private:
    // internal state
    dtype counter;  //counter for the consecutive same numbers
    int i=0;  //iterator
    dtype value_new, value_old;  //2 buffers for holding up past and present value
public:
    // constructor - init internal state
    RunLengthEncoder();
    void run (ac_channel<dtype> &in, ac_channel<dtype> &out);

};

//

class BlackJack {
private:
    // internal state
    int sum;
    int count_cards;
    Card card_drawn;
    bool first_ace;
    bool second_ace;
public:
    // constructor - init internal state
    BlackJack();
    void run (ac_channel<Card> &in_card, bool &end_round, bool &win);
    void fresh_start (bool &end_round, bool &win);
};
