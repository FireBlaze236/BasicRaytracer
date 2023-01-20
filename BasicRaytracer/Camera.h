#ifndef CAMERA_H
#define CAMERA_H

#include "Math.h"
#include "Ray.h"

class Camera {
public:
	virtual ~Camera() { }

	virtual Ray makeRay(Vector2 point) const = 0;

};


class PerspectiveCamera : public Camera {
protected:
	Point origin;
	Vector forward, up, right;
	float h, w;

public:
	PerspectiveCamera(Point origin, Vector target, Vector upguide, float fov, float aspect);

	virtual Ray makeRay(Vector2 point) const;
};
#endif
