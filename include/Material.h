#pragma once

#include "Color.h"

struct Material
{
	Color color;
	float alpha = 1; // not implemented
	bool lit = true;
	float diffuseCoeff = 1;
	float specularCoeff = 0;
	int specularDegree = 0;
	float reflection = 0;

	Material(): color(Color::white()) {}
	Material(Color color) : color(color) {}
    Material(Color color,
             float alpha,
             float diffuseCoeff,
             float specularCoeff,
             int specularDegree,
             float reflection) :

            color{color},
            alpha{alpha},
            diffuseCoeff{diffuseCoeff},
            specularCoeff{specularCoeff},
            specularDegree{specularDegree},
            reflection{reflection} {}
};