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
        friend ostream &operator<<(ostream &out, const Output &output);
        Output(json& j);

    private:
        string filename;
        int size[2];
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