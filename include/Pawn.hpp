#ifndef PAWN_HPP
#define PAWN_HPP

#include <string>

class Pawn {
private:
    bool white;

public:
    Pawn(bool color);
    void setColor(bool color);
    bool getColor();
    void display() const;
};

#endif 
