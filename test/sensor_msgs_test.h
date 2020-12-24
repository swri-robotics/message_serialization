#pragma once

#include "std_msgs_test.h"
#include <message_serialization/sensor_msgs_yaml.h>

template <>
sensor_msgs::JointState create()
{
  const std::size_t n = 10;
  sensor_msgs::JointState js;
  js.header = create<std_msgs::Header>();
  js.name.resize(n);
  std::fill(js.name.begin(), js.name.end(), "test");
  js.position = createRandomVector(n);
  js.velocity = createRandomVector(n);
  js.effort = createRandomVector(n);

  return js;
}

template <>
bool equals(const sensor_msgs::JointState& lhs, const sensor_msgs::JointState& rhs)
{
  bool eq = true;
  eq &= equals(lhs.header, rhs.header);
  eq &= lhs.name == rhs.name;
  eq &= isApprox(lhs.position.data(), rhs.position.data(), lhs.position.size());
  eq &= isApprox(lhs.velocity.data(), rhs.velocity.data(), lhs.velocity.size());
  eq &= isApprox(lhs.effort.data(), rhs.effort.data(), lhs.velocity.size());
  return eq;
}

template <>
sensor_msgs::RegionOfInterest create()
{
  sensor_msgs::RegionOfInterest roi;
  roi.width = 511;
  roi.height = 1567;
  roi.x_offset = 12;
  roi.y_offset = 456;
  roi.do_rectify = true;
  return roi;
}

template <>
bool equals(const sensor_msgs::RegionOfInterest& lhs, const sensor_msgs::RegionOfInterest& rhs)
{
  return lhs == rhs;
}

template <>
sensor_msgs::CameraInfo create()
{
  sensor_msgs::CameraInfo info;
  info.header = create<std_msgs::Header>();
  randomize(info.D.data(), info.D.size());
  randomize(info.K.data(), info.K.size());
  randomize(info.P.data(), info.P.size());
  randomize(info.R.data(), info.R.size());
  info.roi = create<sensor_msgs::RegionOfInterest>();
  info.width = 12345;
  info.height = 54321;
  info.binning_x = 50;
  info.binning_y = 75;
  info.distortion_model = "test";

  return info;
}

template <>
bool equals(const sensor_msgs::CameraInfo& lhs, const sensor_msgs::CameraInfo& rhs)
{
  bool eq = true;
  eq &= equals(lhs.header, rhs.header);
  eq &= isApprox(lhs.D.data(), rhs.D.data(), lhs.D.size());
  eq &= isApprox(lhs.K.data(), rhs.K.data(), lhs.K.size());
  eq &= isApprox(lhs.P.data(), rhs.P.data(), lhs.P.size());
  eq &= isApprox(lhs.R.data(), rhs.R.data(), lhs.R.size());
  eq &= equals(lhs.roi, rhs.roi);
  eq &= lhs.width == rhs.width;
  eq &= lhs.height == rhs.height;
  eq &= lhs.binning_x == rhs.binning_x;
  eq &= lhs.binning_y == rhs.binning_y;
  eq &= lhs.distortion_model == rhs.distortion_model;

  return eq;
}

