#ifndef KNIGHT_HPP
#define KNIGHT_HPP

#include <string>

class Knight {
private:
    bool white;

public:
    Knight(bool color);
    void setColor(bool color);
    bool getColor();
    void display() const;
};

#endif 
