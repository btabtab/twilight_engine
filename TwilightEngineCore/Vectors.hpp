#pragma once

template<typename T>
class Vector
{
private:
	T x, y;
public:
	Vector(T new_x, T new_y):
	x(new_x), y(new_y)
	{
	}
	
	T getX() const
	{
		return x;
	}
	T getY() const
	{
		return y;
	}

	
	void setX(T new_x)
	{
		x = new_x;
	}
	void setY(T new_y)
	{
		y = new_y;
	}

	//Grabs the midpoint between this and another vector<t>.
	Vector<T> midpoint(const Vector<T>& other) const
	{
		return Vector<T>((x + other.getX()) / 2, (y + other.getY()) / 2);
	}
	Vector<T> operator+(const Vector<T>& other) const
	{
		return Vector<T>(x + other.getX(), y + other.getY());
	}
	void operator+=(const Vector<T>& other)
	{
		x += other.getX();
		y += other.getY();
	}

	void set(Vector<T> new_vector)
	{
		setX(new_vector.getX());
		setY(new_vector.getY());
	}

	Vector<T> operator-(const Vector<T>& other) const
	{
		return Vector<T>(x - other.getX(), y - other.getY());
	}

	Vector<T> operator*(const T& scalar) const
	{
		return Vector<T>(x * scalar, y * scalar);
	}

	// Vector<T> operator/(const T& scalar) const
	// {
	// 	if (scalar == 0) throw std::runtime_error("Division by zero in Vector division");
	// 	return Vector<T>(x / scalar, y / scalar);
	// }

	bool operator==(const Vector<T>& other) const
	{
		return (x == other.getX() && y == other.getY());
	}

	// float length() const
	// {
	// 	return std::sqrt(x * x + y * y);
	// }

	// Vector<T> normalized() const
	// {
	// 	float len = length();
	// 	if (len == 0) throw std::runtime_error("Can't normalize zero-length vector(s)");
	// 	return Vector<T>(x / len, y / len);
	// }
	float dot(const Vector<T>& other) const
	{
		return x * other.getX() + y * other.getY();
	}

	Vector<T> makePerpendicular() const
	{
		return Vector<T>(-y, x);
	}

	std::string stringify() const
	{
		return "Vector(" + std::to_string(x) + ", " + std::to_string(y) + ")";
	}
};