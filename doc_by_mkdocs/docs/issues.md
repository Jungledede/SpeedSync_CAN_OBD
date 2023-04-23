# Issue I got

## Dependance of code

Redefinition issue for `gpio.h` and `mcp2518fd_can.h` for the struc/enum about the GPIO state. I have commented the line the CAN lib, since i trust more intel/arduino for the config of the GPIO. Also, and the main factore here, it is an enum in both files. If the code in the lib always use the keyword/label and never the value of the enum, it is 100% the same final result and 100% invisible for the final usage.

gpio.h, line 38:

```cpp
/*!
 * GPIO types
 */
typedef enum {
    GPIO_INPUT,      /*!< Configure GPIO pin as input */
    GPIO_OUTPUT,     /*!< Configure GPIO pin as output */
    GPIO_INTERRUPT   /*!< Configure GPIO pin as interrupt */
} GPIO_TYPE;
```

and mcp2518fd_can_dfs.h, line 669:

```cpp
//! GPIO Pin Directions
typedef enum { GPIO_OUTPUT, GPIO_INPUT } GPIO_PIN_DIRECTION;
```

## Access right under linux

2 points:

* Need to add the curent user in the dialout list
* Need to do some stuff for the udev rules

https://forum.arduino.cc/t/error-timed-out-waiting-for-arduino-101-on-dev-ttyacm0/463154/4

``` bash
curl -sL https://raw.githubusercontent.com/01org/corelibs-arduino101/master/scripts/create_dfu_udev_rule | sudo -E bash -
```