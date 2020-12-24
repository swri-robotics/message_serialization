#pragma once

#include "utilities.h"
#include <message_serialization/std_msgs_yaml.h>

template <>
ros::Time create()
{
  return ros::Time(5.1);
}

template <>
bool equals(const ros::Time& lhs, const ros::Time& rhs)
{
  return lhs == rhs;
}

template <>
std_msgs::Header create()
{
  std_msgs::Header msg;
  msg.stamp = create<ros::Time>();
  msg.seq = 2;
  msg.frame_id = "test";
  return msg;
}

template <>
bool equals(const std_msgs::Header& lhs, const std_msgs::Header& rhs)
{
  return lhs == rhs;
}
