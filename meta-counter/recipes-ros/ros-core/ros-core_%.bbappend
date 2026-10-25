# launch-testing-ros пропущено разом із zenoh (потрібен лише для тестів),
# тому прибираємо його з метапакета ros-core.
ROS_EXEC_DEPENDS:remove = "launch-testing-ros"
