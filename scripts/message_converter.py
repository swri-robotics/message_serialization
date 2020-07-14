#! /usr/bin/env/python
# This Python file uses the following encoding: utf-8

"""
Copyright 2020 Southwest Research Institute

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
see the License for the specific language governing permissions and
limitations under the License.
"""

from rospy_message_converter import json_message_converter as jmc
import json
import rospy
import sys
from StringIO import StringIO
import argparse

class Converter:
  def __init__(self, module_name, msg_class):
    self.module = __import__(module_name)
    self.msg_class = getattr(self.module.msg, msg_class)

  def binaryFileToROS(self, filename):
    msg = self.msg_class()
    with open(filename, 'r') as file:
      msg = msg.deserialize(file.read())
    return msg

  def rosToBinaryFile(self, msg, filename):
    ser = StringIO()
    msg.serialize(ser)
    with open(filename, 'w') as file:
      file.write(ser.getvalue())

  def jsonFileToROS(self, filename):
    json_str = ''
    with open(filename, 'r') as file:
      data = json.load(file)
      json_str = json.dumps(data)
    return jmc.convert_json_to_ros_message(self.msg_class()._type, json_str)

  def rosToJsonFile(self, msg, filename):
    json_str = jmc.convert_ros_message_to_json(msg)
    json_obj = json.loads(json_str)
    with open(filename, 'w') as file:
      file = json.dump(json_obj, file, indent=2)


if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='Converts binary ROS message files to JSON files and vice versa')
  parser.add_argument('msg_module', help='The module from which to load the ROS message class (i.e. std_msgs.msg)')
  parser.add_argument('msg_class', help='The ROS message class name (i.e. Header)')
  parser.add_argument('bin_file', help="The binary ROS message file to read/write from")
  parser.add_argument('json_file', help="The JSON formatted ROS message file to read/write from")
  parser.add_argument('-b2j', '--binary-to-json', action='store_true', help="Convert binary ROS file to JSON formatted ROS file")
  parser.add_argument('-j2b', '--json-to-binary', action='store_true', help="Convert JSON formatted ROS File to binary ROS file")

  args = parser.parse_args()

  try:
    if (args.json_to_binary and args.binary_to_json) or (not args.json_to_binary and not args.binary_to_json):
      raise Exception("Choose a single direction of conversion!")

    conv = Converter(args.msg_module, args.msg_class)
    if args.json_to_binary:
      msg = conv.jsonFileToROS(args.json_file)
      conv.rosToBinaryFile(msg, args.bin_file)
    else:
      msg = conv.binaryFileToROS(args.bin_file)
      conv.rosToJsonFile(msg, args.json_file)

  except Exception as ex:
      print("Failure: " + str(ex))
