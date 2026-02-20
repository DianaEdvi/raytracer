#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <Eigen/Dense>
#include "json.hpp"
#include <iostream>
#include <memory>

using namespace nlohmann;
using namespace std;

class Geometry;
struct HitRecord;

class GeometryFactory {
    public: 
        unique_ptr<Geometry> create(json& j);
};

class Geometry {
    public: 
        virtual ~Geometry();
        friend ostream &operator<<(ostream &out, const Geometry &geometry);
        virtual void print(ostream& out) const;
        virtual bool intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, float& t) const = 0;
        // const Eigen::Vector3f& getAc() const { return ac; }
        // const Eigen::Vector3f& getDc() const { return dc; }
        unique_ptr<HitRecord> hitRecord;

    protected: 
        // float ka, kd, ks, pc;
        // Eigen::Vector3f ac, dc, sc;
        bool visible;
        Eigen::Matrix4f transformMatrix;
        Geometry(json& j);
};

class Sphere : public Geometry {
    public: 
    Sphere(json& j);
    void print(ostream& out) const override;
    virtual bool intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, float& t) const override;
    private: 
        float radius;
        Eigen::Vector3f centre;
    
};

class Rectangle : public Geometry {
    public: 
    Rectangle(json& j);
    void print(ostream& out) const override;
    virtual bool intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction, float& t) const override;
    private:
        Eigen::Vector3f p1, p2, p3, p4;
};

struct HitRecord {
    float t;
    Eigen::Vector3f hitPoint;
    Eigen::Vector3f normal;
    Eigen::Vector3f ac, dc, sc;
    float ka, kd, ks, pc;
};


#endif