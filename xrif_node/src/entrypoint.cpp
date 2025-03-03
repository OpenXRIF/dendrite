#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include "rclcpp/rclcpp.hpp"

#include "irobot_create_msgs/msg/interface_buttons.hpp"
#include "irobot_create_msgs/msg/lightring_leds.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
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

void query_synapse_api(const std::string& api_url, const std::string& json_message) {
    http_client client(U(api_url));

    json::value json_value = json::value::parse(U(json_message));

    http_request request(methods::POST);
    request.headers().set_content_type(U("application/json"));
    request.set_body(json_value);

    client.request(request).then([](http_response response) {
        if (response.status_code() == status_codes::OK) {
            return response.extract_json();
        }
        return pplx::task_from_result(json::value());
    }).then([](pplx::task<json::value> previous_task) {
        try {
            json::value const & v = previous_task.get();
            ucout << U("Response JSON: ") << v.serialize() << std::endl;
            if (v.has_field(U("xrif"))) {
                ucout << U("xrif: ") << v.at(U("xrif")).serialize() << std::endl;
            }
        } catch (http_exception const & e) {
            ucout << e.what() << std::endl;
        }
    }).wait();
}

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    
    // auto node = rclcpp::Node::make_shared("Dendrite_XRIF");
    auto node = rclcpp::spin(std::make_shared<TurtleBot4FirstNode>());

    RCLCPP_INFO(node->get_logger(), "Starting Dendrite");
    
    rclcpp::shutdown();
    return 0;
}
