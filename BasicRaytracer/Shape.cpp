#include "Shape.h"

#include <cmath>
ShapeSet::ShapeSet()
{
}

ShapeSet::~ShapeSet()
{
}

void ShapeSet::addShape(Shape* shape)
{
}

bool ShapeSet::intersect(Intersection& intersection)
{
	bool doesIntersect = false;

	for (auto iter : shapes)
	{
		Shape* curShape = iter;
		if (curShape->intersect(intersection))
			doesIntersect = true;
	}

	return doesIntersect;
}

bool ShapeSet::doesIntersect(const Ray& ray)
{
	for (auto iter : shapes)
	{
		Shape* curShape = iter;
		if (curShape->doesIntersect(ray))
			return true;
	}

	return false;
}

Plane::Plane(const Point& position, const Vector& normal)
	:position(position), normal(normal)
{
}

Plane::~Plane()
{
}

bool Plane::intersect(Intersection& intersection)
{
	float dDotN = dot(intersection.ray.direction, normal);

	if (dDotN == 0.0f) {
		return false;
	}

	float t = dot(position - intersection.ray.origin, normal) / dDotN;

	if (t <= RAY_T_MIN || t >= intersection.t) {
		return false;
	}

	intersection.t = t;
	intersection.pShape = this;

	return true;
}

bool Plane::doesIntersect(const Ray& ray)
{
	float dDotN = dot(ray.direction, normal);

	if (dDotN == 0.0f) {
		return false;
	}

	float t = dot(position - ray.origin, normal) / dDotN;

	if (t <= RAY_T_MIN || t >= ray.tMax) {
		return false;
	}

	return true;
}

Sphere::Sphere(const Point& center, float radius)
	: center(center), radius(radius)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Intersection& intersection)
{
	Ray localRay = intersection.ray;
	localRay.origin -= center;

	float a = localRay.direction.length2();
	float b = 2 * dot(localRay.direction, localRay.origin);
	float c = localRay.origin.length2() - sqr(radius);

	float discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f) {
		return false;
	}

	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	if (t1 > RAY_T_MIN && t1 < intersection.t) {
		intersection.t = t1;
	}
	else if (t2 > RAY_T_MIN && t2 < intersection.t) {
		intersection.t = t2;
	}
	else {
		return false;
	}

	intersection.pShape = this;

	return true;
}

bool Sphere::doesIntersect(const Ray& ray)
{
	Ray localRay = ray;
	localRay.origin -= center;

	float a = localRay.direction.length2();
	float b = 2 * dot(localRay.direction, localRay.origin);
	float c = localRay.origin.length2() - sqr(radius);

	float discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f) {
		return false;
	}

	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	if (t1 > RAY_T_MIN && t1 < ray.tMax) {
		return true;
	}

	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	if (t2 > RAY_T_MIN && t2 < ray.tMax) {
		return true;
	}


	return false;
}
