//--------------------- created by: Babak Stars -----------------------------------------
#define SCR_WD   240
#define SCR_HT   240
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define GREEN 0x07E0
#define RED 0xF800
#define BLACK 0x0000

#if (__STM32F1__) // bluepill
#define TFT_DC  PA1
#define TFT_RST PA0
//#include <Arduino_ST7789_STM.h>
#else
#define TFT_DC  7
#define TFT_RST 8
#include <Arduino_ST7789_Fast.h>
//#include <Arduino_ST7789.h>
#endif

Adafruit_MPU6050 mpu;
Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST);
int analog;

void setup() {
  Serial.begin(9600);
  Serial.println(F("IPS 240x240 ST7789"));
  //tft.reset();
  //tft.init(SCR_WD, SCR_HT);
  tft.begin();
  tft.fillScreen(BLACK);
  
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(150, 70);
  tft.print("m/s");
  tft.setCursor(140, 150);
  tft.print("Feet/min");
  tft.setTextSize(1);
  tft.setCursor(10, 120);
  tft.println("0");

  tft.setCursor(120, 230);
  tft.setTextColor(RED);
  tft.println("TCAS system test OK!");
  tft.setTextColor(WHITE);
  back();
  
  //tft.fillTriangle(120,115,80,40,120,125,GREEN);
  //tft.fillCircle(120,120,10,RED);
  //int a = 65;
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  //Serial.println("");
  delay(100);

}

void loop() {
  //analog = map(analogRead(A0), 0, 1023, -90, 90);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  analog = -1 * (a.acceleration.z  - 11.00);
  showing();
}
void back() {
  for(int a = 0 ; a < 100 ; a++)
  {
    int x = cos(radians(a)) * 119;
    int y = sin(radians(a)) * 119;

    int X = 119 - x;
    int Y = 119 - y;

    tft.setCursor(X, Y);
    tft.println(".");

    if(a ==  20)
    {
      tft.setCursor(X+10, Y);
      tft.println("5");
    }
    if(a  ==  40)
    {
      tft.setCursor(X+10, Y);
      tft.println("10");
    }
    if(a  ==  60)
    {
      tft.setCursor(X+15, Y+5);
      tft.println("20");
    }
  }

  for(int a = 0 ; a > -100 ; a--)
  {
    int x = cos(radians(a)) * 119;
    int y = sin(radians(a)) * 119;

    int X = 119 - x;
    int Y = 119 - y;

    tft.setCursor(X, Y);
    tft.println(".");

    if(a ==  -20)
    {
      tft.setCursor(X+10, Y);
      tft.println("-5");
    }
    if(a  ==  -40)
    {
      tft.setCursor(X+10, Y);
      tft.println("-10");
    }
    if(a  ==  -60)
    {
      tft.setCursor(X+15, Y+5);
      tft.println("-20");
    }
  }

}
  void showing()
  {
    int a = analog*3;
    int x = cos(radians(a)) * 119;
    int y = sin(radians(a)) * 119;

    int X = 119 - x;
    int Y = 119 - y;

    //X(20~119)
    //Y(119~20)

    //X + 20 => 0 [ X+(20*cos(radians(a))) ]
    //Y + 20 => 0 [ Y+(20*sin(radians(a))) ]

   tft.fillTriangle(120+(5*sin(radians(a))),120-(5*cos(radians(a))),X+(25*cos(radians(a))),Y+(25*sin(radians(a))),120-(5*sin(radians(a))),120+(5*cos(radians(a))),GREEN);
   //tft.fillCircle(120,120,10,RED);
    int Xp = X;
    int Yp = Y;
    showNumbers();
    
    delay(12);
    tft.fillTriangle(120+(5*sin(radians(a))),120-(5*cos(radians(a))),X+(25*cos(radians(a))),Y+(25*sin(radians(a))),120-(5*sin(radians(a))),120+(5*cos(radians(a))),BLACK);
    //tft.fillCircle(120,120,10,RED);
    tft.fillRect(150,50,50,15,BLACK);
    tft.fillRect(150,120,80,15,BLACK);
  }
void showNumbers(){

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(150, 50);
  tft.print(analog);
  
  tft.setCursor(150, 120);
  tft.print(analog*196);
  

}
