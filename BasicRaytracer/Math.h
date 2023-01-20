#ifndef MATH_H
#define MATH_H

inline float sqr(float n) {
	return n * n;
}

struct Vector {
	float x, y, z;

	Vector();
	Vector(const Vector& v);
	Vector(float x, float y, float z);
	Vector(float f);

	virtual ~Vector();

	inline float length2();
	inline float length();

	float normalize();
	Vector normalized();

	//Operators

	Vector& operator =(const Vector& v);
	Vector& operator +=(const Vector& v);
	Vector& operator -=(const Vector& v);
	Vector& operator *=(float f);
	Vector& operator /=(float f);
	Vector operator -() const;
};

float dot(Vector v1, Vector v2);
Vector cross(Vector v1, Vector v2);


inline Vector operator +(const Vector& v1, const Vector& v2) {
	return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline Vector operator -(const Vector& v1, const Vector& v2) {
	return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline Vector operator *(const Vector& v1, const Vector& v2) {
	return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline Vector operator *(const Vector& v1, float f) {
	return Vector(v1.x * f, v1.y * f, v1.z * f);
}

inline Vector operator *(float f, const Vector& v1) {
	return Vector(v1.x * f, v1.y * f, v1.z * f);
}

inline Vector operator /(const Vector& v1, const Vector& v2) {
	return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline Vector operator /(const Vector& v1, float f) {
	return Vector(v1.x / f, v1.y / f, v1.z / f);
}

inline Vector operator /(float f, const Vector& v1) {
	return Vector(f/v1.x, f/v1.y, f/v1.z);
}

inline float Dot(const Vector& v1, const Vector& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

typedef Vector Point;

struct Vector2 {
	float u, v;

	Vector2();
	Vector2(const Vector2& v);
	Vector2(float u, float v);
	Vector2(float f);

	virtual ~Vector2();

	Vector2& operator =(const Vector2& v);
};


#endif