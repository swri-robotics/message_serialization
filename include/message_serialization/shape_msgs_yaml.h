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
#ifndef MESSAGE_SERIALIZATION_SHAPE_MSGS_YAML
#define MESSAGE_SERIALIZATION_SHAPE_MSGS_YAML

#include <geometry_msgs/Point.h>
#include <shape_msgs/Mesh.h>
#include <shape_msgs/MeshTriangle.h>
#include <message_serialization/std_msgs_yaml.h>

namespace YAML
{

template<>
struct convert<geometry_msgs::Point>
{
  static Node encode(const geometry_msgs::Point& rhs)
  {
    Node node;
    node["x"] = rhs.x;
    node["y"] = rhs.y;
    node["z"] = rhs.z;
    return node;
  }

  static bool decode(const Node& node, geometry_msgs::Point& rhs)
  {
    if (node.size() != 3) return false;

    rhs.x = node["x"].as<double>();
    rhs.y = node["y"].as<double>();
    rhs.z = node["z"].as<double>();
    
    return true;
  }
};


template<>
struct convert<shape_msgs::MeshTriangle>
{
  static Node encode(const shape_msgs::MeshTriangle& rhs)
  {
    Node node;
    std::vector<unsigned int> tv;
    tv.push_back(rhs.vertex_indices[0]);
    tv.push_back(rhs.vertex_indices[1]);
    tv.push_back(rhs.vertex_indices[2]);
    node["vertex_indices"] = tv;
    return node;
  }

  static bool decode(const Node& node, shape_msgs::MeshTriangle& rhs)
  {
    std::vector<unsigned int> tv;
    tv = node["vertex_indices"].as<decltype (tv)>();
    rhs.vertex_indices[0] = tv[0];
    rhs.vertex_indices[1] = tv[1];
    rhs.vertex_indices[2] = tv[2];
    return true;
  }
};

template<>
struct convert<shape_msgs::Mesh>
{
  static Node encode(const shape_msgs::Mesh& rhs)
  {
    Node node;
    node["triangles"] = rhs.triangles;
    node["vertices"] = rhs.vertices;

    return node;
  }

  static bool decode(const Node& node, shape_msgs::Mesh& rhs)
  {
    if (node.size() != 2) return false;

    rhs.triangles = node["triangles"].as<std::vector< shape_msgs::MeshTriangle> >();
    rhs.vertices  = node["vertices"].as<std::vector<geometry_msgs::Point> >();

    return true;
  }
};

}

#endif // MESSAGE_SERIALIZATION_SHAPE_MSGS_YAML
