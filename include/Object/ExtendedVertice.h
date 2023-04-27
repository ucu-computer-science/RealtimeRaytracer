//
// Created by ADMIN on 26-Apr-23.
//

#ifndef RAYTRACER_EXTENDEDVERTICE_H
#define RAYTRACER_EXTENDEDVERTICE_H


#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

struct ExtendedVertice{
    glm::vec3 vertice;
    glm::vec2 verticeUV;
    ExtendedVertice(const ExtendedVertice &other){
        vertice = other.vertice;
        verticeUV = other.verticeUV;
    }
    ExtendedVertice(ExtendedVertice &other){
        vertice = other.vertice;
        verticeUV = other.verticeUV;
    }
    ExtendedVertice(glm::vec3 vertice,
                    glm::vec2 verticeUV):
                    vertice(vertice),
                    verticeUV(verticeUV){
    }
    ExtendedVertice():
            vertice(),
            verticeUV(){
    }
    ~ExtendedVertice(){}
};


#endif //RAYTRACER_EXTENDEDVERTICE_H