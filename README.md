# message_serialization

A header-only utility for serializing C++ structures (specifically ROS messages) into YAML-formatted and binary-formatted files that can be loaded to/from disk

## Usage

```c++
// Serialization headers
#include <message_serialization/serialize.h>
#include <message_serialization/binary_serialization.h>

// Datatype-specific serialization header
#include <message_serialization/geometry_msgs_serialization.h>

int main(int argc, char** argv)
{
  // Create a structure to serialize
  geometry_msgs::PoseStamped ps;
  ps.header.frame = "world";
  ps.header.stamp = ros::Time::now();
  ...

  const std::string filename = "/path/to/save/dir/file.yaml";

  // YAML Serialization
  // Serialize the message
  if(!message_serialization::serialize(filename, ps))
    return -1;

  // De-serialize the message
  geometry_msgs::Pose new_ps;
  if(!message_serialization::deserialize(filename, new_ps))
    return -1;
    
  // Binary serialization (ROS messages only)
  // Serialize the message
  if(!message_serialization::serializeToBinary(filename, ps))
    return -1;

  // De-serialize the message
  if(!message_serialization::deserializeFromBinary(filename, new_ps))
    return -1;
    
  return 0;
}
```

## Customization

Any custom C++ structure can be serialized to YAML with this library, provided that a specific template structure for the custom datatype be specialized in the YAML namespace:

```c++
struct CustomStruct;

namespace YAML
{
  template<>
  struct convert<CustomStruct>
  {
    static Node encode(const CustomStruct& rhs);
    static bool decode(const Node& node, CustomStruct& rhs);
  };
}
```

See the implementations in the `include` directory for examples on how to implement this structure for a custom data type.
