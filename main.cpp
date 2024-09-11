#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Quadratic{
private:
    double a;
    double b;
    double c;

public:
Quadratic(double ta = 1, int tb = 0, int tc = 0) { a = ta; b = tb; c = tc;}
//Postcondition: The class has ben constructed using default values of 1 
void setA(double a);
void setB(double b);
void setC(double c);
//Postcondition: 
double getA() const;
//Postcondition: returns a coefficient
double getB() const;
//Postcondition: returns b coefficient
double getC() const;
//Postcondition: returns c constant
double evaluate_y(double x);
//Postcondition: the equation has been evaluted using user-given value x
void evaluate_x();
//Postcondition: The quadratic formula is performed, and all real solutions are found and displayed
friend Quadratic operator*(const Quadratic&, double);
// Postcondition: The return value is the quadratic expression obtained by
// multiplying each of q’s coefficients by a factor.
friend Quadratic operator+(const Quadratic&, const Quadratic&);
// Postcondition: The return value is the quadratic expression obtained
// by adding two equations. For example, the a coefficient of the return value
// is the sum of equation 1's a coefficient and equation 2's a coefficient.
friend ostream& operator <<(ostream&, const Quadratic& out);
//Postcondition: The equation is outputted with parentheses and powers diplayed
//ie: (a)x^2 + (b)x + (c)
friend istream& operator >>(istream&, const Quadratic& in);
//Postcondition: Inputs in all coefficeints, accounting for the fact that a > 0

};

void Quadratic::setA(double a){this -> a = a;} //setters and getters
void Quadratic::setB(double b){this -> b = b;}
void Quadratic::setC(double c){this -> c = c;}
double Quadratic::getA() const {return a;}
double Quadratic::getB() const {return b;}
double Quadratic::getC() const {return c;}

istream& operator>>(istream& ins, Quadratic& in){
    double tA(0), tB(0), tC(0);
    bool checkA = true;

    //only want to input a number != 0 for A since a 0 would turn this into a linear function
    while(checkA)
    {
        cout << "Input A: ";
        ins >> tA;
        if (tA != 0)
        {
           checkA = false;
           in.setA(tA);
        }else{
            cout << "Invalid input. Please do not put 0. " << endl;
        }
    }

    //take in B and C 
    cout << "Input B and C: ";
    ins >> tB >> tC;
    in.setB(tB);
    in.setC(tC);
    return ins;
}

ostream& operator<<(ostream& os, const Quadratic& out)
{
    //outputting the equation
    os << "(" << out.a << ")x^2 + (" << out.b << ")x + (" << out.c << ")" << endl;
    return os;
}

Quadratic operator+(const Quadratic& left, const Quadratic& right)
{
    //creating new total coeffcients for a,b,c from the left and right equations
    double ta = (left.a + right.a);
    double tb = (left.b + right.b);
    double tc = (left.c + right.c);
    Quadratic result(ta, tb, tc);

    return result;

}

Quadratic operator*(const Quadratic& given, double factor)
{
    //new total coefficients by multiplying the orignal by the scaling factor
    double ta = (given.a * factor);
    double tb = (given.b * factor);
    double tc = (given.c * factor);
    Quadratic result(ta,tb,tc);

    return result;
}

void Quadratic::evaluate_x()
{
    //we need to find the two solutions that each quadratic has and store them
    double discriminant(0);
    double solution1;
    double solution2;

    //for now this program can only handle real solutions so if the discriminant is < 0 it'll be imaginary
    try
    {
        discriminant = pow(b,2.0) - 4*a*c; 
        if (discriminant < 0)
        {
           throw discriminant;
        }
        // if we do get a real solution we complete the quadratic formula and output it
        solution1 = ((b * -1) + sqrt(discriminant)) / (2 * a);
        solution2 = ((b * -1) - sqrt(discriminant)) / (2 * a);
        cout << "Solution 1: x = " << solution1 << endl;
        cout << "Solution 2: x = " << solution2 << endl;
        return;

    }
    catch(double x)
    {
        cout << "No real solutions" << endl;
        return;
    }

    return;
    
}

double Quadratic::evaluate_y(double x)
{
    //plugging in the given x value to return the y
    double y(0);
    y += pow(x,2.0) * a;
    y += x * b;
    y += c;

    return y;
}

int main()
{
    Quadratic firstEquation;
    Quadratic secondEquation;

    cout << "First Equation: " << endl;
    cin >> firstEquation;
    cout << firstEquation;
    cout << endl << "Second Equation: " << endl;
    cin >> secondEquation;
    cout << secondEquation;

    Quadratic addition = firstEquation + secondEquation;
    cout << endl << "Addition: ";
    cout << addition;

    double factor;
    cout << endl << "Enter a factor to multiply by: ";
    cin >> factor;
    Quadratic mult1 = firstEquation * factor;
    Quadratic mult2 = secondEquation * factor;

    cout << "Scaled Equation 1: ";
    cout << mult1;
    cout << "Scaled Equation 2: ";
    cout << mult2;

    cout << endl << "Solutions to the equations: " << endl;
    cout << "Equation 1: " << endl;
    firstEquation.evaluate_x();
    cout << "Equation 2: " << endl;
    secondEquation.evaluate_x();

    double x;
    cout << endl << "Finding f(x): " << endl;
    cout << "Input x: ";
    cin >> x;

    double y1(0), y2(0);
    y1 = firstEquation.evaluate_y(x);
    y2 = secondEquation.evaluate_y(x);
    cout << "First Equation: " << y1 << endl;
    cout << "Second Equation: " << y2 << endl;

    cout << endl << "Since no getters were used, here is a demonstration of the 1st Equation: " << endl;
    cout << "A: " << firstEquation.getA() << " B: " << firstEquation.getB() << " C: " << firstEquation.getC() << endl;

    return 0;
    

}

