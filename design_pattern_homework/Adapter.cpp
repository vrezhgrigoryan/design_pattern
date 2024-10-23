#include <iostream>
#include <cmath>
class RoundPeg {
public:
    virtual int getRadius() const 
    {
        return R;
    }
private:
    int R;
};

class SquarePeg {
public:
    SquarePeg(int w, int h)
    {
        squareWidth = w;
        height = h;
    }
    int getWidth() const 
    {
        return squareWidth;
    }
private:
    int squareWidth;
    int height;
};

class SquarePegToRoundPeg : public RoundPeg {
private:
    SquarePeg *m_squarePeg;

public:
    SquarePegToRoundPeg(SquarePeg *squarePeg) : m_squarePeg(squarePeg) 
    {
        
    }
    int getRadius() const override 
    {
        return m_squarePeg->getWidth() * sqrt(2) / 2;
    }
};

class RoundHole
{
private:
    int Radius;
public:
    RoundHole(int R): Radius{R}
    {}
    bool fits(RoundPeg* roundPeg)
    {
        return roundPeg->getRadius() < Radius;
    }
};
int main() {
    RoundHole round(10);
    SquarePeg* rp1 = new SquarePeg(2, 6);
    SquarePeg* rp2 = new SquarePeg(15, 1);
    
    SquarePegToRoundPeg* adapter1 = new SquarePegToRoundPeg(rp1);
    SquarePegToRoundPeg* adapter2 = new SquarePegToRoundPeg(rp2);
    
    std::cout << round.fits(adapter1) << "\n"; 
    std::cout << round.fits(adapter2) << "\n"; 
    

    return 0;
}
