#include <cstdlib>
#include <iostream>
#include <string>

enum class Stress_ball_colors
{
    red,
    blue,
    yellow,
    green
};

enum class Stress_ball_sizes
{
    small,
    medium,
    large
};

// Write a class Stress_ball which represents a stress ball.
class Stress_ball
{

    // The class default constructor creates a stress ball with a randomly selected color and size
    // every time the constructor is called.
    // Use only the following colors: red, blue, yellow, and green, and sizes: small, medium, and large.
    // Apply enum class Stress_ball_colors to define colors and Stress_ball_sizes for sizes.
public:
    Stress_ball()
    {
        color = Stress_ball_colors(rand() % 4);
        size = Stress_ball_sizes(rand() % 3);
    };
    // (b) The class parameterized constructor creates a stress ball with a given color and size: Stress_ball(Stress_ball_colors c, Stress_ball_sizes s)
    Stress_ball(Stress_ball_colors c, Stress_ball_sizes s)
    {
        color = c;
        size = s;
    };

    // (c) The function get_color() returns the color of a stress ball using the enum class Stress_ball_colors

    Stress_ball_colors get_color() const
    {
        return (color);
    };

    // (d) The function get_size() returns the size of a stress ball using the enum class Stress_ball_sizes

    Stress_ball_sizes get_size() const
    {
        return (size);
    };
    // (e) The operator ==(const Stress_ball& sb) returns true if sb's color and size are the same as color and size of the stress ball this (object calling the operator).
    bool operator==(const Stress_ball &sb)
    {
        if ((sb.get_color() == get_color()) && (sb.get_size() == get_size()))
            return true;
        return false;
    };

private:
    Stress_ball_colors color;
    Stress_ball_sizes size;
};

// (f) Outside of this class: overload operator<<(std::ostream& o, const Stress_ball& sb); to print a stress ball as a pair of color and size in this form: (color, size). Example: (red, small)
std::ostream &operator<<(std::ostream &o, const Stress_ball &sb)
{
    // can't do this because sb.get_color() is not a string :  << "(" << sb.get_color() << "," << sb.get_size() << ")" << std::endl;
    o << "(";
    //color
    if (Stress_ball_colors::red == sb.get_color())
    {
        o << "red";
    }
    else if (Stress_ball_colors::blue == sb.get_color())
    {
        o << "blue";
    }
    else if (Stress_ball_colors::yellow == sb.get_color())
    {
        o << "yellow";
    }
    else if (Stress_ball_colors::yellow == sb.get_color())
    {
        o << "green";
    }
    o << ",";
    //size
    if (Stress_ball_sizes::small == sb.get_size())
    {
        o << "small";
    }
    else if (Stress_ball_sizes::medium == sb.get_size())
    {
        o << "medium";
    }
    else if (Stress_ball_sizes::large == sb.get_size())
    {
        o << "large";
    }
    o << ")";
}
