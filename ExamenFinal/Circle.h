#ifndef __Circle_H__
#define __Circle_H__

#include "p2Point.h"
#define PI 3.14159265358979323846

template<class TYPE>
class Circle
{
public:
	Point2D<TYPE> center;

	TYPE radius;

public:

	Circle(const TYPE& x, const TYPE& y, const TYPE& r)
	{
		center.x = x;
		center.y = y;
		radius = r;
	}

	TYPE calcArea()const
	{
		return (radius*radius*PI);
	}

	bool intersect(const Circle<TYPE>& circle)const
	{
		if ((radius + circle.radius) < (center.distanceTo(circle)))
			return true;
		return false;
	}
};


#endif