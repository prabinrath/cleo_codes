# Copyright 2016 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose
from geometry_msgs.msg import Twist
import math
import numpy as np

class TurtleCircleCommander(Node):
    def __init__(self):
        super().__init__('turtle_circle_commander')
        self.publisher_ = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.subscriber_ = self.create_subscription(Pose, '/turtle1/pose', self.subscriber_callback, 10)
        x_c, y_c, r = 6, 6, 2
        poly = 9 # sizes of polygon
        self.targets = [(x_c+r*math.cos(th),y_c+r*math.sin(th)) for th in np.linspace(0,2*math.pi,poly+1)]
        print(self.targets)
        self.i = 0        
    
    def angle_trunc(self,a):
        """This maps all angles to a domain of [-pi, pi]"""
        while a < 0.0:
            a += math.pi * 2
        return ((a + math.pi) % (math.pi * 2)) - math.pi

    def get_heading(self,turtle_position, target_position):
        """Returns the angle, in radians, between the target and turtle positions"""
        turtle_x, turtle_y = turtle_position
        target_x, target_y = target_position
        heading = math.atan2(target_y - turtle_y, target_x - turtle_x)
        heading = self.angle_trunc(heading)
        return heading

    def subscriber_callback(self, msg):
        cmd = Twist()
        target = self.targets[self.i]
        print('Target:',target, ' | Current:', (msg.x, msg.y, msg.theta))
        if abs(msg.x-target[0])<0.01 and abs(msg.y-target[1])<0.01:
            self.i = (self.i+1)%len(self.targets)
        target_heading = self.get_heading((msg.x,msg.y), (target[0],target[1]))
        heading_diff = target_heading - msg.theta
        if abs(heading_diff) > 0.01:
            cmd.linear.x = 0.0
            cmd.angular.z = heading_diff
        else:
            cmd.linear.x = 0.5
            cmd.angular.z = 0.0
        self.publisher_.publish(cmd)
    

def main(args=None):
    rclpy.init(args=args)
    node = TurtleCircleCommander()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
