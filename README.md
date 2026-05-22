# Ultrasonic Radar Scanner (Arduino)

A servo-based radar system that sweeps an ultrasonic sensor across a
150° arc, measures distance at each angle, and streams the data over
Serial for real-time visualization.

## How it works

A servo motor rotates continuously back and forth between 15° and 165°.
At each degree of rotation, an HC-SR04 ultrasonic sensor fires a pulse
and listens for the echo. The time-of-flight is converted to distance
using the speed of sound (340 m/s), and the angle + distance pair is
sent over Serial in a simple comma-separated format.

The Serial output is designed to be picked up by a Processing sketch
(or any serial reader) to render a classic radar-style display.

## Hardware

- Arduino (Uno or compatible)
- HC-SR04 ultrasonic distance sensor
- SG90 servo motor (or compatible)
- 5V power supply (servo draws more current than USB can reliably supply)
- Connecting wires / breadboard

## Wiring

| Component         | Arduino Pin |
|-------------------|-------------|
| Ultrasonic TRIG   | D10         |
| Ultrasonic ECHO   | D11         |
| Servo signal      | D12         |
| Servo VCC         | 5V          |
| Servo GND         | GND         |

> **Note:** If the servo causes the Arduino to reset or behave
> erratically, power it from an external 5V supply and share only
> the ground with the Arduino.

## Serial data format

Data is streamed at **9600 baud**.
