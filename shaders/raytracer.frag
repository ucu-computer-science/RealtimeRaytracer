#version 460 core
out vec4 outColor;

#define FLT_MAX  1000000000

// ----------- OPTIONS -----------
//#define USE_BVH


// Window
uniform vec2 pixelSize;
uniform vec2 screenSize;


// General
uniform int rayBounceCount;
uniform bool showBoundingBoxes = true;

// Camera
uniform float focalDistance;
uniform vec3 cameraPos;
uniform mat4x4 cameraRotMat = mat4x4(1.0);
uniform vec4 bgColor = vec4(0.3, 0, 0, 1);


// Light
uniform int lightCount;
struct Light {
    float lightType; // 0 - GlobalLight, 1 - PointLight, 2 - AreaLight(not implemented)
    vec4 pos;
    vec4 color;
    vec4 properties1; // intensity, [PointLight(distance) : GlobalLight(dirX, dirY, dirZ) : AreaLight(size)]
    vec4 properties2; // [AreaLight(distance, pointSize)]
};

// Object
uniform int objectCount;
struct Object {
    float objType; 
    vec4 pos;
    vec4 color;
    vec4 lit;
    vec4 properties1; // diffuse coef, specular coef, specular degree, reflection
    vec4 properties2; // Sphere(radiusSquared)]
};

// Triangle
struct Vertex {
    vec4 posU;
    vec4 normalV;
};

uniform int triangleCount;
struct Triangle {
    Vertex vertices[3];
    float objInd;
    vec4 rows[3];
};

//const int LEAF_ARR_SIZE = 8;
uniform int bvhNodeCount;
struct BVHNode {
    vec4 min; // w = trianglesStart
    vec4 max; // w = triangleCount
    vec4 values; // hitNext, missNext, isLeaf
};



// UNIFORM BUFFERS
layout(std140, binding = 0) uniform Lights {
    Light lights[100];
};

layout(std140, binding = 1) uniform Objects {
    Object objects[100];
};

layout(std140, binding = 2) uniform Triangles {
    Triangle triangles[];
};

layout(std140, binding = 3) uniform BVHNodes {
    BVHNode nodes[];
};



// **************************************************************************
// ------------------------------ INTERSECTION ------------------------------
// **************************************************************************

struct Ray
{
    vec3 pos, dir;
    float closestT;
    Object closestObj;
    vec3 surfaceNormal;
    vec3 interPoint;
    float maxDis;
};

#define RAY_DEFAULT_ARGS FLT_MAX, Object(0, vec4(0), vec4(0), vec4(0), vec4(0), vec4(0)), vec3(0), vec3(0), 10000
#define RAY_DEFAULT_ARGS_WO_DIST Object(0, vec4(0), vec4(0), vec4(0), vec4(0), vec4(0)), vec3(0), vec3(0), 10000


vec3 getTriangleNormalAt(Triangle triangle, float u, float v, bool invert)
{
	vec3 interpolatedNormal = normalize((1 - u - v) * triangle.vertices[0].normalV.xyz + u * triangle.vertices[1].normalV.xyz + v * triangle.vertices[2].normalV.xyz);
	return invert ? -interpolatedNormal : interpolatedNormal;
}

bool IntersectTriangle(out Ray ray, Triangle triangle)
{
    float dz = dot(triangle.rows[2].xyz, ray.dir);
	if (dz == 0.0) return false;

	float oz = dot(triangle.rows[2].xyz, ray.pos) + triangle.rows[2].w;
	float t = -oz / dz;
	if (t < 0.0 || ray.closestT < t || t >= ray.maxDis) return false;

	vec3 hitPos = ray.pos + ray.dir * t;
	float u = dot(triangle.rows[0].xyz, hitPos) + triangle.rows[0].w;
	if (u < 0.0 || u > 1.0) return false;

	float v = dot(triangle.rows[1].xyz, hitPos) + triangle.rows[1].w;
	if (v < 0.0 || u + v > 1.0) return false;

	ray.closestT = t;
	ray.closestObj = objects[int(triangle.objInd)];
	ray.surfaceNormal = getTriangleNormalAt(triangle, u, v, false);
	ray.interPoint = hitPos;

	return true;
}

