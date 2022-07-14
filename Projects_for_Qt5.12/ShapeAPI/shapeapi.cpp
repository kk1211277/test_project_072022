#include <typeinfo>
#include <cmath>
#include "shapeapi.h"


//++++++++++++ Point ++++++++++++

Point::Point()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Point::Point(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Point& Point::operator+=(const Point& p) {
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
}

const Point Point::operator+(const Point& p) const {
    return Point(*this) += p;
}

Point& Point::operator-=(const Point& p) {
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
}

const Point Point::operator-(const Point& p) const {
    return Point(*this) -= p;
}

Point& Point::operator/=(const double div) {
    x /= div;
    y /= div;
    z /= div;
    return *this;
}

const Point Point::operator/(const double div) const {
    return Point(*this) /= div;
}

std::ostream& operator<<(std::ostream& os, const Point& prnt)
{
    os << " " << std::fixed << prnt.x << ", " << prnt.y << ", " << prnt.z << " ";
    return os;
}



//++++++++++++ Vector3d ++++++++++++
Vector3d::Vector3d()
{
    begin = Point{ 0.0, 0.0, 0.0 };
    end = Point{ 0.0, 0.0, 0.0 };
}

Vector3d::Vector3d(Point _begin, Point _end)
{
    begin = _begin;
    end = _end;
}

double Vector3d::length(Point _begin, Point _end)
{
    Point dif = _end - _begin;
    return sqrt(pow(dif.x, 2) + pow(dif.y, 2) + pow(dif.z, 2));
}

double Vector3d::length() const
{
    return Vector3d::length(begin, end);
}






//++++++++++++ Shape ++++++++++++
Shape::Shape()
{
    ref = Point{ 0.0, 0.0, 0.0 };
}

Shape::Shape(Point _ref)
{
    ref = _ref;
}

Point Shape::move(Point dP)
{
    return ref += dP;
}



//++++++++++++ Circle ++++++++++++
Circle::Circle() : Shape()
{
    radius = 0.0;
}

Circle::Circle(double _radius) : Shape()
{
    radius = _radius;
}

Circle::Circle(double _radius, Point _ref) : Shape(_ref)
{
    radius = _radius;
}

Point Circle::get_ref() const
{
    return ref;
}

Point Circle::get_point(double t) const
{
    Point tmp;
    tmp.x = radius * cos(t) + ref.x;
    tmp.y = radius * sin(t) + ref.y;
    tmp.z = ref.z;
    return tmp;
}

Point Circle::get_vector_dr(double t) const
{
    Point tmp;
    tmp.x = -1.0 * radius * sin(t);
    tmp.y = radius * cos(t);
    tmp.z = 0;
    return tmp;
}

Point Circle::get_vector_T(double t) const
{
    Point tmp = Circle::get_vector_dr(t);
    tmp /= Vector3d::length(Point(), tmp);
    return tmp;
}

double Circle::get_radius() const
{
    return radius;
}

void Circle::print(double t, int param)  const
{
    std::cout << typeid(*this).name() << "\t";
    std::cout << "P={" << get_point(t) << "}\t";
    switch(param)
    {
        case 0: std::cout << "dr={" << get_vector_dr(t) << "}" << std::endl;  break;
        case 1: std::cout << "T={" << get_vector_T(t) << "}" << std::endl;  break;
        default: std::cout << "error param" << std::endl;  break;
    }
}


//++++++++++++ Ellipse ++++++++++++
Ellipse::Ellipse() : Circle()
{
    radius2 = 0.0;
}

Ellipse::Ellipse(double _radius1, double _radius2) : Circle(_radius1)
{
    radius2 = _radius2;
}

Ellipse::Ellipse(double _radius1, double _radius2, Point _ref) : Circle(_radius1, _ref)
{
    radius2 = _radius2;
}

Point Ellipse::get_ref() const
{
    return Circle::get_ref();
}

Point Ellipse::get_point(double t) const
{
    Point tmp;
    tmp.x = radius * cos(t) + Circle::get_ref().x;
    tmp.y = radius2 * sin(t) + Circle::get_ref().y;
    tmp.z = Circle::get_ref().z;
    return tmp;
}

Point Ellipse::get_vector_dr(double t) const
{
    Point tmp;
    tmp.x = -1.0 * radius * sin(t);
    tmp.y = radius2 * cos(t);
    tmp.z = 0.0;
    return tmp;
}

Point Ellipse::get_vector_T(double t) const
{
    Point tmp = Ellipse::get_vector_dr(t);
    tmp /= Vector3d::length(Point(), tmp);
    return tmp;
}

void Ellipse::print(double t, int param)  const
{
    std::cout << typeid(*this).name() << "\t";
    std::cout << "P={" << get_point(t) << "}\t";
    switch(param)
    {
        case 0: std::cout << "dr={" << get_vector_dr(t) << "}" << std::endl;  break;
        case 1: std::cout << "T={" << get_vector_T(t) << "}" << std::endl;  break;
        default: std::cout << "error param" << std::endl;  break;
    }
}


//++++++++++++ Spiral ++++++++++++
Spiral::Spiral() : Circle()
{
    step = 0.0;
}

Spiral::Spiral(double _radius, double _step) : Circle(_radius)
{
    step = _step;
}

Spiral::Spiral(double _radius, double _step, Point _ref) : Circle(_radius, _ref)
{
    step = _step;
}

Point Spiral::get_ref() const
{
    return Circle::get_ref();
}

Point Spiral::get_point(double t) const
{
    Point tmp;
    tmp.x = radius * cos(t) + Circle::get_ref().x;
    tmp.y = radius * sin(t) + Circle::get_ref().y;
    tmp.z = step / (2 * M_Pi) * t + Circle::get_ref().z;
    return tmp;
}

Point Spiral::get_vector_dr(double t) const
{
    Point tmp;
    tmp.x = -1.0 * radius * sin(t);
    tmp.y = radius * cos(t);
    tmp.z = step / (2 * M_Pi);
    return tmp;
}

Point Spiral::get_vector_T(double t) const
{
    Point tmp = Spiral::get_vector_dr(t);
    tmp /= Vector3d::length(Point(), tmp);
    return tmp;
}

void Spiral::print(double t, int param)  const
{
    std::cout << typeid(*this).name() << "\t";
    std::cout << "P={" << get_point(t) << "}\t";
    switch(param)
    {
        case 0: std::cout << "dr={" << get_vector_dr(t) << "}" << std::endl;  break;
        case 1: std::cout << "T={" << get_vector_T(t) << "}" << std::endl;  break;
        default: std::cout << "error param" << std::endl;  break;
    }
}
