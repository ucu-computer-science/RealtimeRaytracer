// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#ifndef RAYTRACER_GRAPHICALOBJECT_H
#define RAYTRACER_GRAPHICALOBJECT_H

#include <memory>
#include <vector>
#include "Ray.h"

class GraphicalObject {

public:
    [[nodiscard]] virtual bool intersects(Ray& ray) const = 0;
};
typedef std::vector<std::unique_ptr<GraphicalObject>> graphicalObjectVector;

#endif //RAYTRACER_GRAPHICALOBJECT_H
