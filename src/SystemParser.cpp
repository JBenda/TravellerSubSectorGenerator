#include "SystemParser.hpp"
#include <array>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include <initializer_list> 
#include <cassert>
#include <cstdint>
template<typename T, std::size_t N>
class OpenGlVec : public std::array<T, N>
{
public:
  OpenGlVec() : std::array<T,N>() {}
  OpenGlVec(const OpenGlVec<T, N-1>& vec, const T& num) : std::array<T,N>()
  {
    for(std::size_t i = 0; i < N - 1; ++i)
      std::array<T, N>::operator[](i) = vec[i];
    std::array<T,N>::operator[](N-1) = num;
  }
  OpenGlVec(const OpenGlVec& vec) : std::array<T,N>()
  {
    for(std::size_t i = 0; i < N; ++i)
      std::array<T,N>::operator[](i) = vec[i];
  }
  OpenGlVec(std::initializer_list<T> list)
  {
    assert(list.size() <= N);
    auto itr = list.begin();
    for(std::size_t i = 0; i < N; ++i)
      std::array<T,N>::operator[](i) = itr != list.end() ? *(itr++) : T(0);
  }
  
  void operator*=(const T& scal) 
  {
    for(std::size_t i = 0; i < N; ++i) std::array<T,N>::operator[](i) *= scal;
  }

  OpenGlVec<T,N> 
  operator*(const T& scal) const { return ops(times, scal); }

  OpenGlVec<T,N>
  operator*(const OpenGlVec<T,N>& vec) const { return ops(times, vec); }
  
  friend OpenGlVec<T,N>  
  operator*(const T& scal, const OpenGlVec<T,N>& vec) { return vec * scal; }

  OpenGlVec<T,N> 
  operator+(const T& val) const { return ops(add, val); }

  OpenGlVec<T,N>
  operator+(const OpenGlVec<T,N>& vec) const { return ops(add, vec); }
  
  friend OpenGlVec<T,N> 
  operator+(const T& val, const OpenGlVec<T,N>& vec) { return vec + val; }

  OpenGlVec<T,N> 
  operator-(const T& val) const { return ops(minus, val); }

  OpenGlVec<T,N>
  operator-(const OpenGlVec<T,N>& vec) const { return ops(minus, vec); }

  friend OpenGlVec<T,N>
  operator-(const T& val, const OpenGlVec<T,N>& vec) { return vec.ops(minusR, val); }

  OpenGlVec<T,N>
  operator/(const T& val) const { return ops(div, val); }

private: 
  static T add(const T& v1, const T& v2) { return v1 + v2; }
  static T minus(const T& v1, const T& v2) { return v1 - v2; }  /**< vector minus number */
  static T minusR(const T& v1, const T& v2) { return v2 - v1; } /**< number minus vector */
  static T times(const T& v1, const T& v2) { return v1 * v2; }
  static T div(const T& v1, const T& v2) { return v1 / v2; }
  OpenGlVec<T,N> ops( T (*op)(const T&, const T&), const T& val  ) const
  {
    OpenGlVec<T,N> vec;
    for(std::size_t i = 0; i < N; ++i)
      vec[i] = (*op)( std::array<T,N>::operator[](i), val);
    return vec;
  }
  OpenGlVec<T,N> ops( T (*op)(const T&, const T&), const OpenGlVec<T,N> vecI ) const
  {
    OpenGlVec<T,N> vec;
    for(std::size_t i = 0; i < N; ++i)
      vec[i] = (*op) (std::array<T,N>::operator[](i), vecI[i]);
    return vec;
  }
};
template<typename T, std::size_t N>
OpenGlVec<T,N> floor(const OpenGlVec<T,N>& vec)
{
  OpenGlVec<T, N> vecF;
  for(std::size_t i = 0; i < N; ++i)
  {
    vecF[i] = static_cast<int>(vec[i]);
    if(vec[i] < 0.)
      vecF[i] -= 1.;
  }
  return vecF;
}

