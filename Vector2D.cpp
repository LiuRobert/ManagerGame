#include "Vector2D.h"
#include <math.h>


Vector2D::Vector2D()
{
}

Vector2D::Vector2D(const float& x, const float& y)
{
	this->x = x;
	this->y = y;
}

Vector2D::~Vector2D()
{
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator*(const float& rhs) const
{
	return Vector2D(x * rhs, y * rhs);
}

Vector2D Vector2D::operator/(const float& rhs) const
{
	return Vector2D(x / rhs, y / rhs);
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	return *this + rhs;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	return *this - rhs;
}

Vector2D& Vector2D::operator*=(const float& rhs)
{
	return *this * rhs;
}

Vector2D& Vector2D::operator/=(const float& rhs)
{
	return *this / rhs;
}

float Vector2D::angle() const
{
	Vector2D v = this->getNormalized();
	return atan2(v.x, v.y);
}

float Vector2D::angle(const Vector2D& v) const
{
	Vector2D v1 = this->getNormalized();
	Vector2D v2 = v.getNormalized();
	return atan2(v1.x, v1.y) - atan2(v2.x, v2.y);
}

void Vector2D::normalize()
{
	*this = *this/length();
}

Vector2D Vector2D::getNormalized() const
{
	Vector2D v(*this);
	v.normalize();
	return v;
}

float Vector2D::length() const
{
	return sqrtf(x * x + y * y);
}

sf::Vector2f Vector2D::sfmlVector() const
{
	return sf::Vector2f(x, y);
}


std::ostream& operator <<(std::ostream& os, const Vector2D& v)
{
	os <<"x:" <<v.x <<" y:" <<v.y;
	return os;
}


