#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_srvs/srv/set_bool.hpp"

using namespace std::chrono_literals;

class CounterPublisher : public rclcpp::Node
{
public:
  CounterPublisher()
  : Node("counter_publisher"), count_(0), running_(true)
  {
    publisher_ = create_publisher<std_msgs::msg::Int32>("counter", 10);
    timer_ = create_wall_timer(1s, [this]() { on_timer(); });
    service_ = create_service<std_srvs::srv::SetBool>(
      "set_counting",
      [this](const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
             std::shared_ptr<std_srvs::srv::SetBool::Response> response) {
        on_set_counting(request, response);
      });
    RCLCPP_INFO(get_logger(), "Counter publisher started (counting: ON)");
  }

private:
  void on_timer()
  {
    if (!running_) {
      return;
    }
    std_msgs::msg::Int32 msg;
    msg.data = ++count_;
    RCLCPP_INFO(get_logger(), "Publishing: %d", msg.data);
    publisher_->publish(msg);
  }

  void on_set_counting(
    const std::shared_ptr<std_srvs::srv::SetBool::Request> request,
    std::shared_ptr<std_srvs::srv::SetBool::Response> response)
  {
    running_ = request->data;
    response->success = true;
    response->message = running_ ? "Counting started" : "Counting stopped";
    RCLCPP_INFO(get_logger(), "%s at %d", response->message.c_str(), count_);
  }

  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Service<std_srvs::srv::SetBool>::SharedPtr service_;
  int32_t count_;
  bool running_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CounterPublisher>());
  rclcpp::shutdown();
  return 0;
}
