#include "ShapeRectangle.h"

ShapeRectangle::ShapeRectangle()
{
}

ShapeRectangle::ShapeRectangle(Vector2f center, Vector2f size) :
Shape(center),
m_size(size)
{
}

ShapeRectangle::~ShapeRectangle()
{
}

Vector2f ShapeRectangle::Overlapped(Shape* shape)
{
	return shape->Overlaps(this);
}

void ShapeRectangle::UpdatePosition(Vector2f pos)
{
	m_center = pos + m_size / 2.f;
}

Vector2f ShapeRectangle::Overlaps(ShapeRectangle* rect)
{
	float dx, dy;
	Vector2f ret = Vector2f(0.f, 0.f);

	int xsign = -(abs(rect->m_center.x - m_center.x) / (rect->m_center.x - m_center.x));
	int ysign = -(abs(rect->m_center.y - m_center.y) / (rect->m_center.y - m_center.y));


	dx = abs(m_center.x - rect->m_center.x) - (m_size.x / 2 + rect->m_size.x / 2);
	dy = abs(m_center.y - rect->m_center.y) - (m_size.y / 2 + rect->m_size.y / 2);

	if (dx < 0 && dy < 0)
	{
		ret = Vector2f(abs(dx) * xsign, 0.f);

		if (dy > dx)
		{
			ret = Vector2f(0.f, abs(dy) * ysign);
		}
	}
	
	return ret;
}