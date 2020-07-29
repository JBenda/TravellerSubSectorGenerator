#pragma once

#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Glsl.hpp>
#include <cmath>

template<typename T = float>
constexpr T PI = T(3.1415926535897932385L);

class Quat {
public:
  Quat() : Quat(sf::Vector3f(0,0,0),0){}
  Quat(const sf::Vector3f& axis, float angle);
  sf::Glsl::Mat3 mat() const {
    return sf::Glsl::Mat3(_matrix.data());
  };
  Quat operator*(const Quat& q2) const {
    std::array<float, 4> data;
    data[0] = _data[0]*q2._data[0];
    for (int i = 1; i < 4; ++i) {
     data[0] -= _data[i]*q2._data[i];
    }
    data[1] = _data[0]*q2._data[1]
      + _data[1]*q2._data[0]
      + _data[2]*q2._data[3]
      - _data[3]*q2._data[2];
    data[2] = _data[0]*q2._data[2]
      + _data[2]*q2._data[0]
      - _data[1]*q2._data[3]
      + _data[3]*q2._data[1];
    data[3] = _data[0]*q2._data[3]
      + _data[3]*q2._data[0]
      + _data[1]*q2._data[2]
      - _data[2]*q2._data[1];
    return Quat(std::move(data));
  }
private:
  void updateMatrix();
  Quat(std::array<float, 4>&& data) : _data{data} {
    updateMatrix();
  }
  std::array<float, 4> _data;
  std::array<float, 9> _matrix;
};

template<typename T, typename U>
T cross(const T& v1, const U& v2) {
  return T(
      v1.y*v2.z - v1.z*v2.y,
      v1.z*v2.x - v1.x*v2.z,
      v1.x*v2.y - v1.y*v2.x
   );
}

template<typename T, typename U>
float dot(const T& v1, const U& v2) {
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

inline float norm(const sf::Vector3f& vec) {
  return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

inline sf::Vector3f& normalize(sf::Vector3f& vec) {
  float n = norm(vec);
  vec.x /= n;
  vec.y /= n;
  vec.z /= n;
  return vec;
}

inline sf::Vector3f normalize(const sf::Vector3f& vec) {
  float n = norm(vec);
  return {vec.x / n, vec.y / n, vec.z / n};
}
