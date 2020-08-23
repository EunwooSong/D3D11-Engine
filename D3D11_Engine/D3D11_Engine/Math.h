#pragma once
#include "stdafx.h"

//-----------------------------------------------
// VECTOR 2
//-----------------------------------------------
typedef struct Vector2 : XMFLOAT2 {
public:
	explicit Vector2() { x = 0; y = 0; };
	explicit Vector2(float _x, float _y) { x = _x; y = _y; };
	explicit Vector2(const POINT point) { x = point.x; y = point.y; };

	//Operators ==, +, -, *, /
	bool operator == (const Vector2& rhs) const {
		return (x == rhs.x && y == rhs.y);
	}
	Vector2 operator + (const Vector2& rhs) const {
		return Vector2(x + rhs.x, y + rhs.y);
	}
	Vector2 operator - (const Vector2& rhs) const {
		return Vector2(x - rhs.x, y - rhs.y);
	}
	Vector2 operator * (float rhs) const {
		return Vector2(x * rhs, y * rhs);
	}
	Vector2 operator / (float rhs) const {
		return Vector2(x / rhs, y / rhs);
	}
	//------------------------------------------

	float norm() const {
		return hypot(x, y);
	}

	Vector2 normalize() const{
		return Vector2(x / norm(), y / norm());
	}

	float polar() const {
		return fmod(atan2(y, x) + 2 * XM_PI, 2 * XM_PI);
	}
	
	float dot(const Vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	
	float cross(const Vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	float angle(const Vector2& rhs) const {
		return atan2(this->x - rhs.x, this->y - rhs.y);
	}

}Vec2, VEC2;

//-----------------------------------------------
// Rect 2D
//-----------------------------------------------
typedef struct Rect : RECT {
public:
	Rect() { left = 0; right = 0; top = 0; bottom = 0; };

	explicit Rect(int left, int right, int top, int bottom) {
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	};

	explicit Rect(int right, int bottom) {
		this->left = 0;
		this->right = right;
		this->top = 0;
		this->bottom = bottom;
	}

	bool Intersects(Rect r) {
		Rect intersect;
		return IntersectRect(&intersect, this, &r);
	}

	bool Contain(Vec2 p) {
		return left < p.x&& p.x < right&& top < p.y&& p.y < bottom;
	}

	Rect Offset(Vec2 p) {
		Rect r = *this;
		r.left += p.x;
		r.right += p.x;
		r.top += p.y;
		r.bottom += p.y;
		return r;
	}

	float Width() {
		return right - left;
	}

	float Height() {
		return bottom - top;
	}

	Vec2 Center() {
		return Vec2(Width(), Height()) / 2.0f;
	}

	Vec2 Center(Vec2 pos) {
		return Center() + pos;
	}
};

//-----------------------------------------------
// Color
//-----------------------------------------------
typedef struct Color {
private:
	float a;
	float r;
	float g;
	float b;

public:
	Color() { a = 0; r = 0; g = 0; b = 0; };
	Color(const Color&);
	bool operator == (const Color& rhs) {
		return a == rhs.a && r == rhs.r && g == rhs.g && b == rhs.b;
	}
	float* getColorArray() {
		float tmp[] = { a, r, g, b };
		return tmp;
	}
};


//-----------------------------------------------
// Functions
//-----------------------------------------------
inline double Interval(Vector2 a, Vector2 b) {
	return acos(a.dot(b) / a.norm() * b.norm());
}

inline float random(float min, float max) {
	static default_random_engine random(timeGetTime());
	uniform_real_distribution<float> d(min, max);
	return d(random);
}

inline int random(int min, int max) {
	static default_random_engine random(timeGetTime());
	uniform_int_distribution<int> d(min, max);
	return d(random);
}

template <class T>
inline T Clamp(T v1, T max) {
	v1 = v1 > max ? max : v1;
	return v1;
}

template <class T>
inline T Clamp(T v1, T max, T min) {
	v1 = v1 > max ? max : (v1 < min) ? min : v1;
	return v1;
}

template <class T>
inline T Lerp(T start, T end, float v) {
	v = clamp(v, 1.0f);
	return start + (end - start) * v;
}