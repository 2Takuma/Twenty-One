/*
    File: TwentyOne.cpp
    Author: Keanu Arao
    Created: ET November 14 2025
    Purpose: Simulate Black Jack where it tells user their probability of "winning"

*/


#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

// Header Files
#include "Card.h"
#include "Player.h"

// input to stand/hit/split
// Calculator

// Pre-Game Functions
void fRead(std::string, Card*,  int);
void crtDeck(Card*);

// Menu Functions
void menu();
void rules();

// Game Functions
float prob(Player, Player, Card*); //?
void shuffle(Card*);
void stand(Player, Player, Card*);
void dlCrds(Player&, Player&, Card*);
bool check21(Player, Player);
void output(Player&, Player&, Card*);


int main () {
    // Declarations & Initializations
    srand(static_cast<unsigned int>(time(0)));

    char in;
    int dkSize = 52;
    Player plyr, dealer;
    dealer.setDeal(true);
    Card myDeck[dkSize];

    crtDeck(myDeck);
    
    std::cout << "Welcome to Twenty-One!" << std::endl;
    menu();
    while(std::cin >> in) {
        if (in == 'P' || in == 'p') {
            std::cout << "Starting..." << std::endl;
            break;
        }
        else if (in == 'R' || in == 'r') {
            rules();
            menu();
        }
        else {std::cout << "Quitting."; return 0;}
    }
    sleep(3);

    // Game Start
    bool end = false;
    while(!end){
        dlCrds(plyr, dealer, myDeck);
        output(plyr, dealer, myDeck);
        while (std::cin >> in){
            if (check21(plyr, dealer)) {
                break;
            }
            else if (dealer.getT2() == 21) {
                std::cout << "You lose." << std::endl;
                break;
            }

            if (in == 'Q' || in == 'q') {
                std::cout << "Quitting...";
                return 0;
            }
            else if (in == 'H' || in == 'h') {
                plyr.deal(myDeck);
                plyr.addVals();
                output(plyr, dealer, myDeck);
                if (plyr.getT1() == 21 || plyr.getT2() == 21) {
                    std::cout << "You win!" << std::endl;
                    break;
                }
                else if (plyr.getT1() > 21) {
                    std::cout << "You busted." << std::endl;
                    break;
                }
            }
            else if (in == 'S' || in == 's') {
                stand(plyr, dealer, myDeck);
                dealer.setDeal(true);
                break;
            }
            else if (in == 'P' || in == 'p') {
                std::cout << "Function has not been implemented yet." << std::endl;
                //std::cout << "You decided to split." << std::endl;
            }
            else {
                std::cout << "Invalid input." << std::endl;
            }  
        }
        plyr.clrHand();
        dealer.clrHand();

        sleep(5);
        std::cin.clear();
        std::cout << "\n\n";
    }
        
        

    return 0;
}


// PRE-GAME FUNCTIONS
void crtDeck(Card* deck) {
    for (int i = 0; i < 13; i ++) {
        deck[i].setRank(i+1);
        deck[i].setSuit(1);

        deck[i+13].setRank(i+1);
        deck[i+13].setSuit(2);

        deck[i+26].setRank(i+1);
        deck[i+26].setSuit(3);

        deck[i+39].setRank(i+1);
        deck[i+39].setSuit(4);

        if (i == 0) {
            deck[i].setSoft(11);
            deck[i+13].setSoft(11);
            deck[i+26].setSoft(11);
            deck[i+39].setSoft(11);
        }
    }
}

// MENU FUNCTIONS

void menu() {
    std::cout << "========================================== M E N U =========================================" << std::endl;
    std::cout << "What would you like to do?\n(P/p) to play\n(R/r) to see rules/how to play\n(Q/q) to quit" << std::endl;
    std::cout << ">";
}

void rules() {
    std::cout << "============================================================================================" << std::endl;
    std::cout << "You will be given two cards and then decide to hit or stand." << std::endl;
    std::cout << "Input H/h to hit, which will give you another card" << std::endl;
    std::cout << "And input S/s to stand, which you finalize your hand." << std::endl;
    std::cout << "And input P/p to to split, which lets you have two hands when your initial hand is duplicates." << std::endl;
    std::cout << "And input Q/q to quit." << std::endl;
    std::cout << "Your goal is achieve a total of or close to 21 between your cards." << std::endl;
    std::cout << "============================================================================================" << std::endl;
}


// GAME FUNCTIONS

float prob(Player p, Player d, Card* deck) {
    int safeCards = 0;
    int bustCards = 0;
    
    int currentHardScore = p.getT1();

    for (int i = 0; i < 52; i++) {
        if (!deck[i].isInDk()) {
            continue;
        }

        int cardVal = deck[i].getRank();
        if (cardVal > 10) { 
            cardVal = 10;
        } 

        if (currentHardScore + cardVal <= 21) {
            safeCards++;
        } else {
            bustCards++;
        }
    }

    int totalRemaining = safeCards + bustCards;

    if (totalRemaining == 0) return 0.0f;

    return ((float)safeCards / totalRemaining * 100.0f);
}


void stand(Player plyr, Player d, Card* deck) {
    d.setDeal(false);
    while (true) {
        if (d.getT1() >= 17) {
            break;
        }
        d.deal(deck);
        d.addVals();
        }
    std::cout << "New/Revealed Dealer Hand: ";
    d.showHnd();

    if (((plyr.getT1() < d.getT1() ) && (d.getT1() <= 21) || d.getT2() == 21)){
        std::cout << "You lose." << std::endl;
    }
    else if (plyr.getT1() == d.getT1()) {
        std::cout << "You pushed with the dealer." << std::endl;
    }
    else {
        std::cout << "You win!" << std::endl;
    }
}

void dlCrds(Player& p, Player& d, Card* deck) {
    for (int i = 0; i < 2; i++) {
            p.deal(deck);
            d.deal(deck);
        }
}

void output(Player& p, Player& d, Card* deck) {
    std::cout << "Your cards: ";
    p.showHnd();
    std::cout << "Dealer cards: "; 
    d.showHnd();

    p.addVals();
    d.addVals();
    
        std::cout << "Hit safety: ";
    std::cout << std::setprecision(2) << std::fixed << prob(p, d, deck) <<  " %"<< std::endl;
    std::cout << "Input: ";
}

void hit(Player& p, Card* deck) {
    p.deal(deck);
    p.addVals();

    if (p.getT1() == 21) {
        std::cout << "You win!" << std::endl;
    }
}

bool check21(Player p, Player d) {
    if (p.getT1()== 21 || p.getT2() == 21) {
        if (d.getT1() == 21 || d.getT2() == 21) {
            std::cout << "It's a push! (You tied 21)" << std::endl;
            return true;
        }
        else {
            std::cout << "You win!" << std::endl;
            return true;
        }
    }
    return false;
}