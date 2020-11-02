#include <exercise3_header.h>

typedef ac_int<4,false> dtype;
typedef ac_int<4,false> Card;

int main() {

    std::cout << "\n==================EXERCISE 1=====================\n";
    // initialize ac_channels
    ac_channel<dtype > in;
    ac_channel<dtype > out;

    //call the constructor for example a and b
    RunLengthEncoder my_enc_a;

    // initialize two arrays of 10 ac_int elements each
    dtype input_stream_1[10] = {3,2,2,2,2,2,1,1,1,4};
    dtype input_stream_2[10] = {5,8,13,13,11,12,9,4,4,4};

    std::cout << "Trying first input stream: {3,2,2,2,2,2,1,1,1,4} \n";
    std::cout << "Should be: {3,1,2,5,1,3,4,1} \n";
    for (int i=0;i<10;i++){
        in.write(input_stream_1[i]);
    }

    while(in.available(1)) {
        my_enc_a.run(in, out);
    }
    std::cout << "Waiting for data from the output channel..\n";

    //int encoded_data[14]; //bigger to avoid overflow
    //int iter; // iterator to write down the encoded data
    //iter = 0;
    while(out.available(1)) {
        //encoded_data[iter] = out.read();
        std::cout << out.read() << " ";
        //iter += 1;
    }
    std::cout << "\nSuccessfully received the data.\n";

    std::cout << "-----------------------------\n";

    std::cout << "Trying second input stream: {5,8,13,13,11,12,9,4,4,4} \n";
    std::cout << "Should be: {5,1,8,1,13,2,11,1,12,1,9,1,4,3} \n";
    for (int i=0;i<10;i++){
        in.write(input_stream_2[i]);
    }
    while(in.available(1)) {
        my_enc_a.run(in, out);
    }
    std::cout << "Waiting for data from the output channel..\n";

    //iter = 0;
    while(out.available(1)) {
        //encoded_data[iter] = out.read();
        std::cout << out.read() << " ";
        //iter += 1;
    }
    std::cout << "\nSuccessfully received the data.\n";

    std::cout << "\n==================EXERCISE 2=====================\n";

    // initialize ac_channel
    ac_channel<Card > in_card;

    bool win = false;
    bool end_round = false;

    //Construct game
    BlackJack game;

    //Scenarios - Testbench
    Card two_aces[2] = {1,1};
    Card over_21[4] = {7,9,3,5};
    Card five_cards[5] = {3,4,2,3,5};
    Card exactly_21[4] = {4,7,8,2};

    //Apply scenarios to the game
    std::cout << "\nTwo Aces Scenario\n";
    for (int i=0;i<2;i++){
        in_card.write(two_aces[i]);
    }
    while(in_card.available(1)) {
        game.run(in_card,end_round, win);
    }
    game.fresh_start(end_round, win);

    std::cout << "\nOver 21 Scenario\n";
    for (int i=0;i<4;i++){
        in_card.write(over_21[i]);
    }
    while(in_card.available(1)) {
        game.run(in_card,end_round, win);
    }
    game.fresh_start(end_round, win);

    std::cout << "\nFive Cards Scenario\n";
    for (int i=0;i<5;i++){
        in_card.write(five_cards[i]);
    }
    while(in_card.available(1)) {
        game.run(in_card,end_round, win);
    }
    game.fresh_start(end_round, win);

    std::cout << "\nExactly 21 Scenario\n";
    for (int i=0;i<4;i++){
        in_card.write(exactly_21[i]);
    }
    while(in_card.available(1)) {
        game.run(in_card,end_round, win);
    }
    game.fresh_start(end_round, win);
    
    std::cout << "\nEnd of Game\n";

    return 0;
}
