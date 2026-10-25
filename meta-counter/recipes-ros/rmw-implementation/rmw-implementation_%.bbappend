# Zenoh вимкнено (ROS_WORLD_SKIP_GROUPS += "zenoh"), бо meta-zenoh не підключено.
# Використовуємо RMW за замовчуванням - Fast DDS.
ROS_BUILD_DEPENDS:remove = "rmw-zenoh-cpp"
ROS_BUILDTOOL_DEPENDS:remove = "rmw-zenoh-cpp-native"
ROS_EXPORT_DEPENDS:remove = "rmw-zenoh-cpp"
ROS_EXEC_DEPENDS:remove = "rmw-zenoh-cpp"
ROS_TEST_DEPENDS:remove = "rmw-zenoh-cpp"
