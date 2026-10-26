# ros2-rpi-os

Власна ОС для Raspberry Pi на Yocto Project 6.0 (Wrynose) з ROS 2 Lyrical Luth
та демонстраційними нодами: лічильник (publisher), subscriber і service для
запуску/зупинки лічильника.

## Структура

```
ros2-rpi-os/
├── kas/
│   ├── base.yml        # спільна конфігурація: шари, образ, local.conf
│   ├── rpi4.yml        # MACHINE = raspberrypi4-64
│   └── rpi5.yml        # MACHINE = raspberrypi5 (заділ на майбутнє)
├── layers/             # зовнішні шари (git submodules)
│   ├── bitbake                 (2.18)
│   ├── openembedded-core       (wrynose)
│   ├── meta-yocto              (wrynose)
│   ├── meta-openembedded       (wrynose)
│   ├── meta-raspberrypi        (wrynose)
│   └── meta-ros                (wrynose)
├── meta-counter/       # власний meta-layer
│   ├── conf/layer.conf
│   ├── recipes-core/images/counter-image.bb
│   └── recipes-ros/
│       ├── counter-pkg/counter-pkg_0.1.0.bb
│       ├── rmw-implementation/   # bbappend: вимкнення zenoh
│       ├── ros-core/             # bbappend: вимкнення zenoh
│       └── ament-cmake-ros/      # bbappend: вимкнення zenoh
└── ros2_ws/src/counter_pkg/      # код нод (C++, ament_cmake)
```

## Ноди

| Нода | Роль |
| --- | --- |
| `counter_publisher` | публікує лічильник 1, 2, 3… у topic `/counter` (`std_msgs/Int32`) раз на секунду; service `/set_counting` (`std_srvs/SetBool`) запускає/зупиняє лічильник |
| `counter_subscriber` | підписується на `/counter` і виводить значення |
| `counter_control` | service client: `counter_control start` / `counter_control stop` |

## Збірка та перевірка на ПК (Ubuntu 26.04, ROS 2 Lyrical)

```bash
cd ros2_ws
colcon build --packages-select counter_pkg
source install/setup.bash
ros2 run counter_pkg counter_publisher      # вікно 1
ros2 run counter_pkg counter_subscriber     # вікно 2
ros2 run counter_pkg counter_control stop   # вікно 3
ros2 run counter_pkg counter_control start
```

## Збірка образу ОС

```bash
git clone --recurse-submodules git@github.com:Tymoshenko-Lab/ros2-rpi-os.git
cd ros2-rpi-os
pipx install kas
kas build kas/rpi4.yml        # Raspberry Pi 4
# kas build kas/rpi5.yml      # Raspberry Pi 5
```

Результат: `build/tmp/deploy/images/raspberrypi4-64/counter-image-raspberrypi4-64.rootfs.wic.bz2`.

### Особливості конфігурації

- RMW за замовчуванням — Fast DDS. Zenoh вимкнено (`ROS_WORLD_SKIP_GROUPS += "zenoh"`),
  бо він потребує окремого шару meta-zenoh; залежності від нього прибрано через bbappend у `meta-counter`.
- `git://` для git.yoctoproject.org / git.openembedded.org перенаправлено на `https://` через `PREMIRRORS`.
- `INIT_MANAGER = "systemd"`, мережа через systemd-networkd (DHCP на eth0).
- Вхід `root` без пароля та SSH-сервер увімкнено лише для навчального стенду.

## Запуск на платі

Записати образ на SD-карту (Raspberry Pi Imager → Use custom, або `bmaptool`),
завантажити плату, підключитися по SSH як `root`:

```bash
. /opt/ros/lyrical/setup.sh
ros2 run counter_pkg counter_publisher
ros2 run counter_pkg counter_subscriber
ros2 run counter_pkg counter_control stop
ros2 run counter_pkg counter_control start
```

## Готовий образ

Див. розділ **Releases** цього репозиторію.
