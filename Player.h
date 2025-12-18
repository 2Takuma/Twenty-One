#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Card.h"


class Player {
    private:
    std::vector<Card> hand;
    std::vector<Card> second;
    bool isSplit, isDeal;
    int total1 = 0, total2 = 0;

    public:
    Player() {
        isDeal = false;
    }

    // Set functions
    void setDeal(bool b) {
        isDeal = b;
    }

    // Get Functions
    std::vector<Card> getHand() {
        return hand;
    }

    bool hasAce(){
        for (auto card : this->hand) {
            if (card.getRank() == 1) {
                return true;
            }
        }
        return false;
    }

    int getT1() {
        return total1;
    }

    int getT2() {
        return total2;
    }

    bool chkDeal() {
        return isDeal;
    }

    void showHnd() {
        if (hand.empty()) {
            std::cout << "No cards." << std::endl;
            return;
        }

        if (!isDeal) {
            for (auto card : this->hand) {
            card.display(); std:: cout << " ";
            }
            std::cout << std::endl;
        }
        else {
            hand.at(0).display(); std::cout << " X " << std::endl;
        }
    }

    // Other Functions
    void clrHand() {
        for (auto card : hand) {
            card.setStat(true);
        }
        hand.clear();
        total1 = 0;
        total2 = 0;
    }

    void hit(Card c) {
        hand.push_back(c);
    }

    void addVals() {
        int t1 = 0, t2 = 0;
        bool hsAce = false;

        for (auto& card : hand) {
            int val = card.getRank();

            if (card.getRank() >= 10){
                t1 += 10;
                t2 += 10;
            }
            else {
               t1 += card.getRank();
               t2 += card.getRank();
            }

            if (card.getRank() == 1) {
                t2 += 11;
            }
        }
        
        total1 = t1;
        total2 = t2;
    }
    
    void deal(Card* deck) {
        int rc;
        do {
            rc = (rand() % 52);
        } while(!deck[rc].isInDk());
        hand.push_back(deck[rc]);
        deck[rc].setStat(false);
    }

};

#endif