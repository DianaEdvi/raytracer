#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include "json.hpp"

#include <Eigen/Dense>

using namespace nlohmann;
using namespace std;

class Output {
    public:
        virtual ~Output();
        const Eigen::Vector3f& getLookat() const { return lookat; }
        const Eigen::Vector3f& getUp() const { return up; }
        const Eigen::Vector3f& getCentre() const { return centre; }
        float getFov() const { return fov; }

        unsigned int getWidth() const { return size[0]; }
        unsigned int getHeight() const { return size[1]; }

        friend ostream &operator<<(ostream &out, const Output &output);
        Output(json& j);

    private:
        string filename;
        unsigned int size[2];
        Eigen::Vector3f lookat;
        Eigen::Vector3f up;
        Eigen::Vector3f centre;
        float fov;
        Eigen::Vector3f ai;
        Eigen::Vector3f bkc;
        Eigen::Vector3i raysperpixel;
        bool antialiasing;
        bool twosiderender;
        bool globalillum;
};

#endif