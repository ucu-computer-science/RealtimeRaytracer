#include "Material.h"

#include "Scene.h"


Material* const Material::debugLine = new Material(Color::blue(), false);
Material* const Material::defaultLit = new Material(Color::white(), true);
Material* const Material::defaultUnlit = new Material(Color::white(), false);

Material::Material(Color color, bool lit): lit(lit), color(color), texture(std::make_shared<Texture>())
{
	this->indexID = Scene::materials.size();
	Scene::materials.push_back(this);
}

Material::Material(Color color, bool lit, std::shared_ptr<Texture> texture, float diffuseCoeff, float specularCoeff, float specularDegree,
                   float reflection): lit{lit}, color{color}, texture{std::move(texture)}, diffuseCoeff{diffuseCoeff}, specularCoeff{specularCoeff},
                                      specularDegree{specularDegree}, reflection{reflection}
{
	this->indexID = Scene::materials.size();
	Scene::materials.push_back(this);
}
