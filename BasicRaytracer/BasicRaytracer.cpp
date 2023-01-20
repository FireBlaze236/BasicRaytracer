// BasicRaytracer.cpp : Defines the entry point for the application.
//



#include "BasicRaytracer.h"

#include <cmath>

#include "Camera.h"
#include "Shape.h"
#include "Image.h"



#define PI 3.1416

using namespace std;

Point lightPoint = Point(-3.0f, 10.0f, -4.0f);

void rayTrace(Image& image, Camera* camera, Shape* scene)
{
	for (int x = 0; x < image.getWidth(); x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			Vector2 screenCoord((2.0f * x) / image.getWidth() - 1.0f,
				(-2.0f * y) / image.getHeight() + 1.0f);

			Ray ray = camera->makeRay(screenCoord);

			Color* curPixel = image.getPixel(x, y);

			Intersection intersection(ray);


			if (scene->intersect(intersection)) {
				Color diffuse = intersection.color;
				Point phit = intersection.position();
				Vector dir = (lightPoint - phit).normalized();
				Ray shadowRay = Ray(phit, dir);
				float d = Dot(dir, intersection.pShape->getNormal(phit));
				d = max(0.2f, d);
				*curPixel = diffuse * d;

				//Shadow
				if (scene->doesIntersect(shadowRay))
				{
					*curPixel *= 0.2f;
				}
			}
			else {
				*curPixel = Color(0.0f);
			}
		}
	}
}



int main()
{
	int width = 1920;
	int height = 1080;

	Image image(width, height);
	float aspect = (float)width / (float)height;
	PerspectiveCamera camera(Point(-5.0f, 1.0f, 0.0f),
		Vector(0.0f, 1.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), 25.0f * PI / 180.0f,
		aspect);

	ShapeSet scene;
	
	Plane floor(Point(0.0f, 0.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f), Color(1.0f));
	scene.addShape(&floor);

	Sphere sphere(Point(0.0f, 1.0f, 0.0f), 1.0f, Color(0.2f, 0.8f, 0.3f));
	scene.addShape(&sphere);

	Sphere sphere2(Point(-0.4f, 2.0f, -1.2f), 0.3f, Color(0.8f, 0.2f, 0.3f));
	scene.addShape(&sphere2);

	rayTrace(image, &camera, &scene);

	image.saveImage("out.bmp", 1.0f, 2.2f);
}
;
