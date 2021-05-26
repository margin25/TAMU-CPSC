/**
 * In this file, implement the methods from Jeans.h. The implementation is identical to Stress_ball
 * This file needs to be uploaded to Mimir
 */
#include "Jeans.h"
Jeans::Jeans()
{
    color = Jeans_colors(rand() % 4);
    size = Jeans_sizes(rand() % 4);
};
// (b) The class parameterized constructor creates a stress ball with a given color and size: Stress_ball(Stress_ball_colors c, Stress_ball_sizes s)
Jeans::Jeans(Jeans_colors c, Jeans_sizes s)
{
    color = c;
    size = s;
};

// (c) The function get_color() returns the color of a stress ball using the enum class Stress_ball_colors
Jeans_colors Jeans::get_color() const
{
    return (color);
};

// (d) The function get_size() returns the size of a stress ball using the enum class Stress_ball_sizes

Jeans_sizes Jeans::get_size() const
{
    return (size);
};

// (e) The operator ==(const Stress_ball& sb) returns true if sb's color and size are the same as color and size of the stress ball this (object calling the operator).
bool Jeans::operator==(const Jeans &sb)
{
    if ((sb.get_color() == get_color()) && (sb.get_size() == get_size()))
        return true;
    return false;
};

// (f) Outside of this class: overload operator<<(std::ostream& o, const Stress_ball& sb); to print a stress ball as a pair of color and size in this form: (color, size). Example: (red, small)
std::ostream &operator<<(std::ostream &o, const Jeans &sb)
{
    // can't do this because sb.get_color() is not a string :  << "(" << sb.get_color() << "," << sb.get_size() << ")" << std::endl;
    o << "(";
    //color
    if (Jeans_colors::white == sb.get_color())
    {
        o << "white";
    }
    else if (Jeans_colors::black == sb.get_color())
    {
        o << "black";
    }
    else if (Jeans_colors::blue == sb.get_color())
    {
        o << "blue";
    }
    else if (Jeans_colors::grey == sb.get_color())
    {
        o << "grey";
    }
    o << ", ";
    //size
    if (Jeans_sizes::small == sb.get_size())
    {
        o << "small";
    }
    else if (Jeans_sizes::medium == sb.get_size())
    {
        o << "medium";
    }
    else if (Jeans_sizes::large == sb.get_size())
    {
        o << "large";
    }
    else if (Jeans_sizes::xlarge == sb.get_size())
    {
        o << "xlarge";
    }
    o << ")";

    return o;
}