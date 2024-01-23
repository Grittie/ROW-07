# Motorcontroller / Wheels documentation

This document contains information about the `MotorController` functionality implemented in `wheels.cpp` and its integration into `main.cpp`.
All files pertaining to the `MotorController` can be found in `src/WheelEncoder`.

## wheels.cpp

The `Wheels` class contains the functions for controlling the movement of the bot. Using an unsigned char array written to the `MotorController`
The class contains 5 very similar functions, none of the functions take any parameters.
Every method contains an array of unsigned char's in the form of a `uint8_t` array.
Starting from left to right, the values in the array pertain to;
`Amount of bits`, `high bit right`, `low bit right`, `direction right`, `high bit left`, `low bit left` and `direction left`.
The `Amount of bits` is always 7 as you are sending a high bit, low bit and direction for both wheels.
The high and low bit make up the speed of the wheel together, for example a high bit of 0A and a low bit of FF come together to make 0AFF which translates to 2815 in decimal.

### Class Methods

#### `forward`

Continually move the bot forward, by telling both wheels to move forward at the same speed.

#### `backward`

Continually move the bot backward, by telling both wheels to move backward at the same speed.

#### `left`

Continually spin the bot to the left, by telling the right wheels to go forward whilst the left wheels go backwards at the same speed.

#### `right`

Continually spin the bot to the right, by telling the left wheels to go forward whilst the right wheels go backwards athe same speed.

#### `stop`

Stop the bot in place, through writing the value of 0 to all bits movement is stopped.

## Integration in main.cpp

in the `main.cpp` file, the `Wheels` class is utilized to control the bot remotely using different `MQTT` commands;
'f' for forward, 'b' for backwards, 'l' for left, 'r' for right and 's' to stop.

### Integration Steps

1. **Include Header File**
    - Make sure that the `wheels.h` header file is included at the beginning of the `main.cpp` file.

2. **instantiate `Wheels`:**
    - Create an instance of the `Wheels` class.

    ```cpp
    Wheels wheels;
    ```

3. **invoking the different methods:**
    - Call the move method (`forward`, `backward`, `left`, `right` or `stop`)when the associated `MQTT` message is received.

    ```cpp
    case 'f':
        wheels.forward();
        break;
    ```

