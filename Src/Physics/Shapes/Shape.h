#pragma once
#include "stdincl.h"

class ShapeRectangle;

class Shape
{
public:
	Shape();
	Shape(Vector2f center);
	~Shape();

	virtual Vector2f			Overlapped(Shape* shape);
	virtual Vector2f			Overlaps(ShapeRectangle* rect);
	virtual void				UpdatePosition(Vector2f pos);
	void						SetCenter(Vector2f center);
	

protected:

	Vector2f					m_center;

private:

};
