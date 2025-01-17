# Clearpath Turtlebot4

## UWaterloo Turtlebot
1. Clone turtlebot repo and start Docker Container

```sh
./turtlebot4/start.sh
```

2. Run VPN with Turtlebot ID

```sh
./turtlebot/vpn/vpn.sh <robot_id>
```

3. In a seperate terminal, open the container again and check ROS2 topics

```sh
ros2 topic list
```

4. ssh into the Turtlebot

```sh
ssh ubuntu@<raspberry_pi_ip_addr>
```

### Useful Commands

Run Rviz for visualization

```sh
rviz2
```

Reboot System and Drivers

```sh
sudo systemctl restart turtlebot4
reboot_base
journalctl -u turtlebot4
```

ROS2 lists

```
ros2 topic list
ros2 service list
ros2 node list
```

ROS2 Teleop

```sh
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

To run a service, run `ros2 service call <service_name> <service_type> <args>`
(use tab completion to see service type and args options)
