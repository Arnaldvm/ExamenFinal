// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "p2Point.h"

class Projectile
{
public:

	p2Point<float> point;
	p2Point<float> speed;

	Projectile() {

		point.SetToZero();
		speed.SetToZero();
	}

	p2Point<float> getCurrentPosition(float t) const {

		p2Point<float> tmp;
		tmp.x = point.x + (speed.x * t);
		tmp.y = point.y + (speed.y * t);

		return tmp;
	}


	

};

#endif // __P2POINT_H__