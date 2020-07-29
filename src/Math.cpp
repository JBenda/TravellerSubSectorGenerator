#include "Math.hpp"

Quat::Quat(const sf::Vector3f& axis, float angle) {
  float a2 = angle / 2.f;
  float as = sin(a2);
  float ac = cos(a2);
  _data[0] = axis.x * as;
  _data[1] = axis.y * as;
  _data[2] = axis.z * as;
  _data[3] = ac;
  updateMatrix();
}

void Quat::updateMatrix() {
    _matrix[0] = 1. - 2. * (_data[1]*_data[1] + _data[2]*_data[2]);
    _matrix[3] = 2.*(_data[0]*_data[1]+_data[2]*_data[3]);
    _matrix[6] = 2.*(_data[0]*_data[2]-_data[1]*_data[3]);
    _matrix[1] = 2.*(_data[0]*_data[1] -_data[2]*_data[3]);
    _matrix[4] = 1. - 2.*(_data[0]*_data[0] + _data[2]*_data[2]);
    _matrix[7] = 2.*(_data[1]*_data[2] + _data[0]*_data[3]);
    _matrix[2] = 2.*(_data[0]*_data[2] + _data[1]*_data[3]);
    _matrix[5] = 2.*(_data[1]*_data[2]-_data[0]*_data[3]);
    _matrix[8] = 1.-2.*(_data[0]*_data[0] + _data[1]*_data[1]);
}
