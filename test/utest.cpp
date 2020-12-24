#include <gtest/gtest.h>
#include <message_serialization/binary_serialization.h>
#include <message_serialization/serialize.h>
#include "std_msgs_test.h"
#include "geometry_msgs_test.h"
#include "trajectory_msgs_test.h"
#include "shape_msgs_test.h"
#include "sensor_msgs_test.h"

const std::string YAML_EXT = "yaml";
const std::string BINARY_EXT = "msg";

std::string createFilename(const std::string& extension)
{
  static int counter = 0;
  return "/tmp/" + std::to_string(++counter) + "_test." + extension;
}

template <typename T>
class SerializationTestFixture : public testing::Test
{
public:
  using testing::Test::Test;

  void runTest()
  {
    // YAML
    // Throwing version
    {
      const std::string filename = createFilename(YAML_EXT);
      T value = create<T>();
      EXPECT_NO_THROW(message_serialization::serialize(value, filename));
      T new_value;
      EXPECT_NO_THROW(new_value = message_serialization::deserialize<T>(filename));
      EXPECT_TRUE(equals(value, new_value));
    }

    // Non-throwing version
    {
      const std::string filename = createFilename(YAML_EXT);
      T value = create<T>();
      EXPECT_TRUE(message_serialization::serialize(filename, value));
      T new_value;
      EXPECT_TRUE(message_serialization::deserialize(filename, new_value));
      EXPECT_TRUE(equals(value, new_value));
    }

    // Binary
    // Throwing version
    {
      const std::string filename = createFilename(BINARY_EXT);
      T value = create<T>();
      EXPECT_NO_THROW(message_serialization::serializeToBinary(value, filename));
      T new_value;
      EXPECT_NO_THROW(new_value = message_serialization::deserializeFromBinary<T>(filename));
      EXPECT_TRUE(equals(value, new_value));
    }

    // Non-throwing version
    {
      const std::string filename = createFilename(BINARY_EXT);
      T value = create<T>();
      EXPECT_TRUE(message_serialization::serializeToBinary(filename, value));
      T new_value;
      EXPECT_TRUE(message_serialization::deserializeFromBinary(filename, new_value));
      EXPECT_TRUE(equals(value, new_value));
    }
  }
};

using Implementations = testing::Types<ros::Time,
                                       std_msgs::Header,
                                       geometry_msgs::Point,
                                       geometry_msgs::Vector3,
                                       geometry_msgs::Quaternion,
                                       geometry_msgs::Pose,
                                       geometry_msgs::PoseStamped,
                                       geometry_msgs::PoseArray,
                                       geometry_msgs::Transform,
                                       geometry_msgs::TransformStamped,
                                       trajectory_msgs::JointTrajectoryPoint,
                                       trajectory_msgs::JointTrajectory,
                                       shape_msgs::MeshTriangle,
                                       shape_msgs::Mesh,
                                       sensor_msgs::JointState,
                                       sensor_msgs::RegionOfInterest,
                                       sensor_msgs::CameraInfo>;

TYPED_TEST_CASE(SerializationTestFixture, Implementations);

TYPED_TEST(SerializationTestFixture, SerializationTest)
{
  this->runTest();
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
