SUMMARY = "Raspberry Pi image with ROS 2 Lyrical and counter nodes"
LICENSE = "MIT"

inherit core-image

# SSH-сервер і вхід root без пароля (лише для навчального стенду)
IMAGE_FEATURES += "ssh-server-openssh allow-empty-password empty-root-password allow-root-login"

IMAGE_INSTALL:append = " \
    ros-core \
    counter-pkg \
"
