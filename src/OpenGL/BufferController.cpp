#include "BufferController.h"

#include "BoundingBoxes.h"
#include "GraphicalObject.h"
#include "Raytracer.h"
#include "Scene.h"
#include "Triangle.h"


void BufferController::initializeUniformBuffers()
{
	initializeLightsBuffer();
	initializeMaterialsBuffer();
	initializeObjectsBuffer();
	initializeTrianglesBuffer();
	initializeBVHBuffer();
}

void BufferController::initializeLightsBuffer()
{
	const auto& lights = Scene::lights;
	auto ALIGN = RaytracerShader::lightAlign;
	std::vector<float> data(lights.size() * ALIGN);
	for (int i = 0; i < lights.size(); ++i)
	{
		data[i * ALIGN + 4] = lights[i]->getPos().x;
		data[i * ALIGN + 5] = lights[i]->getPos().y;
		data[i * ALIGN + 6] = lights[i]->getPos().z;
		data[i * ALIGN + 8] = lights[i]->getColor().r();
		data[i * ALIGN + 9] = lights[i]->getColor().g();
		data[i * ALIGN + 10] = lights[i]->getColor().b();
		data[i * ALIGN + 12] = lights[i]->getIntensity();

		if (dynamic_cast<GlobalLight*>(lights[i]) != nullptr)
		{
			auto globalLight = (GlobalLight*)lights[i];
			data[i * ALIGN + 0] = 0;
			data[i * ALIGN + 13] = globalLight->direction.x;
			data[i * ALIGN + 14] = globalLight->direction.y;
			data[i * ALIGN + 15] = globalLight->direction.z;
		}
		else if (dynamic_cast<PointLight*>(lights[i]))
		{
			auto pointLight = (PointLight*)lights[i];
			data[i * ALIGN + 0] = 1;
			data[i * ALIGN + 13] = pointLight->distance;
		}
		else if (dynamic_cast<AreaLight*>(lights[i]))
		{
			auto pointLight = (AreaLight*)lights[i];
			data[i * ALIGN + 0] = 2;
			data[i * ALIGN + 13] = pointLight->size.x;
			data[i * ALIGN + 14] = pointLight->size.y;
			data[i * ALIGN + 15] = pointLight->size.z;
			data[i * ALIGN + 16] = pointLight->distance;
			data[i * ALIGN + 17] = pointLight->pointSize.x;
			data[i * ALIGN + 18] = pointLight->pointSize.y;
			data[i * ALIGN + 19] = pointLight->pointSize.z;
		}
	}

	Raytracer::mainShader->setLightsUBO(data.data(), lights.size());
}
void BufferController::initializeMaterialsBuffer()
{
	auto ALIGN = RaytracerShader::materialAlign;
	const auto& materials = Scene::materials;
	std::vector<float> data(materials.size() * ALIGN);
	for (int i = 0; i < materials.size(); ++i)
	{
		const auto& mat = materials[i];
		data[i * ALIGN + 0] = mat->color.r();
		data[i * ALIGN + 1] = mat->color.g();
		data[i * ALIGN + 2] = mat->color.b();
		data[i * ALIGN + 4] = mat->lit;
		data[i * ALIGN + 5] = mat->diffuseCoeff;
		data[i * ALIGN + 6] = mat->specularCoeff;
		data[i * ALIGN + 7] = mat->specularDegree;
		data[i * ALIGN + 8] = mat->reflection;
	}
	Raytracer::mainShader->setMaterialsUBO(data.data(), materials.size());
}
void BufferController::initializeObjectsBuffer()
{
	auto ALIGN = RaytracerShader::objectAlign;
	const auto& objects = Scene::graphicalObjects;
	auto triangleCount = 0;
	std::vector<float> data(objects.size() * ALIGN);
	for (int i = 0; i < objects.size(); ++i)
	{
		auto obj = objects[i];
		data[i * ALIGN + 1] = obj->material->indexID;
		data[i * ALIGN + 4] = obj->getPos().x;
		data[i * ALIGN + 5] = obj->getPos().y;
		data[i * ALIGN + 6] = obj->getPos().z;

		if (dynamic_cast<Mesh*>(obj) != nullptr)
		{
			auto mesh = (Mesh*)obj;
			data[i * ALIGN + 0] = 0;
			data[i * ALIGN + 8] = triangleCount;
			data[i * ALIGN + 9] = mesh->triangles.size();
			triangleCount += mesh->triangles.size();
		}
		else if (dynamic_cast<Sphere*>(obj) != nullptr)
		{
			auto sphere = (Sphere*)obj;
			data[i * ALIGN + 0] = 1;
			data[i * ALIGN + 8] = sphere->radius * sphere->radius;
		}
		else if (dynamic_cast<Plane*>(obj) != nullptr)
		{
			auto plane = (Plane*)obj;
			data[i * ALIGN + 0] = 2;
			data[i * ALIGN + 8] = plane->normal.x;
			data[i * ALIGN + 9] = plane->normal.y;
			data[i * ALIGN + 10] = plane->normal.z;
		}
	}
	Raytracer::mainShader->setObjectsUBO(data.data(), objects.size());
}
void BufferController::initializeTrianglesBuffer()
{
	auto ALIGN = RaytracerShader::triangleAlign;
	const auto& triangles = Scene::triangles;
	std::vector<float> data(triangles.size() * ALIGN);
	for (int i = 0; i < triangles.size(); i++)
	{
		const auto& triangle = triangles[i];
		for (int k = 0; k < 3; ++k)
		{
			auto globalPos = triangle->globalVertexPositions[k];
			data[i * ALIGN + k * 8 + 0] = globalPos.x;
			data[i * ALIGN + k * 8 + 1] = globalPos.y;
			data[i * ALIGN + k * 8 + 2] = globalPos.z;

			const auto& v = triangle->vertices[k];
			data[i * ALIGN + k * 8 + 3] = v.uvPos.x;
			data[i * ALIGN + k * 8 + 7] = v.uvPos.y;

			auto normal = triangle->globalVertexNormals[k];
			data[i * ALIGN + k * 8 + 4] = normal.x;
			data[i * ALIGN + k * 8 + 5] = normal.y;
			data[i * ALIGN + k * 8 + 6] = normal.z;
		}
		data[i * ALIGN + 24] = triangle->mesh->material->indexID;
		data[i * ALIGN + 25] = triangle->globalNormal.x;
		data[i * ALIGN + 26] = triangle->globalNormal.y;
		data[i * ALIGN + 27] = triangle->globalNormal.z;

		data[i * ALIGN + 28] = triangle->row1.x;
		data[i * ALIGN + 29] = triangle->row1.y;
		data[i * ALIGN + 30] = triangle->row1.z;
		data[i * ALIGN + 31] = triangle->row1Val;
		data[i * ALIGN + 32] = triangle->row2.x;
		data[i * ALIGN + 33] = triangle->row2.y;
		data[i * ALIGN + 34] = triangle->row2.z;
		data[i * ALIGN + 35] = triangle->row2Val;
		data[i * ALIGN + 36] = triangle->row3.x;
		data[i * ALIGN + 37] = triangle->row3.y;
		data[i * ALIGN + 38] = triangle->row3.z;
		data[i * ALIGN + 39] = triangle->row3Val;
	}
	Raytracer::mainShader->setTrianglesUBO(data.data(), triangles.size());
}
void BufferController::initializeBVHBuffer()
{
	auto ALIGN = RaytracerShader::bvhNodeAlign;
	const auto& nodes = BVHBuilder::nodes;
	std::vector<float> data(nodes.size() * ALIGN);
	for (int i = 0; i < nodes.size(); ++i)
	{
		const auto& node = nodes[i];
		const auto& box = node->box;
		data[i * ALIGN + 0] = box.min.x;
		data[i * ALIGN + 1] = box.min.y;
		data[i * ALIGN + 2] = box.min.z;
		data[i * ALIGN + 4] = box.max.x;
		data[i * ALIGN + 5] = box.max.y;
		data[i * ALIGN + 6] = box.max.z;

		data[i * ALIGN + 8] = node->hitNext;
		data[i * ALIGN + 9] = node->missNext;
		data[i * ALIGN + 10] = node->isLeaf;
		data[i * ALIGN + 3] = node->leafTrianglesStart;
		data[i * ALIGN + 7] = node->leafTriangleCount;
	}

	Raytracer::mainShader->setBVHNodesUBO(data.data(), nodes.size());
}
