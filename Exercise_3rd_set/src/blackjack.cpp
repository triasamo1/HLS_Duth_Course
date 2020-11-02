#include <exercise3_header.h>

typedef ac_int<4,false> Card;


// constructor - init internal state
BlackJack::BlackJack() {
    sum = 0;
    first_ace = false;
    second_ace = false;
    count_cards = 0;
}
// top-level interface
void BlackJack::run (ac_channel<Card> &in_card, bool &end_round, bool &win) {
    while (in_card.available(1)) {
        //Draw Card
        card_drawn = in_card.read();
        count_cards += 1;

        //check if it's an Ace
        if ( card_drawn == 1 ){
            if (first_ace){
                //check if it was 2nd Ace in a row
                second_ace = true;
            }
            sum += 11;
            first_ace = true;
        }else{
            sum += card_drawn;
            first_ace = false;
            second_ace = false;
        }
        //round briefing
        std::cout << "Card drawn: " << card_drawn << std::endl;
        std::cout << "Current Sum: " << sum << std::endl;
    }
    //Win-Round Check
    if( sum > 21 ){
        if (second_ace) {
            win = true;
            std::cout << "WIN! (2 Aces)" << std::endl;
        }else{
            win = false;
            std::cout << "Busted! (>21)" << std::endl;
        }
        end_round = true;
    }else if( sum == 21){
        win = true;
        end_round = true;
        std::cout << "WIN! (exactly 21)" << std::endl;
    }else if (count_cards==5){
        win = true;
        end_round = true;
        std::cout << "WIN! (5 cards drawn)" << std::endl;
    }else{
        win = false;
        end_round = false;
    }
}

void BlackJack::fresh_start (bool &end_round, bool &win){
    sum = 0;
    first_ace = false;
    second_ace = false;
    count_cards = 0;
    end_round = false;
    win = false;
    std::cout << "Fresh Start... OK! \n";
}
