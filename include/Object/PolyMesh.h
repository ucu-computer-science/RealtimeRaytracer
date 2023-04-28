#pragma once

#include "GraphicalObject.h"
#include "Vertex.h"


class PolyMesh final: public GraphicalObject {
    std::vector<Vertex> vertices;

public:
    PolyMesh(): GraphicalObject(){};
    static std::vector<std::shared_ptr<Triangle>> generateTriangles(float side);
};