template<typename T, std::size_t N>
OpenGlVec<T, N> fract(const OpenGlVec<T, N>& vec)
{
  OpenGlVec<T,N> vecF;
  for(std::size_t i = 0; i < N; ++i)
    vecF[i] = vec[i] - floor(vec[i]);
  return vecF;
}

float floor(float value)
{
  return static_cast<int>(value) - ( value < 0 ? 1.: 0.);
}

float fract(float value)
{
  return value - floor(value);
}

// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/mix.xhtml
// by OpenGl
template<typename T, typename P>
T mix(T x, T y, P a)
{
  return (x * (P(1) - a)) + (y * a);
}

template<typename T, std::size_t N>
T length(const OpenGlVec<T,N>& vec)
{
  T out;
  for(std::size_t i = 0; i < N; ++i)
    out += vec[i] * vec[i];
  return sqrt(out);
}

template<typename T, std::size_t N>
OpenGlVec<T,N> sin(const OpenGlVec<T,N>& vecI)
{
  OpenGlVec<T,N> vecO;
  for(std::size_t i = 0; i < N; ++i)
    vecO[i] = sin(vecI[i]);
  return vecO;
}

struct vec2 : public OpenGlVec<float, 2>
{
  vec2(float f1, float f2) : 
    OpenGlVec<float, 2>({f1, f2}),
    x{OpenGlVec<float, 2>::operator[](0)},
    y{OpenGlVec<float, 2>::operator[](1)}
  {}
  vec2(const OpenGlVec<float, 2>& vec) : 
    OpenGlVec<float, 2>(vec),
    x{OpenGlVec<float, 2>::operator[](0)},
    y{OpenGlVec<float, 2>::operator[](1)}
  {}
  vec2& operator=(const vec2& vec)
  {
    x = vec.x;
    y = vec.y;
    return *this;
  }
  float &x, &y;
};

struct vec2i : public OpenGlVec<int, 2> {
  vec2i(int i1, int i2) : 
    OpenGlVec<int,2>({i1,i2}),
    x{OpenGlVec<int,2>::operator[](0)},
    y{OpenGlVec<int,2>::operator[](1)} {}

  vec2i(const OpenGlVec<int,2>& vec) :
    OpenGlVec<int,2>(vec),
    x{OpenGlVec<int,2>::operator[](0)},
    y{OpenGlVec<int,2>::operator[](1)} {}
  vec2i& operator=(const vec2i& vec) {
    x = vec.x;
    y = vec.y;
    return *this;
  }
  int &x, &y;
};

struct vec3 : public OpenGlVec<float, 3>
{
  vec3(float f1, float f2, float f3) : 
    OpenGlVec<float, 3>({f1, f2, f3}), 
    x{OpenGlVec<float, 3>::operator[](0)}, 
    y{OpenGlVec<float, 3>::operator[](1)}, 
    z{OpenGlVec<float, 3>::operator[](2)}
  {}
  vec3(const OpenGlVec<float, 3>& vec) : 
    OpenGlVec<float, 3>(vec), 
    x{OpenGlVec<float, 3>::operator[](0)}, 
    y{OpenGlVec<float, 3>::operator[](1)}, 
    z{OpenGlVec<float, 3>::operator[](2)}
  {}
  vec3& operator=(const vec3& vec)
  {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
  }
  float &x, &y, &z;
  vec2 xy()
  {
    return vec2(x, y);
  }
};

