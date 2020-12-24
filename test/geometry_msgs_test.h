#pragma once

#include "std_msgs_test.h"
#include <message_serialization/geometry_msgs_yaml.h>
#include <tf2_eigen/tf2_eigen.h>

template <>
geometry_msgs::Quaternion create()
{
  return tf2::toMsg(Eigen::Quaterniond::UnitRandom());
}

template <>
bool equals(const geometry_msgs::Quaternion& lhs, const geometry_msgs::Quaternion& rhs)
{
  Eigen::Quaterniond q_lhs, q_rhs;
  tf2::fromMsg(lhs, q_lhs);
  tf2::fromMsg(rhs, q_rhs);
  return q_lhs.isApprox(q_rhs);
}

template <>
geometry_msgs::Point create()
{
  const Eigen::Vector3d v = Eigen::Vector3d::Random();
  return tf2::toMsg(v);
}

template <>
bool equals(const geometry_msgs::Point& lhs, const geometry_msgs::Point& rhs)
{
  Eigen::Vector3d v_lhs, v_rhs;
  tf2::fromMsg(lhs, v_lhs);
  tf2::fromMsg(rhs, v_rhs);
  return v_lhs.isApprox(v_rhs);
}

template <>
geometry_msgs::Vector3 create()
{
  geometry_msgs::Vector3 v;
  return tf2::toMsg(Eigen::Vector3d::Random(), v);
}

template <>
bool equals(const geometry_msgs::Vector3& lhs, const geometry_msgs::Vector3& rhs)
{
  Eigen::Vector3d v_lhs, v_rhs;
  tf2::fromMsg(lhs, v_lhs);
  tf2::fromMsg(rhs, v_rhs);
  return v_lhs.isApprox(v_rhs);
}

template <>
geometry_msgs::Pose create()
{
  geometry_msgs::Pose p;
  p.position = create<geometry_msgs::Point>();
  p.orientation = create<geometry_msgs::Quaternion>();
  return p;
}

template <>
bool equals(const geometry_msgs::Pose& lhs, const geometry_msgs::Pose& rhs)
{
  bool eq = true;
  eq &= equals(lhs.position, rhs.position);
  eq &= equals(lhs.orientation, rhs.orientation);
  return eq;
}

template <>
geometry_msgs::PoseStamped create()
{
  geometry_msgs::PoseStamped p;
  p.pose = create<geometry_msgs::Pose>();
  p.header = create<std_msgs::Header>();
  return p;
}

template <>
bool equals(const geometry_msgs::PoseStamped& lhs, const geometry_msgs::PoseStamped& rhs)
{
  bool eq = true;
  eq &= equals(lhs.pose, rhs.pose);
  eq &= equals(lhs.header, rhs.header);
  return eq;
}

template <>
geometry_msgs::PoseArray create()
{
  geometry_msgs::PoseArray arr;
  arr.poses.resize(5);
  std::generate(arr.poses.begin(), arr.poses.end(), []()->geometry_msgs::Pose { return create<geometry_msgs::Pose>(); });
  arr.header = create<std_msgs::Header>();
  return arr;
}

template <>
bool equals(const geometry_msgs::PoseArray& lhs, const geometry_msgs::PoseArray& rhs)
{
  bool eq = true;
  eq &= equals(lhs.poses, rhs.poses);
  eq &= equals(lhs.header, rhs.header);
  return eq;
}

template <>
geometry_msgs::Transform create()
{
  geometry_msgs::Transform p;
  p.translation = create<geometry_msgs::Vector3>();
  p.rotation = create<geometry_msgs::Quaternion>();
  return p;
}

template <>
bool equals(const geometry_msgs::Transform& lhs, const geometry_msgs::Transform& rhs)
{
  bool eq = true;
  eq &= equals(lhs.translation, rhs.translation);
  eq &= equals(lhs.rotation, rhs.rotation);
  return eq;
}

template <>
geometry_msgs::TransformStamped create()
{
  geometry_msgs::TransformStamped p;
  p.transform = create<geometry_msgs::Transform>();
  p.header = create<std_msgs::Header>();
  return p;
}

template <>
bool equals(const geometry_msgs::TransformStamped& lhs, const geometry_msgs::TransformStamped& rhs)
{
  bool eq = true;
  eq &= equals(lhs.transform, rhs.transform);
  eq &= equals(lhs.header, rhs.header);
  return eq;
}
