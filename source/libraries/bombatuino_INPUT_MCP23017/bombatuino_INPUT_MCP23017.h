/**
 * @file bombatuino_INPUT_MCP23017.h
 * 
 * @author Lukas Haubaum (lukas@haubaum.de)
 * 
 * @date February, 2013
 * 
 * @brief arduino library for reading inputs from MCP23017 port Expander
 * 
 * library is for specialiced use: all I/O ports are used as digital inputs with internal pullup resistor active, values are stored and a callback function is called, when a value changes.
 * ATTETION: Wire.h must be included in sketch #include <Wire.h>
 * 	
 * */
#ifndef bombatuino_INPUT_MCP23017_h
#define bombatuino_INPUT_MCP23017_h

#if !defined(CallbackFunction)
/**
 * callback function
 * 
 * @param address
 * @param pin
 * @param value
 */
typedef void (*CallbackFunction)(int,int,int);
#endif

class INPUT_MCP23017
{
	public:
		/**
		 * initalize the class, should be called in setup() function
		 * 
		 * @param hardware address (0-7)
		 * @param callback function
		 */
		void begin(uint8_t addr,CallbackFunction cbF);		
		/**
		 * read values and call callback function on change, should be called in loop()
		 */
		void loop(void);		
		/**
		 * get value of specific pin (0-15)
		 * 
		 * @param pin
		 * @return value of pin
		 */
		int getSpecificValue(uint8_t pin);
	private:
		uint8_t _addr; /**< hardware address (0-7) */ 
		int _value[16]; /**< read values */ 
		CallbackFunction _callbackFunction; /**< callback function */ 
};

#define MCP23017_ADDRESS 0x20 /**< hardware address */

/**
 * registers of MCP23017 (BANK = 0)
 * 
 * default is 0 except for I/O DIRECTION REGISTERS
 * 
 * for detailed description see http://ww1.microchip.com/downloads/en/DeviceDoc/21952b.pdf
 * 
 * */
#define MCP23017_IODIR_A 0x00 		/**< I/O DIRECTION REGISTER PORT A - Controls the direction of the data I/O. */
#define MCP23017_IODIR_B 0x01 		/**< I/O DIRECTION REGISTER PORT B - Controls the direction of the data I/O. */
#define MCP23017_IPOL_A 0x02 		/**<  INPUT POLARITY REGISTER PORT A - This register allows the user to configure the polarity on the corresponding GPIO port bits. */
#define MCP23017_IPOL_B 0x03 		/**< INPUT POLARITY REGISTER PORT B - This register allows the user to configure the polarity on the corresponding GPIO port bits. */
#define MCP23017_GPINTEN_A 0x04 	/**< INTERRUPT-ON-CHANGE CONTROL REGISTER PORT A - The GPINTEN register controls the interrupt-on-change feature for each pin. */
#define MCP23017_GPINTEN_B 0x05 	/**< INTERRUPT-ON-CHANGE CONTROL REGISTER PORT B - The GPINTEN register controls the interrupt-on-change feature for each pin. */
#define MCP23017_DEFVAL_A 0x06 		/**< DEFAULT COMPARE REGISTER FOR INTERRUPT-ON-CHANGE PORT A - The default comparison value is configured in the DEFVAL register. */
#define MCP23017_DEFVAL_B 0x07 		/**< DEFAULT COMPARE REGISTER FOR INTERRUPT-ON-CHANGE PORT B - The default comparison value is configured in the DEFVAL register.. */
#define MCP23017_INTCON_A 0x08 		/**< INTERRUPT CONTROL REGISTER PORT A - The INTCON register controls how the associated pin value is compared for the interrupt-on-change feature. */
#define MCP23017_INTCON_B 0x09 		/**< INTERRUPT CONTROL REGISTER PORT B - The INTCON register controls how the associated pin value is compared for the interrupt-on-change feature.*/
#define MCP23017_IOCON_A 0x0A 		/**<  CONFIGURATION REGISTER - The IOCON register contains several bits for configuring the device. BANK/MIRROR/SEQOP/DISSLW/HAEN/ODR/INTPOL/— */
#define MCP23017_IOCON_B 0x0B 		/**<  CONFIGURATION REGISTER - The IOCON register contains several bits for configuring the device. BANK/MIRROR/SEQOP/DISSLW/HAEN/ODR/INTPOL/— */
#define MCP23017_GPPU_A 0x0C 		/**< PULL-UP RESISTOR CONFIGURATION REGISTER PORT A - The GPPU register controls the pull-up resistors for the port pins. */
#define MCP23017_GPPU_B 0x0D 		/**< PULL-UP RESISTOR CONFIGURATION REGISTER PORT B - The GPPU register controls the pull-up resistors for the port pins. */
#define MCP23017_INTF_A 0x0E 		/**< INTERRUPT FLAG REGISTER PORT A - The INTF register reflects the interrupt condition on the port pins of any pin that is enabled for interrupts via the GPINTEN register. */
#define MCP23017_INTF_B 0x0F 		/**< INTERRUPT FLAG REGISTER PORT B - The INTF register reflects the interrupt condition on the port pins of any pin that is enabled for interrupts via the GPINTEN register. */
#define MCP23017_INTCAP_A 0x10 		/**< INTERRUPT CAPTURE REGISTER PORT A - The INTCAP register captures the GPIO port value at the time the interrupt occurred. */
#define MCP23017_INTCAP_B 0x11 		/**< INTERRUPT CAPTURE REGISTER PORT B - The INTCAP register captures the GPIO port value at the time the interrupt occurred. */
#define MCP23017_GPIO_A 0x12  		/**< PORT REGISTER PORT A - The GPIO register reflects the value on the port. */
#define MCP23017_GPIO_B 0x13 		/**< PORT REGISTER PORT B - The GPIO register reflects the value on the port. */
#define MCP23017_OLAT_A 0x14 		/**< OUTPUT LATCH REGISTER PORT A - The OLAT register provides access to the output latches. */
#define MCP23017_OLAT_B 0x15 		/**< OUTPUT LATCH REGISTER PORT B - The OLAT register provides access to the output latches. */


#endif
