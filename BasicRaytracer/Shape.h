#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Math.h"
#include "Ray.h"
#include "Color.h"


class Shape {
public:
	virtual ~Shape() {};

	virtual bool intersect(Intersection& intersection) = 0;
	virtual bool doesIntersect(const Ray& ray) = 0;

	virtual Vector getNormal(Vector p) const = 0;

};

class ShapeSet : public Shape {
protected:
	std::vector<Shape*> shapes;
public:
	ShapeSet(); 

	virtual ~ShapeSet();

	void addShape(Shape* shape);

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);
	virtual Vector getNormal(Vector p) const { return Vector(); }
	
};


class Plane : public Shape {
protected:
	Point position;
	Vector normal;
	Color color;

public:
	Plane(const Point& position, const Vector& normal);
	Plane(const Point& position, const Vector& normal,const Color& color);
	virtual ~Plane();

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);

	virtual Vector getNormal(Vector p) const;
};

class Sphere : public Shape {
protected:
	Point center;
	float radius;
	Color color;
public:
	Sphere(const Point& center, float radius);
	Sphere(const Point& center, float radius,const Color& color);
	virtual ~Sphere();

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);

	virtual Vector getNormal(Vector p) const;
};

#endif