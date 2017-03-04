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
	
	Vector2D operator+(const Vector2D& rhs) const;
	Vector2D operator-(const Vector2D& rhs) const;
	Vector2D operator*(const float& rhs) const;
	Vector2D operator/(const float& rhs) const;
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	Vector2D& operator*=(const float& rhs);
	Vector2D& operator/=(const float& rhs);
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

	// Returns the angle between this vector and (0, 1)
	float angle() const;
	// Returns the angle between this vector and v
	float angle(const Vector2D& v) const;
	// Normalizes this vector
	void normalize();
	// Returns a new vector that is a normalized version of this vector
	Vector2D getNormalized() const;
	// Returns the length of this vector
	float length() const;
	
	sf::Vector2f sfmlVector() const;

	float x;
	float y;
};


#endif // VECTOR_H
