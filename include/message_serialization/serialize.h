/* 
 * Copyright 2018 Southwest Research Institute
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MESSAGE_SERIALIZATION_SERIALIZE_H
#define MESSAGE_SERIALIZATION_SERIALIZE_H

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <ros/console.h>

namespace message_serialization
{
/**
 * @brief Serializes an input object to a YAML-formatted file
 * @param file
 * @param val
 * @throws exception on failure to open or write to a file stream
 */
template <class T>
inline void serialize(const std::string& file, const T& val)
{
  std::ofstream ofh(file);
  if (!ofh)
    throw std::runtime_error("Failed to open output file stream at '" + file + "'");

  YAML::Node n = YAML::Node(val);
  ofh << n;
}

/**
 * @brief Serializes an input object to a YAML-formatted file
 * @param file
 * @param val
 * @return true on success, false otherwise
 */
template <class T>
inline bool serialize(const std::string& file, const T& val) noexcept
{
  try
  {
    serialize(file, val);
  }
  catch (const std::exception& ex)
  {
    ROS_ERROR_STREAM(ex.what());
    return false;
  }
  return true;
}

/**
 * @brief Deserializes a YAML-formatted file into a specific object type
 * @param file
 * @return
 * @throws exception when unable to load the file or convert it to the specified type
 */
template <class T>
inline T deserialize(const std::string &file)
{
  YAML::Node node;
  node = YAML::LoadFile(file);
  return node.as<T>();
}

/**
 * @brief Deserializes a YAML-formatted file into a specific object type
 * @param file
 * @param val
 * @return true on success, false otherwise
 */
template <class T>
inline bool deserialize(const std::string &file, T& val) noexcept
{
  try
  {
    val = deserialize<T>(file);
  }
  catch (const std::exception& ex)
  {
    ROS_ERROR_STREAM("Deserialization error: " << ex.what());
    return false;
  }
  return true;
}

} // namespace message_serialization

#endif // MESSAGE_SERIALIZATION_SERIALIZE_H
