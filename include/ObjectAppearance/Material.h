#pragma once

#include "Color.h"
#include "Texture.h"


class Material
{
public:
	int indexID;

	bool lit;
	Color color;
	std::shared_ptr<Texture> texture;

	float diffuseCoeff = 1;
	float specularCoeff = 0;
	float specularDegree = 0;
	float reflection = 0;


	Material(Color color = Color::white(), bool lit = true);
	Material(Color color,
	         bool lit,
	         std::shared_ptr<Texture> texture,
	         float diffuseCoeff,
	         float specularCoeff,
	         float specularDegree,
	         float reflection);

	Color getColor(float u, float v) const
	{
		return texture->getColor(u, v) * color;
	}


	static Material* const defaultLit;
	static Material* const defaultUnlit;
};