bool intersectTriangledObject(out Ray ray, Object obj)
{
    bool hit = false;
    for(int j = int(obj.properties2.x); j < obj.properties2.y; j++)
    {
        if(IntersectTriangle(ray, triangles[j]))
        {
            hit = true;
            ray.closestObj = obj;
        }      
    }
    return hit;
}

bool solveQuadratic(float a, float b, float c, out float x0, out float x1)
{
    float discr = b * b - 4 * a * c;
    if (discr < 0)
		return false;
	if (discr == 0)
		x0 = x1 = -0.5f * b / a;
	else
	{
		float q = (b > 0) ? -0.5f * (b + sqrt(discr)) : -0.5f * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1)
    {
        float temp = x0;
        x0 = x1;
        x1 = temp;
    }
    return true;
}

bool intersectSphere(out Ray ray, Object sphere)
{
    float x0, x1;
	vec3 inter = (ray.pos - sphere.pos.xyz);
	float a = dot(ray.dir, ray.dir);
	float b = dot(ray.dir + ray.dir, inter);
	float c = abs(dot(inter, inter)) - sphere.properties2.x;

    if(!solveQuadratic(a, b, c, x0, x1)) return false;
	if (!(x0 > 0 && x0 < ray.closestT && x0 < ray.maxDis)) return false;

	ray.closestT = x0;
	ray.interPoint = ray.pos + x0 * ray.dir;
	ray.surfaceNormal = normalize(ray.interPoint - sphere.pos.xyz);
	ray.closestObj = sphere;

//	vec3 n = ray.surfaceNormal;
//	float u = atan(-n.x, n.y) / (2.0 * 3.141597) + 0.5;
//	float v = -n.z * 0.5 + 0.5;

	return true;
}

bool intersectPlane(out Ray ray, Object plane)
{
    vec3 normal = plane.properties2.xyz;
    float denom = -dot(normal, ray.dir);
	if (denom <= 1e-6f)
        return false;

	vec3 dir = plane.pos.xyz - ray.pos;
	float t = -dot(normal, dir) / denom;
	if (!(t < ray.closestT && t > 0 && t < ray.maxDis))
        return false;

	ray.closestT = t;
	ray.interPoint = ray.pos + t * ray.dir;
	ray.surfaceNormal = normal;
	ray.closestObj = plane;

	return true;
}

bool intersectObj(out Ray ray, Object obj)
{
    if(obj.objType == 0)
    {
        if(intersectTriangledObject(ray, obj))
            return true;
    }
    else if(obj.objType == 1)
    {
        if(intersectSphere(ray, obj))
            return true;
    }
    else if(obj.objType == 2)
    {
        if(intersectPlane(ray, obj))
            return true;
    }
    return false;
}

bool intersectsAABB(Ray ray, vec4 min_, vec4 max_, float tMin, float tMax)
{
	for (int i = 0; i < 3; i++)
	{
		float invD = 1.0f / ray.dir[i];
		float t0 = (min_[i] - ray.pos[i]) * invD;
		float t1 = (max_[i] - ray.pos[i]) * invD;
		if (invD < 0.0f)
		{
            float temp = t0;
            t0 = t1;
            t1 = temp;
        }

		tMin = max(t0, tMin);
		tMax = min(t1, tMax);
		if (tMax <= tMin)
			return false;
	}
	return true;
}

const float lineWidth = 0.05f;
bool intersectAABBForVisual(out Ray ray, vec4 min_, vec4 max_)
{
	float tMin = 0, tMax = FLT_MAX;
	for (int i = 0; i < 3; i++)
	{
		float invD = 1.0f / ray.dir[i];
		float t0 = (min_[i] - ray.pos[i]) * invD;
		float t1 = (max_[i] - ray.pos[i]) * invD;
		if (invD < 0.0f)
		{
            float temp = t0;
            t0 = t1;
            t1 = temp;
        }

		tMin = max(t0, tMin);
		tMax = min(t1, tMax);
		if (tMax <= tMin)
			return false;
	}

    vec2 ts = vec2(tMin, tMax);
	for (int i = 0; i < 2; i++)
	{
        float t = ts[i];
		vec3 point = ray.pos + t * ray.dir;
		if (ray.closestT > t && ((abs(min_.x - point.x) <= lineWidth || abs(max_.x - point.x) <= lineWidth ||
				abs(min_.y - point.y) <= lineWidth || abs(max_.y - point.y) <= lineWidth) &&
			(abs(min_.y - point.y) <= lineWidth || abs(max_.y - point.y) <= lineWidth ||
				abs(min_.z - point.z) <= lineWidth || abs(max_.z - point.z) <= lineWidth) &&
			(abs(min_.z - point.z) <= lineWidth || abs(max_.z - point.z) <= lineWidth ||
				abs(min_.x - point.x) <= lineWidth || abs(max_.x - point.x) <= lineWidth)))
		{
			ray.surfaceNormal = vec3(0, 0, 1);
			ray.interPoint = point;
			ray.closestT = t;
			ray.closestObj = objects[0];
			return true;
		}
	}

	return false;
}

