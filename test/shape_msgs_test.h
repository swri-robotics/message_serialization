#pragma once

#include "geometry_msgs_test.h"
#include <message_serialization/shape_msgs_yaml.h>

template <>
shape_msgs::MeshTriangle create()
{
  shape_msgs::MeshTriangle tri;
  tri.vertex_indices[0] = 4;
  tri.vertex_indices[1] = 3;
  tri.vertex_indices[2] = 5;
  return tri;
}

template <>
bool equals(const shape_msgs::MeshTriangle& lhs, const shape_msgs::MeshTriangle& rhs)
{
  return lhs == rhs;
}

template <>
shape_msgs::Mesh create()
{
  shape_msgs::Mesh mesh;
  const std::size_t n = 10;
  mesh.vertices.resize(n);
  std::generate(mesh.vertices.begin(), mesh.vertices.end(),
                []() -> geometry_msgs::Point { return create<geometry_msgs::Point>(); });

  mesh.triangles.resize(n);
  std::generate(mesh.triangles.begin(), mesh.triangles.end(),
                []() -> shape_msgs::MeshTriangle { return create<shape_msgs::MeshTriangle>(); });

  return mesh;
}

template <>
bool equals(const shape_msgs::Mesh& lhs, const shape_msgs::Mesh& rhs)
{
  bool eq = true;
  eq &= equals(lhs.vertices, rhs.vertices);
  eq &= equals(lhs.triangles, rhs.triangles);
  return eq;
}
