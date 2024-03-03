#include "MinxinOperator.h"

#include <array>
#include <iostream>

struct Vec3 : public knight::Mixin<knight::AddMixin<int,double,std::array<int,3>>,
                                   knight::MultipliMixin<int,double>,
                                   knight::unit_steppable>{
    int x, y, z;

    Vec3(int x, int y, int z) : x(x), y(y), z(z) { }

    Vec3& operator +=(const Vec3& rhs) {
        this->x = rhs.x + this->x;
        this->y = rhs.y + this->y;
        this->z = rhs.z + this->z;
        return *this;
    }

    Vec3& operator +=(const double& rhs) {
        std::cout << "double   += here" << std::endl;
        this->x = rhs + this->x;
        this->y = rhs + this->y;
        this->z = rhs + this->z;
        return *this;
    }

    Vec3& operator +=(const int& rhs) {
        std::cout << "int  += here" << std::endl;
        this->x = rhs + this->x;
        this->y = rhs + this->y;
        this->z = rhs + this->z;
        return *this;
    }

    Vec3& operator *=(const int& rhs) {
        std::cout << "int  *= here" << std::endl;
        this->x = rhs * this->x;
        this->y = rhs * this->y;
        this->z = rhs * this->z;
        return *this;
    }

    Vec3& operator +=(const std::array<int,3>& rhs) {
        std::cout << "array  += here" << std::endl;
        this->x = rhs[0] + this->x;
        this->y = rhs[1] + this->y;
        this->z = rhs[2] + this->z;
        return *this;
    }

    Vec3& operator ++() {
        std::cout << "self pre add " << std::endl;
        ++x;
        ++y;
        ++z;
        return *this;
    }
};

int main() {
    Vec3 one(1, 1, 1);
    Vec3 two(2, 2, 2);
    std::array<int,3> arr{2, 2, 2};
    two + one;
    two + arr;
    two + 1;
    two + 1.2;
}
