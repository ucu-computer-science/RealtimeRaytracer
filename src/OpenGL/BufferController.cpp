#include "BufferController.h"

#include "BoundingBoxes.h"
#include "GraphicalObject.h"
#include "Light.h"
#include "Raytracer.h"
#include "Scene.h"
#include "Triangle.h"


void BufferController::initializeUniformBuffers()
{
	initializeTexturesBuffer();
	initializeMaterialsBuffer();
	initializeLightsBuffer();
	initializeObjectsBuffer();
	initializeTrianglesBuffer();
	initializeBVHBuffer();
}

void BufferController::initializeTexturesBuffer()
{
	for (const auto& tex : Scene::textures)
	{
		Raytracer::shader->addTexture2D(tex);
	}
}
void BufferController::initializeMaterialsBuffer()
{
	std::vector<MaterialStruct> data{};
	for (const auto& mat : Scene::materials)
	{
		MaterialStruct materialStruct{};
		materialStruct.color = mat->color;
		materialStruct.properties1 = glm::vec4(mat->lit, mat->diffuseCoeff, mat->specularCoeff, mat->specularDegree);
		materialStruct.properties2.x = mat->reflection;
		materialStruct.properties2.y = mat->texture->indexID;
		data.push_back(materialStruct);
	}
	Raytracer::shader->ssboMaterials->setData((float*)data.data(), data.size());
	Raytracer::shader->setInt("materialCount", data.size());
}
void BufferController::initializeLightsBuffer()
{
	std::vector<LightStruct> data{};
	for (const auto& light : Scene::lights)
	{
		LightStruct lightStruct{};
		lightStruct.pos = glm::vec4(light->getPos(), 0);
		lightStruct.color = light->getColor();
		lightStruct.properties1.x = light->getIntensity();

		if (dynamic_cast<GlobalLight*>(light) != nullptr)
		{
			auto globalLight = (GlobalLight*)light;
			lightStruct.lightType = 0;
			lightStruct.properties1 = glm::vec4(lightStruct.properties1.x, globalLight->direction);
		}
		else if (dynamic_cast<PointLight*>(light))
		{
			auto pointLight = (PointLight*)light;
			lightStruct.lightType = 1;
			lightStruct.properties1.y = pointLight->distance;
		}
		else if (dynamic_cast<AreaLight*>(light))
		{
			auto pointLight = (AreaLight*)light;
			lightStruct.lightType = 2;
			lightStruct.properties1 = glm::vec4(lightStruct.properties1.x, pointLight->size);
			lightStruct.properties2 = glm::vec4(pointLight->distance, pointLight->pointSize);
		}
		data.push_back(lightStruct);
	}
	Raytracer::shader->ssboLights->setData((float*)data.data(), data.size());
	Raytracer::shader->setInt("lightCount", data.size());
}
void BufferController::initializeObjectsBuffer()
{
	auto triangleCount = 0;
	std::vector<ObjectStruct> data{};
	for (const auto& obj : Scene::graphicalObjects)
	{
		ObjectStruct objectStruct{};
		objectStruct.data.y = obj->material->indexID;
		objectStruct.pos = glm::vec4(obj->getPos(), 0);

		if (dynamic_cast<Mesh*>(obj) != nullptr)
		{
			auto mesh = (Mesh*)obj;
			objectStruct.data.x = 0;
			objectStruct.properties.x = triangleCount;
			objectStruct.properties.y = mesh->triangles.size();
			triangleCount += mesh->triangles.size();
		}
		else if (dynamic_cast<Sphere*>(obj) != nullptr)
		{
			auto sphere = (Sphere*)obj;
			objectStruct.data.x = 1;
			objectStruct.properties.x = sphere->radius * sphere->radius;
		}
		else if (dynamic_cast<Plane*>(obj) != nullptr)
		{
			auto plane = (Plane*)obj;
			objectStruct.data.x = 2;
			objectStruct.properties = glm::vec4(plane->normal, 0);
		}
		data.push_back(objectStruct);
	}
	Raytracer::shader->ssboObjects->setData((float*)data.data(), data.size());
	Raytracer::shader->setInt("objectCount", data.size());
}

void BufferController::initializeTrianglesBuffer()
{
	std::vector<TriangleStruct> data{};
	for (const auto& triangle : Scene::triangles)
	{
		TriangleStruct triangleStruct{};
		for (int k = 0; k < 3; ++k)
		{
			triangleStruct.vertices[k].posU = glm::vec4(triangle->globalVertexPositions[k], triangle->vertices[k].uvPos.x);
			triangleStruct.vertices[k].normalV = glm::vec4(triangle->globalVertexNormals[k], triangle->vertices[k].uvPos.y);
		}
		triangleStruct.materialIndex = glm::vec4(triangle->mesh->material->indexID, triangle->globalNormal);

		triangleStruct.rows[0] = glm::vec4(triangle->row1, triangle->row1Val);
		triangleStruct.rows[1] = glm::vec4(triangle->row2, triangle->row2Val);
		triangleStruct.rows[2] = glm::vec4(triangle->row3, triangle->row3Val);
		triangleStruct.texVec = glm::vec4(triangle->texVecU, triangle->texVecV);
		data.push_back(triangleStruct);
	}
	Raytracer::shader->ssboTriangles->setData((float*)data.data(), data.size());
	Raytracer::shader->setInt("triangleCount", data.size());
}
void BufferController::initializeBVHBuffer()
{
	const auto& nodes = BVHBuilder::nodes;
	std::vector<BVHNodeStruct> data{};
	for (const auto& node : nodes)
	{
		BVHNodeStruct bvhNodeStruct{};
		bvhNodeStruct.min = glm::vec4(node->box.min, node->leafTrianglesStart);
		bvhNodeStruct.max = glm::vec4(node->box.max, node->leafTriangleCount);
		bvhNodeStruct.values = glm::vec4(node->hitNext, node->missNext, node->isLeaf, 0);
		data.push_back(bvhNodeStruct);
	}
	Raytracer::shader->ssboBVHNodes->setData((float*)data.data(), data.size());
	Raytracer::shader->setInt("bvhNodeCount", data.size());
}
