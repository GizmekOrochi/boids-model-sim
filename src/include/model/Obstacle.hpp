#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#pragma once
#include <string>
#include "utils/MathsVector.hpp"


namespace bd {

class Obstacle {
public:

    MathsVector<float, 3> position;
    MathsVector<int, 3> size;


    Obstacle() : position{}, size{{10, 10, 10}} {}

    Obstacle(MathsVector<float, 3> position, MathsVector<int, 3> size) : position{position}, size{size} {}
};

} //namespace


#endif // OBSTACLE_HPP