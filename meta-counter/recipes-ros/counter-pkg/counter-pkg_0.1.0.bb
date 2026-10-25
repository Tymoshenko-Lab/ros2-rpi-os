SUMMARY = "ROS 2 counter: publisher, subscriber and start/stop service"
AUTHOR = "Oleksandr Tymoshenko"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

# Код береться з ros2_ws/src цього ж репозиторію
FILESEXTRAPATHS:prepend := "${THISDIR}/../../../ros2_ws/src:"
SRC_URI = "file://counter_pkg"
S = "${UNPACKDIR}/counter_pkg"

ROS_CN = "counter_pkg"
ROS_BPN = "counter_pkg"

# Залежності з package.xml (у Yocto "_" замінюється на "-")
ROS_BUILD_DEPENDS = "rclcpp std-msgs std-srvs"
ROS_BUILDTOOL_DEPENDS = "ament-cmake-native"
ROS_EXEC_DEPENDS = "rclcpp std-msgs std-srvs"

DEPENDS = "${ROS_BUILD_DEPENDS} ${ROS_BUILDTOOL_DEPENDS}"
RDEPENDS:${PN} += "${ROS_EXEC_DEPENDS}"

ROS_BUILD_TYPE = "ament_cmake"
inherit ros_distro_${ROS_DISTRO}
inherit ros_${ROS_BUILD_TYPE}
