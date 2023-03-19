#include "Vector.h"

Vector Vector::xPr(const Vector& v) const {
	return {y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x};
}
Vector operator*(float n, const Vector& v ) {
    return {n * v.getX(), n * v.getY(), n * v.getZ()};
}
Vector operator*(const Vector& v , float n) {
    return {n * v.getX(), n * v.getY(), n * v.getZ()};
}