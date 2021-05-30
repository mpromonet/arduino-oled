/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_HMC5883_U.h>

Adafruit_MPU6050 mpu;

Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire);

void setup() {
  Serial.begin(115200);

  if (!mpu.begin()) {
    Serial.println("MPU init failed");
    while (1)
      yield();
  }
  mpu.setI2CBypass(true);
  mpu.enableSleep(false);
  Serial.println(F("Found a MPU-6050 sensor"));

  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println(F("MAG init failed"));
    while(1);
  }
  Serial.println(F("Found a HMC5883  sensor"));

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("Found a SSD1306  sensor"));

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Display Text
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);        
  display.setCursor(0,0);   
  display.print("GY-86");
  display.display();
  delay(2000);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  sensors_event_t event; 
  mag.getEvent(&event);  

  display.clearDisplay();
  display.setCursor(0, 0);

  Serial.print("Accelerometer ");
  Serial.print("X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" m/s^2, ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z, 1);
  Serial.println(" m/s^2");

  display.print("A: ");
  display.print(a.acceleration.x, 1);
  display.print(", ");
  display.print(a.acceleration.y, 1);
  display.print(", ");
  display.print(a.acceleration.z, 1);
  display.println("");

  Serial.print("Gyroscope ");
  Serial.print("X: ");
  Serial.print(g.gyro.x, 1);
  Serial.print(" rps, ");
  Serial.print("Y: ");
  Serial.print(g.gyro.y, 1);
  Serial.print(" rps, ");
  Serial.print("Z: ");
  Serial.print(g.gyro.z, 1);
  Serial.println(" rps");

  Serial.print("Temperature ");
  Serial.println(temp.temperature, 1);

  display.print("G: ");
  display.print(g.gyro.x, 1);
  display.print(", ");
  display.print(g.gyro.y, 1);
  display.print(", ");
  display.print(g.gyro.z, 1);
  display.println("");

  display.print("T: ");
  display.println(temp.temperature, 1);

  Serial.print("Magnetometer ");
  Serial.print("X: ");
  Serial.print(event.magnetic.x, 1);
  Serial.print(" rps, ");
  Serial.print("Y: ");
  Serial.print(event.magnetic.y, 1);
  Serial.print(" rps, ");
  Serial.print("Z: ");
  Serial.print(event.magnetic.z, 1);
  Serial.println(" rps");

  display.print("M: ");
  display.print(event.magnetic.x, 1);
  display.print(", ");
  display.print(event.magnetic.y, 1);
  display.print(", ");
  display.print(event.magnetic.z, 1);
  display.println("");

  display.display();
  delay(100);  
}

