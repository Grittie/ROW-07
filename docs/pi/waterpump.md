# Water Pump Documentation

This documentation focuses on the `Waterpump` functionality implemented in `waterpump.cpp` and its integration into the main control program in `main.cpp`.

## waterpump.cpp

The `Waterpump` class encapsulates the logic for controlling a water pump using a GPIO pin on a Raspberry Pi. It provides methods for initializing the Raspberry Pi, extruding water, and printing messages during the extrusion process.

### Class Methods

#### `extrude(int in, int time)`

Extrudes water by activating the specified GPIO pin for the specified duration.

- Parameters:
  - `in`: GPIO pin connected to the water pump.
  - `time`: Duration for which the GPIO pin remains active during water extrusion.

#### `printStart()`

Prints a message indicating the start of the water extrusion process.

#### `printEnd()`

Prints a message indicating the completion of the water extrusion process.

## Integration in main.cpp

In the `main.cpp` file, the `Waterpump` class is utilized to perform water extrusion actions when the MQTT command 'x' is received.

### Integration Steps

1. **Include Header File:**
   - Ensure that the `waterpump.h` header file is included at the beginning of the `main.cpp` file.

2. **Instantiate `Waterpump`:**
   - Create an instance of the `Waterpump` class.

   ```cpp
   Waterpump waterpump;
   ```

3. **Invoke `extrude` Method:**
   - Call the `extrude` method when the 'x' command is received.

   ```cpp
   // Extrude water
   waterpump.extrude(WATERPUMP_PIN, EXTRUSION_TIME);
   ```

   - Adjust the GPIO pin (`WATERPUMP_PIN`) and extrusion time (`EXTRUSION_TIME`) based on the hardware configuration.

## Related Documentation

For additional information and documentation, refer to the following related documents:

- [Cupdispenser](../pi/cupdispenser.md)