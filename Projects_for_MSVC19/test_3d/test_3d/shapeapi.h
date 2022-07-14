#ifndef SHAPEAPI_H
#define SHAPEAPI_H

#ifdef SHAPEAPI_EXPORTS
#define SHAPEAPI_EXPORT __declspec(dllexport)
#else
#define SHAPEAPI_EXPORT __declspec(dllimport)
#endif

#include <iostream>

#define M_Pi (3.14159265358979323846)

class SHAPEAPI_EXPORT Point
{
public:

    double x;
    double y;
    double z;

    Point();
    Point(double _x, double _y, double _z);

    Point& operator+= (const Point& p);
    const Point operator+ (const Point& p) const;
    Point& operator-= (const Point& p);
    const Point operator- (const Point& p) const;
    Point& operator/= (const double div);
    const Point operator/ (const double div) const;

    friend std::ostream& operator<<(std::ostream& os, const Point& prnt);
};


class SHAPEAPI_EXPORT Vector3d
{
public:
    Point begin;
    Point end;

    Vector3d();
    Vector3d(Point _begin, Point _end);

    static double length(Point _begin, Point _end);
    double length() const;
};









class SHAPEAPI_EXPORT Shape
{
protected:
    Point ref;

    Shape();
    Shape(Point _ref);
public:

    virtual ~Shape() {}

    virtual Point get_ref() const = 0; // центр
    virtual Point get_point(double t) const = 0; // точка на кривой
    virtual Point get_vector_dr(double t) const = 0; // направляющий вектор касательной (от {0, 0, 0})
    virtual Point get_vector_T(double t) const = 0; // направляющий единичный вектор касательной (от {0, 0, 0})
    virtual void print(double t, int param) const = 0;
	
    virtual Point move(Point dP); // перемещение центра на дельту
};


class SHAPEAPI_EXPORT Circle : public Shape
{
protected:
    double radius;

public:
    Circle();
    Circle(double _radius);
    Circle(double _radius, Point _ref);
    virtual ~Circle() {}

    virtual Point get_ref() const override; // центр
    virtual Point get_point(double t) const override; // точка на кривой
    virtual Point get_vector_dr(double t) const override; // направляющий вектор касательной
    virtual Point get_vector_T(double t) const override;// направляющий единичный вектор касательной
    virtual double get_radius() const;
    virtual void print(double, int param) const override;
};


class SHAPEAPI_EXPORT Ellipse : public Circle
{
protected:
    double radius2;

public:
    Ellipse();
    Ellipse(double _radius1, double _radius2);
    Ellipse(double _radius1, double _radius2, Point _ref);
    virtual ~Ellipse() {}

    virtual Point get_ref() const override; // центр
    virtual Point get_point(double t) const override; // точка на кривой
    virtual Point get_vector_dr(double t) const override; // направляющий вектор касательной
    virtual Point get_vector_T(double t) const override;// направляющий единичный вектор касательной
    virtual void print(double, int param) const override;
};



class SHAPEAPI_EXPORT Spiral : public Circle
{
protected:
    double step;

public:
    Spiral();
    Spiral(double _radius, double _step);
    Spiral(double _radius, double _step, Point _ref);
    virtual ~Spiral() {}

    virtual Point get_ref() const override; // центр
    virtual Point get_point(double t) const override; // точка на кривой
    virtual Point get_vector_dr(double t) const override; // направляющий вектор касательной
    virtual Point get_vector_T(double t) const override;// направляющий единичный вектор касательной
    virtual void print(double, int param) const override;
};



#endif // SHAPEAPI_H