struct vec4 : public OpenGlVec<float, 4>
{
  vec4(float f1, float f2, float f3, float f4) : 
    OpenGlVec<float, 4>({f1, f2, f3, f4}), 
    x{OpenGlVec<float, 4>::operator[](0)}, 
    y{OpenGlVec<float, 4>::operator[](1)}, 
    z{OpenGlVec<float, 4>::operator[](2)}, 
    w{OpenGlVec<float, 4>::operator[](3)} 
  {}
  vec4(const OpenGlVec<float, 4>& vec) : 
    OpenGlVec<float, 4>(vec), 
    x{OpenGlVec<float, 4>::operator[](0)}, 
    y{OpenGlVec<float, 4>::operator[](1)}, 
    z{OpenGlVec<float, 4>::operator[](2)}, 
    w{OpenGlVec<float, 4>::operator[](3)} 
  {}
  vec4(const OpenGlVec<float, 3>& vec, float d) : 
    OpenGlVec<float, 4>(vec, d), 
    x{OpenGlVec<float, 4>::operator[](0)}, 
    y{OpenGlVec<float, 4>::operator[](1)}, 
    z{OpenGlVec<float, 4>::operator[](2)}, 
    w{OpenGlVec<float, 4>::operator[](3)} 
  {}
  vec4& operator=(const vec4& vec)
  {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
    return *this;
  }
  float &x, &y, &z, &w;
};

const float iTime = 1232.23f;
const vec2 iResolution(500., 500.);

template<typename T>
const T& max( const T& t1, const T& t2)
{
  return std::max(t1, t2);
}

// https://www.shadertoy.com/view/lssGRH
// written by Trisomie21
// start
float noise2D(vec2 uv)
{
	uv = fract(uv)*1e3;
	vec2 f = fract(uv);
	uv = floor(uv);
        float v = uv.x+uv.y*1e3;
        vec4 r = vec4(v, v+1., v+1e3, v+1e3+1.);
        r = fract(1e5*sin(r*1e-2));
	f = f*f*(3.0-2.0*f);
	return (mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y));	
}

float fractal(vec2 p) {
	float v = 0.5;
	v += noise2D(p*16.); v*=.5;
	v += noise2D(p*8.); v*=.5;
	v += noise2D(p*4.); v*=.5;
	v += noise2D(p*2.); v*=.5;
	v += noise2D(p*1.);  v*=.5;
	return v;
}

vec3 func( vec2  p) {
	p = p*.1+.5;
	vec3 c = vec3(.0, .0, .1);
	vec2 d = vec2(iTime*.0001, 0.);
        c = mix(c, vec3(.8, .1, .1), pow(fractal(p*.20-d), 3.)*2.);
        c = mix(c, vec3(.9, .6, .6), pow(fractal(p.y*p*.10+d)*1.3, 3.));
        c = mix(c, vec3(1., 1., 1.), pow(fractal(p.y*p*.05+d*2.)*1.2, 1.5));
	return c;
}

vec4 mainImage(vec2 fragCoord) {
	vec2 p = 2.*(fragCoord - iResolution*.5)/iResolution.y;
	float d = length(p);
	p *= (acos(d) - 1.57079632)/d;
	return vec4(func(p)*max(1.-d*d*d, 0.), 1.0);
}
// end

/** \brief transform float defined color to byte defined Color
 * \param color array from colors with length 3 or 4
 */
template<size_t N>
sf::Color dcTbx(const OpenGlVec<float,N>& color)
{
  static_assert(N == 4 || N == 3, "fcTbx can only convert rgb and rgba");
  if constexpr (N == 4)
  {
    std::uint8_t c[3];
    float b;
    for(int i = 0; i < 3; ++i)
    {
      b = color[i] * 255.;
      if(b < 1.) c[i] = 0;
      else if(b > 254.) c[i] = 255;
      else c[i] = static_cast<std::uint8_t>(b);
    }
    return sf::Color(c[0], c[1], c[2]);
  }
  else 
    return sf::Color(color[0] * 255., color[1] * 255., color[2] * 255., 255.);
}

sf::Image SystemParser::generatePicture(const System& sys) const
{
  sf::Image img;
  img.create(500, 500, sf::Color::Yellow);
  vec2i pos(0, 0);
  sf::Color co;
  for(;pos.y < 512; pos.y+=1)
    for(pos.x = 0.; pos.x < 512; pos.x+=1)
      if ((pos.y / 64 + pos.x / 64)%2) {
        img.setPixel(pos.x, pos.y, sf::Color::Green);
      }// dcTbx(mainImage(pos)));
  return img;
}
