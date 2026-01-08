#ifndef MATHSVECTOR_HPP
#define MATHSVECTOR_HPP

#pragma once
#include <array>
#include <vector>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <limits>

namespace bd {

template<typename T, size_t Dimension_>
class MathsVector {
public:
    std::array<T, Dimension_> dimensions_{};

    MathsVector() = default;

    MathsVector(const std::array<T, Dimension_>& dimensions) : dimensions_{dimensions} {}
    //MathsVector(const MathsVector& other) : dimensions_(other.dimensions_) {}

    const T& operator[](size_t index) const { return dimensions_[index]; }        

    MathsVector operator+(const MathsVector& other) const { 
    	std::array<T, Dimension_> newDim{dimensions_};
    	for(size_t i = 0; i < Dimension_; i++) newDim[i]+= other[i];
    	return MathsVector(newDim); 
    }
      
    MathsVector operator-(const MathsVector& other) const { 
    	std::array<T, Dimension_> newDim{dimensions_};
    	for(size_t i = 0; i < Dimension_; i++) newDim[i]-= other[i];
    	return MathsVector(newDim); 
    }
    
    MathsVector operator*(const T scalar) const { 
    	std::array<T, Dimension_> newDim{dimensions_};
    	for(size_t i = 0; i < Dimension_; i++) newDim[i] = newDim[i] * scalar;
    	return MathsVector(newDim); 
    }
      
    MathsVector operator/(const T scalar) const { 
    	std::array<T, Dimension_> newDim{dimensions_};
    	assert((scalar != T(0)) && "Division by zero impossible");
    	for(size_t i = 0; i < Dimension_; i++) newDim[i] = newDim[i] / scalar;
    	return MathsVector(newDim); 
    }

    bool operator==(const MathsVector& other) const { return dimensions_ == other.dimensions_; }
    
    bool operator!=(const MathsVector& other) const { 
    	return !(this->operator==(other)); 
    }
    

    MathsVector& operator=(const MathsVector& other) { 
    	dimensions_ = other.dimensions_;
    	return *this; 
    }
    
    
    MathsVector& operator+=(const MathsVector& other) { 
    	dimensions_ = this->operator+(other).dimensions_;
    	return *this;
    }
    
    MathsVector& operator-=(const MathsVector& other) {
    	dimensions_ = this->operator-(other).dimensions_;
    	return *this;
    }
    
    MathsVector& operator*=(const T scalar) {
        dimensions_ = this->operator*(scalar).dimensions_;
    	return *this;
    }
    
    MathsVector& operator/=(const T scalar) {
        dimensions_ = this->operator/(scalar).dimensions_;
    	return *this;
    }
    

    T dot(const MathsVector& other) const {
        T result{};
        for(size_t i = 0; i < Dimension_; i++) result += (*this)[i] * other[i];
        return result;
    }

    
    MathsVector cross(const MathsVector& other) {
    	assert((Dimension_ == 3) && "Cross product only avalible in 3D");
    	std::array<T, 3> newDim{};
    	newDim[0] = this->operator[](1) * other[2] - this->operator[](2) * other[1];
    	newDim[1] = this->operator[](2) * other[0] - this->operator[](0) * other[2];
    	newDim[2] = this->operator[](0) * other[1] - this->operator[](1) * other[0];
    	return MathsVector<T, Dimension_>{newDim};
    }
    
    T lengthSq() const {
    	T res{};
    	for(size_t i = 0; i < Dimension_; i++) res += (this->operator[](i) * this->operator[](i));
    	return res;
    }
    
    T length() const { 
    	T res{this->lengthSq()};
    	return std::sqrt(res);
    }
    
    MathsVector normalized() const {
    	MathsVector res{this->operator/(this->length())};
    	return res;
    }
    
    bool isZero(T value) const { return value < std::numeric_limits<T>::min(); }
    
    MathsVector limited(T Max) const {
    	T lenSq = this->lengthSq();
    	return (lenSq > (Max * Max)) ? *this * (Max / std::sqrt(lenSq)) : *this;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, MathsVector<T, Dimension_>& other) {
    	for(size_t i = 0; i < Dimension_; i++) stream << other.dimensions_[i] << ", ";
    	return stream;
    }

};;

} // namespace

#endif