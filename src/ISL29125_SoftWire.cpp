/******************************************************************************
SparkFunISL29125.cpp
Core implementation file for the ISL29125 RGB sensor library.
Jordan McConnell @ SparkFun Electronics
25 Mar 2014
https://github.com/sparkfun/ISL29125_Breakout

This file implements the functions of the ISL29125_SOFT sensor class as well as
providing documentation on what each function does.

Developed/Tested with:
Arduino Uno
Arduino IDE 1.0.5

This code is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given. 
******************************************************************************/

#include "ISL29125_SoftWire.h"

// Constructor - Creates sensor object and sets I2C address
ISL29125_SOFT::ISL29125_SOFT(uint8_t addr) 
{
  _addr = addr;
}

// Destructor - Deletes sensor object
ISL29125_SOFT::~ISL29125_SOFT()
{

}

// Initialize - returns true if successful
// Starts Wire/I2C Communication
// Verifies sensor is there by checking its device ID
// Resets all registers/configurations to factory default
// Sets configuration registers for the common use case
bool ISL29125_SOFT::init(uint8_t SDA, uint8_t SCL)
{
  bool ret = true;
  uint8_t data = 0x00;
  
  // Start I2C
  wire = SoftwareWire(SDA, SCL);
  wire.begin();
  
  // Check device ID
  data = read8(DEVICE_ID);
  if (data != 0x7D)
  {
    ret &= false;
  }
  
  // Reset registers
  ret &= reset();
  
  // Set to RGB mode, 10k lux, and high IR compensation
  ret &= config(CFG1_MODE_RGB | CFG1_10KLUX, CFG2_IR_ADJUST_HIGH, CFG_DEFAULT);
  
  return ret;
}

// Reset all registers - returns true if successful
bool ISL29125_SOFT::reset()
{
  uint8_t data = 0x00;
  // Reset registers
  write8(DEVICE_ID, 0x46);
  // Check reset
  data = read8(CONFIG_1);
  data |= read8(CONFIG_2);
  data |= read8(CONFIG_3);
  data |= read8(STATUS);
  if (data != 0x00)
  {
    return false;
  }
  return true;
}

// Setup Configuration registers (three registers) - returns true if successful
// Use CONFIG1 variables from ISL29125_SOFT.h for first parameter config1, CONFIG2 for config2, 3 for 3
// Use CFG_DEFAULT for default configuration for that register
bool ISL29125_SOFT::config(uint8_t config1, uint8_t config2, uint8_t config3)
{
  bool ret = true;
  uint8_t data = 0x00;
  
  // Set 1st configuration register
  write8(CONFIG_1, config1);
  // Set 2nd configuration register
  write8(CONFIG_2, config2);
  // Set 3rd configuration register
  write8(CONFIG_3, config3);
  
  // Check if configurations were set correctly
  data = read8(CONFIG_1);
  if (data != config1)
  {
    ret &= false;
  }
  data = read8(CONFIG_2);
  if (data != config2)
  {
    ret &= false;
  }
  data = read8(CONFIG_3);
  if (data != config3)
  {
    ret &= false;
  }
  return ret;
}

// Sets upper threshold value for triggering interrupts
void ISL29125_SOFT::setUpperThreshold(uint16_t data)
{
  write16(THRESHOLD_HL, data);
}

// Sets lower threshold value for triggering interrupts
void ISL29125_SOFT::setLowerThreshold(uint16_t data)
{
  write16(THRESHOLD_LL, data);
}

// Check what the upper threshold is, 0xFFFF by default
uint16_t ISL29125_SOFT::readUpperThreshold()
{
  return read16(THRESHOLD_HL);
}

// Check what the upper threshold is, 0x0000 by default
uint16_t ISL29125_SOFT::readLowerThreshold()
{
  return read16(THRESHOLD_LL);
}

// Read the latest Sensor ADC reading for the color Red
uint16_t ISL29125_SOFT::readRed()
{
  return read16(RED_L);
}

// Read the latest Sensor ADC reading for the color Green
uint16_t ISL29125_SOFT::readGreen()
{
  return read16(GREEN_L);
}

// Read the latest Sensor ADC reading for the color Blue
uint16_t ISL29125_SOFT::readBlue()
{
  return read16(BLUE_L);
}

// Check status flag register that allows for checking for interrupts, brownouts, and ADC conversion completions
uint8_t ISL29125_SOFT::readStatus()
{
  return read8(STATUS);
}

// Generic I2C read register (single byte)
uint8_t ISL29125_SOFT::read8(uint8_t reg)
{
  wire.beginTransmission(_addr);
  wire.write(reg);
  wire.endTransmission();
  wire.beginTransmission(_addr);
  wire.requestFrom(_addr,(uint8_t)1);
  uint8_t data = wire.read();
  wire.endTransmission();
  
  return data;
}

// Generic I2C write data to register (single byte)
void ISL29125_SOFT::write8(uint8_t reg, uint8_t data)
{
  wire.beginTransmission(_addr);
  wire.write(reg);
  wire.write(data);
  wire.endTransmission();
  
  return;
}

// Generic I2C read registers (two bytes, LSB first)
uint16_t ISL29125_SOFT::read16(uint8_t reg)
{
  uint16_t data = 0x0000;

  wire.beginTransmission(_addr);
  wire.write(reg);
  wire.endTransmission();
  
  wire.beginTransmission(_addr);
  wire.requestFrom(_addr, (uint8_t)2); // request 2 bytes of data
  data = wire.read();
  data |= (wire.read() << 8);
  wire.endTransmission();

  return data;
}

// Generic I2C write data to registers (two bytes, LSB first)
void ISL29125_SOFT::write16(uint8_t reg, uint16_t data)
{
  wire.beginTransmission(_addr);
  wire.write(reg);
  wire.write(data);
  wire.write(data>>8); 
  wire.endTransmission();
}