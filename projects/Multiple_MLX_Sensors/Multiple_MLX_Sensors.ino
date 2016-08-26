/**
 * Multiple MLX Sensors
 * by David Stoewe
 * This code is based on Six_MLX906114 by William Winters 12JUN2015 (http://minimal.engineering/archives/18)
 * Returns the temperature in Celcius from multiple MLX90614 sensors.
 **/
 
#include <i2cmaster.h>
 
// Shift the address 1 bit right, the
// I²Cmaster library only needs the 7 most
// significant bits for the address.
int mlx1address = 0x1B<<1; 
int mlx2address = 0x1C<<1;
int mlx3address = 0x1D<<1; 
 
void setup()
{
  Serial.begin(9600);
  i2c_init();
  
  PORTC = (1 << PORTC4) | (1 << PORTC5);
}
 
void loop()
{
  float temp1 = temperatureCelcius(mlx1address);
  float temp2 = temperatureCelcius(mlx2address);
  float temp3 = temperatureCelcius(mlx3address);
  
  Serial.print("C1:");
  Serial.println(temp1);
  Serial.print("C2:");
  Serial.println(temp2);
  Serial.print("C3:");
  Serial.println(temp3);
  Serial.println("######");
  
  delay(1000);
}

float temperatureCelcius(int address)
{
  int device = address;
  int dataLow = 0;
  int dataHigh = 0;
  int pec = 0;
 
  // Write
  i2c_start_wait(device+I2C_WRITE);
  i2c_write(0x07);
 
  // Read
  i2c_rep_start(device+I2C_READ);
  dataLow = i2c_readAck();       // Read 1 byte and then send ack.
  dataHigh = i2c_readAck();      // Read 1 byte and then send ack.
  pec = i2c_readNak();
  i2c_stop();
 
  // Scaling factor for the MLX90614
  double temperatureFactor = 0.02;
  double temperatureData = 0x0000;
 
  // This masks off the error bit of the high byte
  // Then moves it left 8 bits and adds the low byte.
  temperatureData = (double)(((dataHigh & 0x007F) << 8) + dataLow);
  temperatureData = (temperatureData * temperatureFactor)-0.01;
  
  //Convert Kelvin to Celcius
  float celcius = temperatureData - 273.15;
  
  // Return temperature in Celcius.
  return celcius;
}
