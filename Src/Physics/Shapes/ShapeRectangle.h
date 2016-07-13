#pragma once
#include "stdincl.h"
#include "Shape.h"

class ShapeRectangle : public Shape
{
public:

	ShapeRectangle();
	ShapeRectangle(Vector2f center, Vector2f size);
	~ShapeRectangle();

	Vector2f						Overlapped(Shape* shape);
	void							UpdatePosition(Vector2f pos);

private:

	Vector2f						Overlaps(ShapeRectangle* rect);

	Vector2f						m_size;
};
