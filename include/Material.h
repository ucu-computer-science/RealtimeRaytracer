#pragma once
#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "Color.h"

struct Material {
    Color color;
    float diffuse_coeff;
    float specular_coeff;
    int specular_degree;
    float reflection;

    Material(Color color,
             float diffuse_coeff,
             float specular_coeff,
             int specular_degree,
             float reflection) :

            color{color},
            diffuse_coeff{diffuse_coeff},
            specular_coeff{specular_coeff},
            specular_degree{specular_degree},
            reflection{reflection} {}
    Material(): color{},
                diffuse_coeff{1},
                specular_coeff{0},
                specular_degree{0},
                reflection{0}{};

};


#endif //RAYTRACER_MATERIAL_H