#ifndef CARD_H
#define CARD_H

#include <string>
#include <cstring>

class Card {
    private:
    int suit, soft;

    protected:
    bool inDeck;
    int rank;

    public:
    Card(int s, int r) { 
        inDeck = true;
        suit = s;
        rank = r;
        soft = 0;
    }
    
    Card() {
        inDeck = true;
        suit = 0;
        rank = 0;
        soft = 0;
    }

    // Set Functions

    void setStat(bool d) {
        inDeck = d;
    }

    void setSuit(int s) {
        suit = s;
    }

    void setRank(int r) {
        rank = r;
    }

    void setSoft(int s) {
        soft = s;
    }

    // Get Functions
    
    bool isInDk() {
        return inDeck;
    }

    int getSuit() {
        return suit;
    }

    int getRank() {
        return rank;
    }

    int getSoft() {
        return soft;
    }

    // Other Functions

    void display() {
        
        if (rank == 1) {
            std::cout << 'A';
        } 
        else if (rank <= 10) {
            std::cout << getRank();
        }
        else {
            if (rank == 11) {
                std::cout << 'J';
            }
            else if (rank == 12) {
                std::cout << 'Q';
            }
            else {
                std::cout << 'K';
            }
        }

        switch (this->suit) {
            case 1:
                std::cout << "♣";
                break;
            case 2:
                std::cout << "♥";
                break;
            case 3:
                std::cout << "♠";
                break;
            case 4:
                std::cout << "♦";
                break;
        }
        
        //std::cout << "___ ___\n| " << getNum() << "    |\n|      |\n|      |\n|    " << getNum() << " |\n";
    }

};


#endif