#pragma once

#include "std_msgs_test.h"
#include <message_serialization/trajectory_msgs_yaml.h>

template <>
trajectory_msgs::JointTrajectoryPoint create()
{
  trajectory_msgs::JointTrajectoryPoint pt;

  std::size_t n = 10;
  pt.positions = createRandomVector(n);
  pt.velocities = createRandomVector(n);
  pt.accelerations = createRandomVector(n);
  pt.effort = createRandomVector(n);
  pt.time_from_start = ros::Duration(1.1);

  return pt;
}

template <>
bool equals(const trajectory_msgs::JointTrajectoryPoint& lhs, const trajectory_msgs::JointTrajectoryPoint& rhs)
{
  bool eq = true;
  eq &= isApprox(lhs.positions.data(), rhs.positions.data(), lhs.positions.size());
  eq &= isApprox(lhs.velocities.data(), rhs.velocities.data(), lhs.velocities.size());
  eq &= isApprox(lhs.accelerations.data(), rhs.accelerations.data(), lhs.accelerations.size());
  eq &= isApprox(lhs.effort.data(), rhs.effort.data(), rhs.accelerations.size());
  eq &= lhs.time_from_start == rhs.time_from_start;
  return eq;
}

template <>
trajectory_msgs::JointTrajectory create()
{
  const std::size_t n = 10;
  trajectory_msgs::JointTrajectory traj;
  traj.header = create<std_msgs::Header>();
  traj.joint_names = std::vector<std::string>(n, "test");
  traj.points.resize(n);
  std::generate(traj.points.begin(), traj.points.end(), []() -> trajectory_msgs::JointTrajectoryPoint {
    return create<trajectory_msgs::JointTrajectoryPoint>();
  });

  return traj;
}

template <>
bool equals(const trajectory_msgs::JointTrajectory& lhs, const trajectory_msgs::JointTrajectory& rhs)
{
  bool eq = true;
  eq &= equals(lhs.header, rhs.header);
  eq &= lhs.joint_names == rhs.joint_names;
  eq &= equals(lhs.points, rhs.points);
  return eq;
}
