#include "Geometry.h"

#include "jsonUtility.h"
#include "json.hpp"

#include <iostream>

using namespace nlohmann;
using namespace std;

unique_ptr<Geometry> GeometryFactory::create(json& j) {
    string type = j["type"].get<string>();

    if (type == "sphere"){
        return make_unique<Sphere>(j);
    }
    else if (type == "rectangle"){
        return make_unique<Rectangle>(j);
    }    

    throw std::runtime_error("Unknown geometry type: " + type);
}

Geometry::Geometry(json& j){
    ac = parseVector(j, "ac");
    dc = parseVector(j, "dc");
    sc = parseVector(j, "sc");
    ka = j.value("ka", 0.0);
    kd = j.value("kd", 0.0);
    ks = j.value("ks", 0.0);
    pc = j.value("pc", 0.0);
    visible = j.value("visible", true);
    transformMatrix = parseMatrix4f(j, "transform");
}

void Geometry::print(ostream& out) const {
    out << "ac: " << ac.transpose() << endl
        << "dc: " << dc.transpose() << endl
        << "sc: " << sc.transpose() << endl
        << "ka: " << ka << endl
        << "kd: " << kd << endl
        << "ks: " << ks << endl
        << "pc: " << pc << endl;
}

ostream &operator<<(ostream &out, const Geometry &geometry)
{
    geometry.print(out);
	return out; 
}

Geometry::~Geometry(){}
// geometry should have a hit function that takes in a ray, do the intersection algorithm and have it return bool 
// and at what distance

Sphere::Sphere(json& j) : Geometry(j) {
    radius = j.value("radius", 0);
    centre = parseVector(j, "centre");
}

void Sphere::print(ostream& out) const{
    out << "Sphere: " << endl
        << "radius: " << radius << endl
        << "centre: " << centre.transpose() << endl;
    Geometry::print(out);
}

bool Sphere::intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, float& t) const {
    Eigen::Vector3f OC = origin - centre;
    //||O - C + t * d||^2 = r^2 expanded becomes
    // (O−C+td)⋅(O−C+td) = r^2, let OC = O - C
    // (OC + td)⋅(OC + td) = r^2
    // (OC⋅OC) + (d⋅OC)2t + (d⋅d)t^2 = r^2 , d is normalized in getRay()
    // this is a quadratic equation, at^2 + bt + c
    // let b = 2(d⋅OC), let c = OC⋅OC - r^2, a is 1 bcs d is normalized 
    float b = 2.0f * direction.dot(OC);
    float c = OC.squaredNorm() - radius * radius;

    // descriminant = b^2 - 4ac in quadratic formula
    float discriminant = b * b - 4.0f * c;

    if (discriminant < 0) return false;  // no intersection, 0 solutions 

    float sqrtDisc = sqrt(discriminant);
    float t0 = (-b - sqrtDisc)/2.0f;
    float t1 = (-b + sqrtDisc)/2.0f;

    if (t0 > 0) {
        t = t0;     // closest intersection in front of camera
        return true; 
    } else if (t1 > 0) {
        t = t1;     // ray started inside sphere, t0 < 0, t1 is exit point
        return true;
    }
    return false;      // both t0 and t1 are behind the camera
}

Rectangle::Rectangle(json& j) : Geometry(j){
    p1 = parseVector(j, "p1");
    p2 = parseVector(j, "p2");
    p3 = parseVector(j, "p3");
    p4 = parseVector(j, "p4");
}

void Rectangle::print(ostream& out) const {
    out << "Rectangle: " << endl
        << "p1: " << p1.transpose() << endl
        << "p2: " << p2.transpose() << endl
        << "p3: " << p3.transpose() << endl
        << "p4: " << p4.transpose() << endl;
    Geometry::print(out);
}

bool Rectangle::intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, float& t) const
{
    // R(t) = origin + t * direction
    // Plane: normal⋅(X - p1) = 0 => point is on a plane
    // normal⋅(R(t) - p1) = 0
    // t = normal⋅(p1 -  origin)/normal⋅direction
    const float EPS = 1e-6f;

    Eigen::Vector3f u = p2 - p1;
    Eigen::Vector3f v = p4 - p1;
    Eigen::Vector3f n = u.cross(v).normalized();

    float denom = n.dot(direction);
    if (std::abs(denom) < EPS)
        return false; // Ray parallel to plane

    float tHit = n.dot(p1 - origin) / denom;
    if (tHit <= 0)
        return false; // Behind camera

    Eigen::Vector3f P = origin + tHit * direction;

    // if all four normals are the same sign, they are considered "inside"
    // account for if the rectangle is accidentally read in clockwise order instead of counter clockwise order

    Eigen::Vector3f edge, current;
    float sign;

    edge = p2 - p1;
    current = P - p1;
    sign = n.dot(edge.cross(current));
    if (abs(sign) < EPS) sign = 1.0f;

    edge = p3 - p2;
    current = P - p2;
    if (sign * n.dot(edge.cross(current)) < 0) return false;

    edge = p4 - p3;
    current = P - p3;
    if (sign * n.dot(edge.cross(current)) < 0) return false;

    edge = p1 - p4;
    current = P - p4;
    if (sign * n.dot(edge.cross(current)) < 0) return false;

    t = tHit;
    return true;
}

