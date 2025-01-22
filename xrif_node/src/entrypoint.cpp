#include "rclcpp/rclcpp.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  
  auto node = rclcpp::Node::make_shared("Dendrite_XRIF");

  RCLCPP_INFO(node->get_logger(), "Starting Dendrite");
  
  rclcpp::shutdown();
  return 0;
}
