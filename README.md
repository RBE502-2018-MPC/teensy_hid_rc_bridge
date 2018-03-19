# teensy_hid_rc_bridge
Bridge from a computer to the little RC car using a Teensy and RawHID protocol

The USB HID protocol was used intsead of the ROS Serial libraries, because
USB Interrupt type endpoints have better jitter characteristics than
USB Bulk type endpoints.  The jitter in the data matters in our particular
case, and the data being sent to the controller isn't complex anyways.

This code is designed to run on a Teensy 3.1 with two MCP4131 Digital
potentiometers.  The digital potentiometers replace the steering and
throttle inputs on the RC controller to send commands to the RC car.

NOTE: There is no safety code in here yet at all.  Nothing is preventing
the car from running away.

![Breadboard][docs/breadboard.jpg]
