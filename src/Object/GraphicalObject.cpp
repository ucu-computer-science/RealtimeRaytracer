#include "GraphicalObject.h"
#include "Raycast.h"
#include "Scene.h"
#include "Triangle.h"


GraphicalObject::GraphicalObject(const glm::vec3 pos) : Object(pos)
{
	Scene::graphicalObjects.emplace_back(this);
}
void GraphicalObject::setColor(Color color) const
{
	for (const auto triangle : triangles)
	{
		triangle->color = color;
	}
}

void GraphicalObject::intersect(Ray& ray)
{
	for (const auto triangle : triangles)
	{
		ray.intersect(triangle);
	}
}


Square::Square(glm::vec3 pos, float side) : GraphicalObject(pos)
{
	glm::vec3 p1 = pos + glm::vec3(-side / 2, 0, -side / 2);
	glm::vec3 p2 = pos + glm::vec3(-side / 2, 0, side / 2);
	glm::vec3 p3 = pos + glm::vec3(side / 2, 0, side / 2);
	glm::vec3 p4 = pos + glm::vec3(side / 2, 0, -side / 2);
	triangles.emplace_back(new Triangle(p1, p3, p2));
	triangles.emplace_back(new Triangle(p1, p3, p4));
}


Cube::Cube(glm::vec3 pos, float side) : GraphicalObject(pos)
{
	glm::vec3 p1 = pos + glm::vec3(-side / 2, -side / 2, -side / 2);
	glm::vec3 p2 = pos + glm::vec3(-side / 2, -side / 2, side / 2);
	glm::vec3 p3 = pos + glm::vec3(side / 2, -side / 2, side / 2);
	glm::vec3 p4 = pos + glm::vec3(side / 2, -side / 2, -side / 2);

	glm::vec3 p5 = pos + glm::vec3(-side / 2, side / 2, -side / 2);
	glm::vec3 p6 = pos + glm::vec3(-side / 2, side / 2, side / 2);
	glm::vec3 p7 = pos + glm::vec3(side / 2, side / 2, side / 2);
	glm::vec3 p8 = pos + glm::vec3(side / 2, side / 2, -side / 2);

	triangles.emplace_back(new Triangle(p1, p3, p2));
	triangles.emplace_back(new Triangle(p1, p3, p4));
	triangles.emplace_back(new Triangle(p5, p7, p6));
	triangles.emplace_back(new Triangle(p5, p7, p8));

	triangles.emplace_back(new Triangle(p1, p6, p2));
	triangles.emplace_back(new Triangle(p1, p6, p5));
	triangles.emplace_back(new Triangle(p4, p7, p3));
	triangles.emplace_back(new Triangle(p4, p7, p8));

	triangles.emplace_back(new Triangle(p2, p7, p3));
	triangles.emplace_back(new Triangle(p2, p7, p6));
	triangles.emplace_back(new Triangle(p1, p8, p4));
	triangles.emplace_back(new Triangle(p1, p8, p5));
}


void Cube::intersect(Ray& ray)
{
	int interCount = 0;
	for (const auto triangle : triangles)
	{
		if (ray.intersect(triangle))
		{
			if (++interCount == 2)
				return;
		}

	}
}
static bool solveQuadratic(float a, float b, float c,
                           float &x0, float &x1)
{
  float discr = b * b - 4 * a * c;
  if (discr < 0) return false;
  else if (discr == 0) x0 = x1 = - 0.5 * b / a;
  else {
    float q = (b > 0) ?
                      -0.5 * (b + sqrt(discr)) :
                      -0.5 * (b - sqrt(discr));
    x0 = q / a;
    x1 = c / q;
  }
  if (x0 > x1) std::swap(x0, x1);
  return true;
}

void Sphere::intersect(Ray &ray) {
  float x0, x1;
  auto inter = (ray.pos - pos) ;
  float a = dot(ray.dir, ray.dir);
  float b = dot(ray.dir + ray.dir, inter);
  float c = fabsf(dot(inter, inter)) - radiusSquared;
  if (solveQuadratic(a,b,c,x0,x1)) {
      if (x0 > 0 && x0 < ray.closestT) {
        ray.closestT = x0;
        ray.color = color;
        ray.interPoint = ray.pos + x0 * ray.dir;
        ray.normal = ray.interPoint - pos;
      }
  }
}
void Plane::intersect(Ray &ray) {
//  if (dot(ray.dir, pos)!=0);
  float denom = dot(normal, ray.dir);
  if (denom > 1e-6) {
    glm::vec3 p0l0 = pos - ray.pos;
    float t = dot(p0l0, normal) / denom;
    if (t < ray.closestT && t >= 0){
      ray.closestT = t;
      ray.color = color;
      ray.interPoint = ray.pos + t*ray.dir;
      ray.normal = normal;
    };
  }

//  return false;
}
//void Box::intersect(Ray &ray) {
//    float tmin, tmax, tymin, tymax, tzmin, tzmax;
//
//    tmin = (bounds[r.sign[0]].x - r.pos.x) * r.invdir.x;
//    tmax = (bounds[1-r.sign[0]].x - r.pos.x) * r.invdir.x;
//    tymin = (bounds[r.sign[1]].y - r.pos.y) * r.invdir.y;
//    tymax = (bounds[1-r.sign[1]].y - r.pos.y) * r.invdir.y;
//
//    if ((tmin > tymax) || (tymin > tmax))
//      return false;
//
//    if (tymin > tmin)
//      tmin = tymin;
//    if (tymax < tmax)
//      tmax = tymax;
//
//    tzmin = (bounds[r.sign[2]].z - r.orig.z) * r.invdir.z;
//    tzmax = (bounds[1-r.sign[2]].z - r.orig.z) * r.invdir.z;
//
//    if ((tmin > tzmax) || (tzmin > tmax))
//      return false;
//
//    if (tzmin > tmin)
//      tmin = tzmin;
//    if (tzmax < tmax)
//      tmax = tzmax;
//
//    return true;
//  }
//}