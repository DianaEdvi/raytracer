#ifndef LIGHT_H
#define LIGHT_H

#include <Eigen/Dense>
#include "json.hpp"
#include <iostream>
#include <memory>

using namespace nlohmann;
using namespace std;

class Light;

class LightFactory {
    public: 
        unique_ptr<Light> create(json& j);
};


class Light {
    public: 
        virtual ~Light();
        friend ostream &operator<<(ostream &out, const Light &light);
        virtual const std::vector<Eigen::Vector3f> getSamplePoints() const = 0;
        virtual void print(ostream& out) const;
        Eigen::Vector3f getId() const { return id; }
        Eigen::Vector3f getIs() const { return is; }

    protected: 
        Eigen::Vector3f id, is;
        Eigen::Matrix4f transformMatrix;
        unsigned int n;
        bool usecenter;
        bool use;
        Light(json& j);
};

class Point : public Light {
    public: 
        Point(json& j);
    void print(ostream& out) const override;
        const std::vector<Eigen::Vector3f> getSamplePoints() const override;
    private: 
        Eigen::Vector3f centre;
    
};

class Area: public Light {
    public: 
        Area(json& j);
    void print(ostream& out) const override;
    const std::vector<Eigen::Vector3f> getSamplePoints() const override;
    private:
        Eigen::Vector3f p1, p2, p3, p4;
        Eigen::Vector3f centre;
};


 


#endif