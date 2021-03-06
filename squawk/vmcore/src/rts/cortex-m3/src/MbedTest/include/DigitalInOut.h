/* mbed Microcontroller Library - DigitalInOut
 * Copyright (c) 2006-2009 ARM Limited. All rights reserved.
 * sford
 */ 
 
#ifndef MBED_DIGITALINOUT_H
#define MBED_DIGITALINOUT_H

#include "platform.h"
#include "PinNames.h"
#include "PeripheralNames.h"
#include "Base.h"

namespace mbed {

/* Class: DigitalInOut
 *  A digital input/output, used for setting or reading a bi-directional pin
 */
class DigitalInOut : public Base {

public:

    /* Constructor: DigitalInOut
     *  Create a DigitalInOut connected to the specified pin
     *
     * Variables:
     *  pin - DigitalInOut pin to connect to
     */
    DigitalInOut(PinName pin, const char* name = NULL);

    /* Function: write
     *  Set the output, specified as 0 or 1 (int)
     *
     * Variables:
     *  value - An integer specifying the pin output value, 
     *      0 for logical 0 and 1 (or any other non-zero value) for logical 1 
     */
    void write(int value) {
        if(value) {
            _gpio->FIOSET = _mask;
        } else {
            _gpio->FIOCLR = _mask;
        }
    }

    /* Function: read
     *  Return the output setting, represented as 0 or 1 (int)
     *
     * Variables:
     *  returns - An integer representing the output setting of the pin if it is an output, 
     *      or read the input if set as an input
     */
    int read() {
        return ((_gpio->FIOPIN & _mask) ? 1 : 0);
    }


    /* Function: output
     *  Set as an output
     */
    void output();

    /* Function: input
     *  Set as an input
     */
    void input();

    /* Function: mode
     *  Set the input pin mode
     *
     * Variables:
     *  mode - PullUp, PullDown, PullNone, OpenDrain
     */
    void mode(PinMode pull);
    
#ifdef MBED_OPERATORS
    /* Function: operator=
     *  A shorthand for <write>
     */
    DigitalInOut& operator= (int value) {
        write(value);
        return *this;
    }

    DigitalInOut& operator= (DigitalInOut& rhs) {
        write(rhs.read());
        return *this;
    }

    /* Function: operator int()
     *  A shorthand for <read>
     */
    operator int() {
        return read();
    }
#endif

#ifdef MBED_RPC
    virtual const struct rpc_method *get_rpc_methods();
    static struct rpc_class *get_rpc_class();
#endif

protected:

    PinName             _pin;
    LPC_GPIO_TypeDef    *_gpio;
    uint32_t            _mask;

};

} // namespace mbed 

#endif 
