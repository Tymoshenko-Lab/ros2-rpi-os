#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

class CounterSubscriber : public rclcpp::Node
{
public:
  CounterSubscriber()
  : Node("counter_subscriber")
  {
    subscription_ = create_subscription<std_msgs::msg::Int32>(
      "counter", 10,
      [this](const std_msgs::msg::Int32 & msg) { on_message(msg); });
    RCLCPP_INFO(get_logger(), "Counter subscriber started");
  }

private:
  void on_message(const std_msgs::msg::Int32 & msg)
  {
    RCLCPP_INFO(get_logger(), "Received: %d", msg.data);
  }

  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CounterSubscriber>());
  rclcpp::shutdown();
  return 0;
}
