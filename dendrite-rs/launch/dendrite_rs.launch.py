from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package = 'dendrite-rs',
            executable = 'dendrite_rs_node',
            output = 'screen',
            emulate_tty= True),
])
