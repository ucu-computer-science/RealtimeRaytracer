//
// Created by ADMIN on 20-Mar-23.
//

#ifndef RAYTRACER_GRAPHICALOBJECT_H
#define RAYTRACER_GRAPHICALOBJECT_H

#include <memory>
#include <vector>
#include "Ray.h"

class GraphicalObject {

public:
    [[nodiscard]] virtual bool intersects(Ray& ray) const = 0;
//    virtual const GraphicalObject& operator[](int i) = 0;
//    virtual GraphicalObject& operator[](int i) = 0;

//    virtual bool rotateX(float phi);
//    virtual bool rotate(float phi);

};
typedef std::vector<std::unique_ptr<GraphicalObject>> graphicalObjectVector;

#endif //RAYTRACER_GRAPHICALOBJECT_H
