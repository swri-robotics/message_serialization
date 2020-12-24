cmake_minimum_required(VERSION 2.8.3)
project(message_serialization)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  eigen_conversions
  geometry_msgs
  sensor_msgs
  std_msgs
  roscpp_serialization
  trajectory_msgs
)

find_package(yaml-cpp REQUIRED)

catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    eigen_conversions
    geometry_msgs
    sensor_msgs
    std_msgs
    roscpp_serialization
    trajectory_msgs
  DEPENDS
    YAML_CPP
)

###########
## Build ##
###########
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIRS}
)

#############
## Install ##
#############
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

#############
## Testing ##
#############
if(CATKIN_ENABLE_TESTING)
  find_package(catkin REQUIRED COMPONENTS
    roscpp
    tf2_eigen
  )
  find_package(rostest REQUIRED)
  catkin_add_gtest(utest test/utest.cpp)
  target_link_libraries(utest ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})
endif()