bool intersectBVHTree(out Ray ray)
{
    int curr = 0;
    while(curr != -1)
    {
        BVHNode node = nodes[curr];
        if(intersectsAABB(ray, node.min, node.max, 0, FLT_MAX))
        {
            if(node.values.z == 1)
            {
                for (int i = int(node.min.w); i < node.min.w + node.max.w; i++)
			        IntersectTriangle(ray, triangles[i]);
            }
            curr = int(node.values.x);
        }
        else
            curr = int(node.values.y);
    }
    return ray.surfaceNormal != vec3(0);
}


// *************************************************************************
// --------------------------------- LIGHT ---------------------------------
// *************************************************************************
bool castShadowRays(Ray ray)
{
#ifdef USE_BVH
    for(int objInd = 0; objInd < objectCount; objInd++)
    {
        if(objects[objInd].objType!= 0 && intersectObj(ray, objects[objInd]))
            return true;
    }
    return intersectBVHTree(ray);
#else
    for(int objInd = 0; objInd < objectCount; objInd++)
    {
        if(intersectObj(ray, objects[objInd]))
            return true;
    }
    return false;
#endif
}



void getGlobalLightIllumination(Ray ray, Light globalLight, out vec4 diffuse, out vec4 specular)
{
    if (castShadowRays(Ray(globalLight.pos.xyz, - globalLight.properties1.yzw, RAY_DEFAULT_ARGS)))
	    return;

    float light = max(dot(globalLight.properties1.yzw, ray.surfaceNormal), 0.0f);
    diffuse += light * globalLight.color * globalLight.properties1.x;

    vec3 h = normalize(globalLight.properties1.yzw - ray.dir);
    specular += pow(max(dot(h, ray.surfaceNormal), 0.0f), ray.closestObj.properties1.z) * globalLight.color * globalLight.properties1.x;    
}

void getPointLightIllumination(Ray ray, Light pointLight, out vec4 diffuse, out vec4 specular)
{
    vec3 dir = pointLight.pos.xyz - ray.interPoint;
	float dist = length(dir);
	if (dist > pointLight.properties1.y)
		return;

	dir = normalize(dir);
	if (castShadowRays(Ray(pointLight.pos.xyz, -dir, dist, RAY_DEFAULT_ARGS_WO_DIST)))
		return;

	float distanceImpact = min(1 - (dist / pointLight.properties1.y), 1.f);
	float lightFacingAtPoint = max(dot(dir, ray.surfaceNormal), 0.0f);
	diffuse += (distanceImpact * lightFacingAtPoint) * pointLight.color * pointLight.properties1.x;

	vec3 h = normalize(dir - ray.dir);
	specular += distanceImpact * pow(max(dot(h, ray.surfaceNormal), 0.0f), ray.closestObj.properties1.z) * pointLight.color * pointLight.properties1.x;
}

