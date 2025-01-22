from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package = 'dendrite_xrif',
            executable = 'dendrite_xrif_node',
            output = 'screen',
            emulate_tty= True),
])
