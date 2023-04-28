#include "PolyMesh.h"
#include "Triangle.h"
#include <memory>

std::vector<std::shared_ptr<Triangle>> PolyMesh::generateTriangles(float side) {
    side = 10;
    auto p1 = glm::vec3(-side / 2, 0, -side / 2);
    auto p2 = glm::vec3(-side / 2, 0, side / 2);
    auto p3 = glm::vec3(side / 2, 0, side / 2);
    auto p4 = glm::vec3(side / 2, 0, -side / 2);

    std::vector<std::shared_ptr<Triangle>> triangles;
//    Triangle(this, {}, {}, {});
//auto t1 = std::make_shared<Triangle>(this, p1, p2, p3));
//    triangles.emplace_back(std::make_shared<Triangle>(this, p1, p2, p3));
//    triangles.emplace_back(std::make_shared<Triangle>(this, p1, p3, p4));
    return triangles;
}