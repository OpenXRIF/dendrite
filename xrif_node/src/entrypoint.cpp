#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

#include "irobot_create_msgs/msg/interface_buttons.hpp"
#include "irobot_create_msgs/msg/lightring_leds.hpp"

class TurtleBot4FirstNode: public rclcpp::Node {
    public:
        TurtleBot4FirstNode(): Node("turtlebot4_first_cpp_node") {
            // Subscribe to the /interface_buttons topic
            interface_buttons_subscriber_ =
                this->create_subscription<irobot_create_msgs::msg::InterfaceButtons>(
                "/interface_buttons",
                rclcpp::SensorDataQoS(),
                std::bind(&TurtleBot4FirstNode::interface_buttons_callback, this, std::placeholders::_1));

            // Create a publisher for the /cmd_lightring topic
            lightring_publisher_ = this->create_publisher<irobot_create_msgs::msg::LightringLeds>(
                "/cmd_lightring",
                rclcpp::SensorDataQoS());
        }

    private:
        // Interface buttons subscription callback
        void interface_buttons_callback(
            const irobot_create_msgs::msg::InterfaceButtons::SharedPtr create3_buttons_msg) {
            // Button 1 is pressed
            if (create3_buttons_msg->button_1.is_pressed) {
                RCLCPP_INFO(this->get_logger(), "Button 1 Pressed!");
            }
        }

        // Interface Button Subscriber
        rclcpp::Subscription<irobot_create_msgs::msg::InterfaceButtons>::SharedPtr interface_buttons_subscriber_;
        // Lightring Publisher
        rclcpp::Publisher<irobot_create_msgs::msg::LightringLeds>::SharedPtr lightring_publisher_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    
    // auto node = rclcpp::Node::make_shared("Dendrite_XRIF");
    auto node = rclcpp::spin(std::make_shared<TurtleBot4FirstNode>());

    RCLCPP_INFO(node->get_logger(), "Starting Dendrite");
    
    rclcpp::shutdown();
    return 0;
}
