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
	Material(Color color) : color(color) { }
};
