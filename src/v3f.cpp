#include "v3f.hpp"
#ifndef V3F_CPP
#define V3F_CPP

// Constructors
v3f::v3f() : x{}, y{}, z{}, c1{} {}

v3f::v3f(float x, float y, float z) : x{ x }, y{ y }, z{ z }, c1{} {}

v3f::v3f(float x, float y, float z, c4f c1) : x{ x }, y{ y }, z{ z }, c1{ c1 } {}

v3f::v3f(const v3f& other) : x{ other.x }, y{ other.y }, z{ other.z }, c1{ other.c1 } {}

v3f::v3f(const v3f& other, c4f c1) : x{ other.x }, y{ other.y }, z{ other.z }, c1{ c1 } {}

v3f::v3f(v3f&& other) noexcept : x{ std::move(other.x) }, y{ std::move(other.y) }, z{ std::move(other.z) }, c1{ std::move(other.c1) } {}

// Methods
void v3f::move3D(const v3f& other) {
	x += other.x;
	y += other.y;
	z += other.z;
}

v3f& v3f::normalize() {
	float mag = length();
	if (mag == 0.0f) mag = 1.0f;
	x /= mag;
	y /= mag;
	z /= mag;
	return *this;
}

float v3f::length() const {
	return sqrt(x * x + y * y + z * z);
}

v3f v3f::normalized() const {
	float mag = length();
	if (mag == 0.0f) mag = 1.0f;
	return v3f(x / mag, y / mag, z / mag);
}

// Class Operators
v3f& v3f::operator=(const v3f& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

v3f& v3f::operator=(v3f&& other) noexcept {
	x = std::move(other.x);
	y = std::move(other.y);
	z = std::move(other.z);
	return *this;
}

v3f& v3f::operator+=(const v3f& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

v3f& v3f::operator*=(const v3f& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

v3f& v3f::operator*=(const v3f&& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

v3f& v3f::operator*=(float d) {
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

v3f& v3f::operator/=(float d) {
	x /= d;
	y /= d;
	z /= d;
	return *this;
}

// Operators Overlaod
v3f operator+(const v3f& v1, const v3f& v2) {			// Soma vetores		
	return v3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

v3f operator-(const v3f& v1, const v3f& v2) {			// Subtrai vetores
	return v3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

v3f operator*(const v3f& v, float d) {					// Multiplicação escalar		
	return v3f(v.x * d, v.y * d, v.z * d);
}

v3f operator/(const v3f& v, float d) {					// Divisão escalar		
	return v3f(v.x / d, v.y / d, v.z / d);
}

// Functions
float dot(const v3f& v1, const v3f& v2) {				// Produto escalar
	return v1.x * v2.x + v1.y * v2.y + v1.z * v1.z;
}

v3f cross(const v3f& v1, const v3f& v2) {				// Produto vetorial
	float i = v1.y * v2.z - v1.z * v2.y;
	float j = v1.z * v2.x - v1.x * v2.z;
	float k = v1.x * v2.y - v1.y * v2.x;
	return v3f(i, j, k);
}

float distance(const v3f& v1, const v3f& v2) {			// Magnitude
	return (v1 - v2).length();
}

// Overloads
void glVertex3f(const v3f& v) { glVertex3f(v.x, v.y, v.z); }

void glNormal3f(const v3f& v) { glNormal3f(v.x, v.y, v.z); }

void glTranslatef(const v3f& v) { glTranslatef(v.x, v.y, v.z); }

std::ostream& operator<<(std::ostream& os, const v3f& v) { return os << "{" << v.x << " " << v.y << " " << v.z << "}"; }

std::istream& operator>>(std::istream& is, v3f& v) {
	char ch1;
	is >> ch1;
	if (ch1 != '{') std::cout << "Caracter incorreto: Esperava '{', foi recebido '" << ch1 << "'\n";

	float x, y, z;
	is >> x >> y >> z;

	char ch2;
	is >> ch2;
	if (ch2 != '}') std::cout << "Caracter incorreto: Esperava '}', foi recebido '" << ch2 << "'\n";

	v = { x, y, z };

	return is;
}

#endif
