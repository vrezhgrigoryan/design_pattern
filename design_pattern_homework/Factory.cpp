#include <iostream>
#include <cmath>

class Point
{
private:
        Point(float x, float y)
            :m_x(x),
            m_y(y)
        {}
    
    class PointFactory
    {
    public:
        static Point makePolarPoint(float r, float t)
        {
            return Point{r * std::cos(t), r * std::sin(t)};
        }
        static Point makeCartesianPoint(float x, float y)
        {
            return Point{x, y};
        }
    };
public:
    static PointFactory pointFactory;
    void print()
    {
        std::cout << "x = " << m_x << "\n";
        std::cout << "y = " << m_y << "\n";
    }
private:
    float m_x;
    float m_y;
};

int main() 
{
    Point pPolar = Point::pointFactory.makePolarPoint(4, 6.28);
    pPolar.print();
    Point pCarest = Point::pointFactory.makeCarestianPoint(4, 6.28);
    pCarest.print();
    
    return 0;
}
