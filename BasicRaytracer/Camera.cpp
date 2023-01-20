#include "Camera.h"

#include <cmath>

PerspectiveCamera::PerspectiveCamera(Point origin, Vector target, Vector upguide, float fov, float aspect)
	: origin(origin)
{
	forward = (target - origin).normalized();
	right = cross(forward, upguide).normalized();
	up = cross(right, forward);

	h = tan(fov);
	w = h * aspect;
}

Ray PerspectiveCamera::makeRay(Vector2 point) const
{
	Vector direction = forward + point.u * w * right
		+ point.v * h * up;

	return Ray(origin, direction.normalized());
}


