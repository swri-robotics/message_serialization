#pragma once

#include <Eigen/Geometry>
#include <random>

inline std::vector<double> createRandomVector(const std::size_t n)
{
  static std::mt19937 gen(0);
  static std::uniform_real_distribution<double> dist;
  std::vector<double> v(n);
  std::generate(v.begin(), v.end(), []() -> double { return dist(gen); });
  return v;
}

inline void randomize(double* data, const std::size_t len)
{
  static std::mt19937 gen(0);
  static std::uniform_real_distribution<double> dist;
  std::generate(data, data + len, []() -> double { return dist(gen); });
}

inline bool isApprox(const double* lhs, const double* rhs, const std::size_t len)
{
  Eigen::Map<const Eigen::VectorXd> map_lhs(lhs, len);
  Eigen::Map<const Eigen::VectorXd> map_rhs(rhs, len);
  return map_lhs.isApprox(map_rhs);
}

/** @brief Specializable function for creating a serializable object with non-default values */
template <typename T>
T create();

/** @brief Specializable function for comparing the equality of two objects */
template <typename T>
bool equals(const T& lhs, const T& rhs);

/** @brief Specializable function for comparing the equality of two vectors of objects */
template <typename T>
inline bool equals(const std::vector<T>& lhs, const std::vector<T>& rhs)
{
  bool eq = lhs.size() == rhs.size();
  if (eq)
  {
    for (std::size_t i = 0; i < lhs.size(); ++i)
    {
      eq &= equals(lhs[i], rhs[i]);
    }
  }
  return eq;
}
