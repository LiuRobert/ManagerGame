#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <SFML\System\Vector2.hpp>

class Vector2D
{
public:
	Vector2D();
	Vector2D(const float& x, const float& y);
	Vector2D(const Vector2D& other) = default;
	~Vector2D();
	
	Vector2D& operator+(const Vector2D& rhs);
	Vector2D& operator-(const Vector2D& rhs);
	Vector2D& operator*(const float& rhs);
	Vector2D& operator/(const float& rhs);
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	Vector2D& operator*=(const float& rhs);
	Vector2D& operator/=(const float& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

	float angle() const;
	float angle(const Vector2D& v) const;
	void normalize();
	Vector2D getNormalized();
	float length() const;
	
	sf::Vector2f sfmlVector() const;

	float x;
	float y;
};


#endif // VECTOR_H