void getAreaLightIllumination(Ray ray, Light areaLight, out vec4 diffuse, out vec4 specular)
{
    vec3 size =  areaLight.properties1.yzw;
    vec3 pointSize = areaLight.properties2.yzw;
    float intensity = areaLight.properties1.x / (pointSize.x * pointSize.y * pointSize.z);
    float dx = size.x / pointSize.x;
	float dy = size.y / pointSize.y;
	float dz = size.z / pointSize.z;
	for (int x = 0; x < pointSize.x; ++x)
	{
		for (int y = 0; y < pointSize.y; ++y)
		{
			for (int z = 0; z < pointSize.z; ++z)
			{
				vec3 lightPoint = areaLight.pos.xyz - size / 2.0 + vec3(x * dx, y * dy, z * dz);

                float dist = length(lightPoint - ray.interPoint);
		        if (dist > areaLight.properties2.x)
			        continue;

		        vec3 dir = normalize(lightPoint - ray.interPoint);
		        if (castShadowRays(Ray(areaLight.pos.xyz/*lightPoint*/, -dir, dist, RAY_DEFAULT_ARGS_WO_DIST)))
			        continue;

		        float distanceImpact = max(1 - (dist / areaLight.properties2.x), 0.f);
		        float lightFacingAtPoint = max(dot(dir, ray.surfaceNormal), 0.f);
		        diffuse += distanceImpact * lightFacingAtPoint * areaLight.color * intensity;

		        vec3 h = normalize(dir - ray.dir);
		        specular += distanceImpact * pow(max(dot(h, ray.surfaceNormal), 0.0f), ray.closestObj.properties1.z)* areaLight.color * intensity;
			}
		}
	}
}

void getIlluminationAtPoint(Ray ray, out vec4 diffuse, vec4 specular)
{
    diffuse = vec4(0);
    specular = vec4(0);
	for (int i = 0; i < lightCount; i++)
	{
		if(lights[i].lightType == 0)
        {
        	getGlobalLightIllumination(ray, lights[i], diffuse, specular);
        }
        else if(lights[i].lightType == 1)
        {
            getPointLightIllumination(ray, lights[i], diffuse, specular);
        }
        else if(lights[i].lightType == 2)
        {
            getAreaLightIllumination(ray, lights[i], diffuse, specular);
        }
	}
}



// **************************************************************************
// ---------------------------------- MAIN ----------------------------------
// **************************************************************************

vec4 castRay(Ray ray)
{
    vec4 color = vec4(0);
    bool hit = false;
    float colorImpact = 1;
    for(int bounce = 0; bounce < rayBounceCount; bounce++) 
    {
        #ifdef USE_BVH
        for(int objInd = 0; objInd < objectCount; objInd++)
        {
            if(objects[objInd].objType == 0) continue;
            intersectObj(ray, objects[objInd]);
        }
        intersectBVHTree(ray);
        #else
        for(int objInd = 0; objInd < objectCount; objInd++)
        {
            intersectObj(ray, objects[objInd]);
        }
        #endif

        if(ray.surfaceNormal == vec3(0)) // no hit
            break;

        hit = true;
        ray.interPoint += ray.surfaceNormal * 0.01f;

		if (ray.closestObj.lit.x == 1)
		{
            vec4 diffuse, specular;
			getIlluminationAtPoint(ray, diffuse, specular);
			color += colorImpact * (1 - ray.closestObj.properties1.w) * ray.closestObj.color * diffuse * ray.closestObj.properties1.x;
			color += specular * ray.closestObj.properties1.y;
		}
		else
			color += colorImpact * (1 - ray.closestObj.properties1.w) * ray.closestObj.color;

		colorImpact *= ray.closestObj.properties1.w;
		if (colorImpact <= 1e-6f)
			break;
            
		vec3 dir = ray.dir - 2 * dot(ray.dir, ray.surfaceNormal) * ray.surfaceNormal;
		ray = Ray(ray.interPoint, dir, RAY_DEFAULT_ARGS);
    }
    
    color += colorImpact * bgColor;
    return hit ? color : bgColor;
}

void main()
{
    float x = gl_FragCoord.x / pixelSize.x * screenSize.x;
    float y = gl_FragCoord.y / pixelSize.y * screenSize.y;
    vec4 right = cameraRotMat[0];
    vec4 forward = cameraRotMat[1];
    vec4 up = cameraRotMat[2];
    vec4 lb = focalDistance * forward - 0.5 * right * screenSize.x - 0.5 * up;
    vec4 rayDir = normalize(lb + x * right + y * up);
    Ray ray = Ray(cameraPos, rayDir.xyz, RAY_DEFAULT_ARGS);

    outColor = castRay(ray);
}