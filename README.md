# smart-traffic-light-arduino
Adaptive Arduino-based Smart Traffic Light system using IR sensors to manage four-lane traffic efficiently.

# Smart Traffic Light Control System

This project uses an Arduino UNO and IR sensors to create an intelligent traffic light system that adapts signal timing based on real-time vehicle presence.

## Features
- Adaptive green light timing based on vehicle count
- Controls 4 traffic lanes using LEDs
- Real-time traffic data logging via Serial Monitor
- Low-cost and easy to build with basic electronics

## Hardware Components
- Arduino UNO
- IR Sensors × 4
- LEDs (Red, Yellow, Green × 4 lanes)
- Jumper Wires
- Breadboard
- Power Supply (USB or Battery)

## Software Stack
- Arduino IDE (Embedded C++)
- Serial Monitor for real-time data view
- (Optional) Python for traffic data analysis

## How it Works
IR sensors detect vehicles; Arduino adjusts green time based on traffic in each lane.

## Limitations
- Limited to IR detection range
- No emergency vehicle prioritization

## Future Work
- Add camera-based detection
- Integrate ML for predictive traffic timing

## Project Files
- smart_traffic_light.ino: Main Arduino sketch
- circuit_diagram.png: Connection diagram
- hardware_list.txt: Complete list of components

## License
This project is open-source under the MIT License.
