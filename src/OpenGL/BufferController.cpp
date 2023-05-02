#include "BufferController.h"

#include "BoundingBoxes.h"
#include "GraphicalObject.h"
#include "Raytracer.h"
#include "Scene.h"
#include "Triangle.h"


void BufferController::initializeUniformBuffers()
{
	initializeLightsBuffer();
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
void BufferController::initializeObjectsBuffer()
{
	auto ALIGN = RaytracerShader::objectAlign;
	const auto& objects = Scene::graphicalObjects;
	auto triangleCount = 0;
	std::vector<float> data(objects.size() * ALIGN);
	for (int i = 0; i < objects.size(); ++i)
	{
		data[i * ALIGN + 4] = objects[i]->getPos().x;
		data[i * ALIGN + 5] = objects[i]->getPos().y;
		data[i * ALIGN + 6] = objects[i]->getPos().z;

		const auto& mat = objects[i]->material;
		data[i * ALIGN + 8] = mat.color.r();
		data[i * ALIGN + 9] = mat.color.g();
		data[i * ALIGN + 10] = mat.color.b();
		data[i * ALIGN + 12] = mat.lit;
		data[i * ALIGN + 16] = mat.diffuseCoeff;
		data[i * ALIGN + 17] = mat.specularCoeff;
		data[i * ALIGN + 18] = mat.specularDegree;
		data[i * ALIGN + 19] = mat.reflection;

		if (dynamic_cast<Mesh*>(objects[i]) != nullptr)
		{
			auto mesh = (Mesh*)objects[i];
			data[i * ALIGN + 0] = 0;
			data[i * ALIGN + 20] = triangleCount;
			data[i * ALIGN + 21] = triangleCount + mesh->triangles.size();
			triangleCount += mesh->triangles.size();
		}
		else if (dynamic_cast<Sphere*>(objects[i]) != nullptr)
		{
			auto sphere = (Sphere*)objects[i];
			data[i * ALIGN + 0] = 1;
			data[i * ALIGN + 20] = sphere->radius * sphere->radius;
		}
		else if (dynamic_cast<Plane*>(objects[i]) != nullptr)
		{
			auto plane = (Plane*)objects[i];
			data[i * ALIGN + 0] = 2;
			data[i * ALIGN + 20] = plane->normal.x;
			data[i * ALIGN + 21] = plane->normal.y;
			data[i * ALIGN + 22] = plane->normal.z;
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
		data[i * ALIGN + 24] = triangle->mesh->indexID;

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
