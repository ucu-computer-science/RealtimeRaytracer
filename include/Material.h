#pragma once

#include "Color.h"

struct Material
{
	Color color;
	float alpha;
	float diffuseCoeff;
	float specularCoeff;
	int specularDegree;
	float reflection;

	Material(Color color,
	         float transparency,
	         float diffuseCoeff,
	         float specularCoeff,
	         int specularDegree,
	         float reflection) : color{color},
	                             alpha(transparency),
	                             diffuseCoeff{diffuseCoeff},
	                             specularCoeff{specularCoeff},
	                             specularDegree{specularDegree},
	                             reflection{reflection} {}
	Material(): color(Color::white()),
	            alpha(1),
	            diffuseCoeff{1},
	            specularCoeff{0},
	            specularDegree{0},
	            reflection{0} {}
};
