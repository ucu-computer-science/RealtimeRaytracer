//
// Created by ADMIN on 26-Apr-23.
//

#ifndef RAYTRACER_POLYMESH_H
#define RAYTRACER_POLYMESH_H


#include "GraphicalObject.h"
#include "ExtendedVertice.h"


class PolyMesh final: public GraphicalObject {
    std::vector<ExtendedVertice> vertices;

public:
    PolyMesh(): GraphicalObject(){};
    std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);
};


#endif //RAYTRACER_POLYMESH_H