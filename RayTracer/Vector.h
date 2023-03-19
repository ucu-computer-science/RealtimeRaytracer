#pragma once
#ifndef RAY_TRACING_VECTOR_H
#define RAY_TRACING_VECTOR_H
class Vector
{
	const float x, y, z;
public:
	Vector(float x, float y, float z): 
	x{x}, y{y}, z{z}{};
	~Vector() = default;

    [[nodiscard]] float getX() const {
        return x;
    }
    [[nodiscard]] float getY() const {
        return y;
    }
    [[nodiscard]] float getZ() const {
        return z;
    }
//    void setX(float n_x){
//        x = n_x;
//    }
//    void setY(float n_y){
//        y = n_y;
//    }
//    void setZ(float n_z){
//        z = n_z;
//    }

	[[nodiscard]] Vector xPr(const Vector& v) const;
    [[nodiscard]] Vector operator+ (const Vector& v) const {
        return {x + v.x, y + v.y, z + v.z};
    }
    [[nodiscard]] Vector operator- (const Vector& v) const {
		return {x - v.x, y - v.y, z - v.z};
	}
    [[nodiscard]] Vector operator- () const {
		return {-x, -y, -z};
	};

    [[nodiscard]] float operator*(const Vector& v ) const {
        return x*v.x + y*v.y + z*v.z;
    };


    //friend float Vector operator* (Vector& v) {};

};
[[nodiscard]] Vector operator*(float n, const Vector& v );
[[nodiscard]] Vector operator*(const Vector& v , float n);

#endif // RAY_TRACING_VECTOR_H
