#pragma once
#include <cmath>

struct Vector2D {
public:
	float x = 0.0f;
	float y = 0.0f;

	Vector2D() : x(0.0f), y(0.0f) {}

	Vector2D(float xVal, float yVal) : x(xVal), y(yVal) {}

	static Vector2D one() {
		return Vector2D(1.0f, 1.0f);
	}
	static Vector2D zero() {
		return Vector2D(0.0f, 0.0f);
	}

	static Vector2D up() {
		return Vector2D(0.0f, -1.0f);
	}

	static Vector2D right() {
		return Vector2D(1.0f, 0.0f);
	}

	static Vector2D down() {
		return Vector2D(0.0f, 1.0f);
	}

	static Vector2D left() {
		return Vector2D(-1.0f, 0.0f);
	}

	Vector2D& add(const Vector2D& vector)
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}

	Vector2D& subtract(const Vector2D& vector)
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
	Vector2D& multiply(const Vector2D& vector)
	{
		x *= vector.x;
		y *= vector.y;
		return *this;
	}

	Vector2D& multiply_float(const float val) {
		x *= val;
		y *= val;
		return *this;
	}

	Vector2D& divide(const Vector2D& vector)
	{
		x /= vector.x;
		y /= vector.y;
		return *this;
	}

	Vector2D& normalize()
	{
		if (x == 0.0f && y == 0.0f) { return *this; }

		const float magnitude = std::sqrt(x * x + y * y);
		x /= magnitude;
		y /= magnitude;
		return *this;
	}

	static float distance(Vector2D v1, Vector2D v2) {
		
		const float x = v2.x - v1.x;
		const float y = v2.y - v1.y;

		return std::sqrt(x * x + y * y);
	}

	friend Vector2D operator+(Vector2D v1, const Vector2D& v2) { return v1.add(v2); }
	friend Vector2D operator-(Vector2D v1, const Vector2D& v2) { return v1.subtract(v2); }
	friend Vector2D operator*(Vector2D v1, const Vector2D& v2) { return v1.multiply(v2); }
	friend Vector2D operator/(Vector2D v1, const Vector2D& v2) { return v1.divide(v2); }

	friend Vector2D operator*(Vector2D v1, const float value) { return v1.multiply_float(value); }
	Vector2D& operator*=(const float value) { return this->multiply_float(value); }

	Vector2D& operator+=(const Vector2D& v2) { return this->add(v2); }
	Vector2D& operator-=(const Vector2D& v2) { return this->subtract(v2); }
	Vector2D& operator*=(const Vector2D& v2) { return this->multiply(v2); }
	Vector2D& operator/=(const Vector2D& v2) { return this->divide(v2); }

	friend bool operator < (Vector2D v1, Vector2D v2) {
		return v1.x < v2.x&& v1.y < v2.y;
	}

	friend bool operator > (Vector2D v1, Vector2D v2) {
		return v1.x > v2.x&& v1.y > v2.y;
	}

	friend bool operator!= (Vector2D v1, Vector2D v2) {
		return v1.x != v2.x || v1.y != v2.y;
	}
	friend bool operator== (Vector2D v1, Vector2D v2) {
		return v1.x == v2.x && v1.y == v2.y;
	}
};

struct Transform
{
protected:
	Vector2D position_ = Vector2D::one();
	Vector2D scale_ = Vector2D::one();

public:
	Transform() = default;

	Transform(float x, float y, float xS, float yS) {
		position_.x = x;
		position_.y = y;
		scale_.x = xS;
		scale_.y = yS;
	}

	Transform(Vector2D position, Vector2D scale) {
		position_ = position;
		scale_ = scale;
	}

	inline Vector2D& get_position() { return position_; }
	inline void set_position(const Vector2D& newPosition) { position_ = newPosition; }
	inline void set_position(const float xPos, const float yPos) { position_.x = xPos; position_.y = yPos; }
	inline void add_position(const Vector2D& posAdd) { position_ += posAdd; }
	inline void add_position(const float xPos, const float yPos) { position_ += Vector2D(xPos, yPos); }


	inline Vector2D& get_scale() { return scale_; }
	inline void set_scale(const Vector2D& newScale) { scale_ = newScale; }
	inline void set_scale(const float xScale, const float yScale) { scale_.x = xScale; scale_.y = yScale; }

};