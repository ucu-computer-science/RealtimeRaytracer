#pragma once

#include "Color.h"
#include "Texture.h"

struct Material
{
	bool lit = true;
	Color color;
	std::shared_ptr<Texture> texture;

	float diffuseCoeff = 1;
	float specularCoeff = 0;
	float specularDegree = 0;
	float reflection = 0;


	Material(Color color = Color::white(), bool lit = true) : lit(lit), color(color), texture(std::make_shared<Texture>()) {}
	Material(bool lit,
	         Color color,
	         std::shared_ptr<Texture> texture,
	         float diffuseCoeff,
	         float specularCoeff,
	         float specularDegree,
	         float reflection) : lit{lit},
	                             color{color},
	                             texture{std::move(texture)},
	                             diffuseCoeff{diffuseCoeff},
	                             specularCoeff{specularCoeff},
	                             specularDegree{specularDegree},
	                             reflection{reflection} { }

	Color getColor(float u, float v) const
	{
		return texture->getColor(u, v) * color;
	}
};
