#include "Shape.h"

Shape::Shape()
{
}

Shape::Shape(Vector2f center) :
m_center(center)
{
}

Shape::~Shape()
{
}

Vector2f Shape::Overlapped(Shape* shape)
{
	return Vector2f(0.f, 0.f);
}

Vector2f Shape::Overlaps(ShapeRectangle* rect)
{
	return Vector2f(0.f, 0.f);
}

void Shape::UpdatePosition(Vector2f pos)
{
}


void Shape::SetCenter(Vector2f center)
{
	m_center = center;
}