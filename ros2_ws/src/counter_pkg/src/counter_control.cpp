#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto args = rclcpp::remove_ros_arguments(argc, argv);
  auto node = rclcpp::Node::make_shared("counter_control");

  if (args.size() != 2 || (args[1] != "start" && args[1] != "stop")) {
    RCLCPP_ERROR(node->get_logger(), "Usage: counter_control start|stop");
    rclcpp::shutdown();
    return 1;
  }

  auto client = node->create_client<std_srvs::srv::SetBool>("set_counting");
  if (!client->wait_for_service(5s)) {
    RCLCPP_ERROR(node->get_logger(), "Service /set_counting not available");
    rclcpp::shutdown();
    return 1;
  }

  auto request = std::make_shared<std_srvs::srv::SetBool::Request>();
  request->data = (args[1] == "start");

  auto future = client->async_send_request(request);
  if (rclcpp::spin_until_future_complete(node, future, 5s) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    auto response = future.get();
    RCLCPP_INFO(node->get_logger(), "Response: success=%s, message='%s'",
      response->success ? "true" : "false", response->message.c_str());
  } else {
    RCLCPP_ERROR(node->get_logger(), "Service call failed");
    rclcpp::shutdown();
    return 1;
  }

  rclcpp::shutdown();
  return 0;
}
