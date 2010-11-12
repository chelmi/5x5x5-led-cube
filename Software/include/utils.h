#ifndef _UTILS_H
#define _UTILS_H

/* Internal macros */
#define DDR_NAME(PORT_ID) DDR ## PORT_ID
#define PORT_NAME(PORT_ID) PORT ## PORT_ID
#define PINREG_NAME(PORT_ID)  PIN ## PORT_ID
#define PIN_NAME(PORT_ID, PIN) P ## PORT_ID ## PIN

/* Sets pin direction
 * PORT_ID: the identifier of the port (B, C, D)
 * PIN: the pin number (0...7)
 */
#define PIN_OUT2(PORT_ID, PIN)  DDR_NAME(PORT_ID) |= _BV(PIN_NAME(PORT_ID, PIN))
#define PIN_IN2(PORT_ID, PIN)   DDR_NAME(PORT_ID) &= ~_BV(PIN_NAME(PORT_ID, PIN))

/* Enables pull-up resistor on an input pin
 * PORT_ID: the identifier of the port (B, C, D)
 * PIN: the pin number (0...7)
 */
#define PULL_UP2(PORT_ID, PIN)  PORT_NAME(PORT_ID) |= _BV(PIN_NAME(PORT_ID, PIN))

/* Sets pin value
 * PORT_ID: the identifier of the port (B, C, D)
 * PIN: the pin number (0...7)
 */
#define PIN_HIGH2(PORT_ID, PIN) PORT_NAME(PORT_ID) |= _BV(PIN_NAME(PORT_ID, PIN))
#define PIN_LOW2(PORT_ID, PIN)  PORT_NAME(PORT_ID) &= ~_BV(PIN_NAME(PORT_ID, PIN))
#define PIN_TOGGLE2(PORT_ID, PIN) PORT_NAME(PORT_ID) ^= _BV(PIN_NAME(PORT_ID, PIN))

/* Gets pin value
 * PORT_ID: the identifier of the port (B, C, D)
 * PIN: the pin number (0...7)
 */
#define PIN_VALUE2(PORT_ID, PIN) (PINREG_NAME(PORT_ID) & _BV(PIN_NAME(PORT_ID, PIN))) >> PIN
#define PIN_IS_LOW2(PORT_ID, PIN) (PINREG_NAME(PORT_ID) & _BV(PIN_NAME(PORT_ID, PIN))) == 0
#define PIN_IS_HIGH2(PORT_ID, PIN) (PINREG_NAME(PORT_ID) & _BV(PIN_NAME(PORT_ID, PIN))) != 0

/* Configures a pin. Usage:
 * The pin must have been declare like:
 * #define LED_PORT D
 * #define LED_PIN  4
 * (the LED is connected to PD4)
 * ID is the name of the pin (LED in this example).
 * ex. PIN_OUT(LED)
 */
#define PIN_OUT(ID) PIN_OUT2(ID ## _PORT, ID ## _PIN)
#define PIN_IN(ID) PIN_IN2(ID ## _PORT, ID ## _PIN)

/* Enables pull-up resistor on an input pin
 * PIN ID is the name of the pin
 */
#define PULL_UP(ID) PULL_UP2(ID ## _PORT, ID ## _PIN)

/* Sets pin value
 * PIN ID is the name of the pin
 */
#define PIN_HIGH(ID)   PIN_HIGH2(ID ## _PORT, ID ## _PIN)
#define PIN_LOW(ID)    PIN_LOW2(ID ## _PORT, ID ## _PIN)
#define PIN_TOGGLE(ID) PIN_TOGGLE2(ID ## _PORT, ID ## _PIN)

/* Gets pin value
 * PIN ID is the name of the pin
 */
#define PIN_VALUE(ID)   PIN_VALUE2(ID ## _PORT, ID ## _PIN)
#define PIN_IS_HIGH(ID) PIN_IS_HIGH2(ID ## _PORT, ID ## _PIN)
#define PIN_IS_LOW(ID)  PIN_IS_LOW2(ID ## _PORT, ID ## _PIN)

#endif
