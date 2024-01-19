# Cup Dispenser Documentation

This documentation focuses on the `CupDispenser` functionality implemented in `cupDispenser.cpp` and its integration into the main control program in `main.cpp`.

## cupDispenser.cpp

The `CupDispenser` class encapsulates the logic for dispensing cups using a GPIO pin on a Raspberry Pi. The primary purpose is to provide methods for initializing the Raspberry Pi, dispensing cups, and printing messages during the dispensing process.

### Class Methods

#### `dispense(int dispenserPin, int time)`

Dispenses a cup by activating the specified GPIO pin for the specified duration.

- Parameters:
  - `dispenserPin`: GPIO pin connected to the cup dispenser.
  - `time`: Duration for which the dispenserPin remains active.

#### `printStart()`

Prints a message indicating the start of the cup dispensing process.

#### `printEnd()`

Prints a message indicating the completion of the cup dispensing process.

## Integration in main.cpp

In the `main.cpp` file, the `CupDispenser` class is utilized to perform cup dispensing actions when the MQTT command 'x' is received.

### Integration Steps

1. **Include Header File:**
   - Ensure that the `cupDispenser.h` header file is included at the beginning of the `main.cpp` file.

2. **Instantiate `CupDispenser`:**
   - Create an instance of the `CupDispenser` class.

   ```cpp
   CupDispenser cupDispenser;
   ```

3. **Invoke `dispense` Method:**
   - Call the `dispense` method when the 'x' command is received.

   ```cpp
   // Dispense cup
   cupDispenser.dispense(DISPENSER_PIN, DISPENSER_TIME);
   ```

   - Adjust the GPIO pin (`DISPENSER_PIN`) and dispensing time (`DISPENSER_TIME`) based on the hardware configuration.
  
## Related Documentation

For additional information and documentation, refer to the following related documents:

- [Waterpump](../pi/waterpump.md)