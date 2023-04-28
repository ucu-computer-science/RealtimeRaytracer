#pragma once

#include "Color.h"
#include "Texture.h"

struct Material
{
	Color color;
	std::shared_ptr<Texture> texture{new Texture()};
	bool lit = true;
	float diffuseCoeff = 1;
	float specularCoeff = 0;
	int specularDegree = 0;
	float reflection = 0;


	Material(): color(Color::white()) { }
	Material(Color color) : color(color) {}
	Material(Color color,
	         std::shared_ptr<Texture>& texture,
	         bool lit,
	         float diffuseCoeff,
	         float specularCoeff,
	         int specularDegree,
	         float reflection) : color{color},
	                             texture{texture},
	                             lit{lit},
	                             diffuseCoeff{diffuseCoeff},
	                             specularCoeff{specularCoeff},
	                             specularDegree{specularDegree},
	                             reflection{reflection} { }

	Color getColor(float u, float v) const
	{
		return texture->getColor(u, v) * color;
	}
};
