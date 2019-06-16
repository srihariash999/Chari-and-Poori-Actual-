

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"



#define OLED_RESET LED_BUILTIN  // For NodeMCU


Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
const char* ssid = "Redmi4";            
const char* pass = "namaste99";


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "srihariash"
#define AIO_KEY         "c640fbb3668c44ddbfd945347aa40170"

WiFiClient client;


Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/



Adafruit_MQTT_Subscribe charipoori = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/charipoori");




// ------------------------------------------------------------- Global Variable and constants ------------------------------------------------------------------------------

const uint8_t chariWidth    = 9;
const uint8_t chariHeight   = 16;
//const uint8_t revchariWidth  = 9;
//const uint8_t revchariHeight  = 16;
const uint8_t pooriWidth    = 7;
const uint8_t pooriHeight   = 5;

char chariXpos = 10;
char chariYpos = 10;
char pooriXpos = 60;
char pooriYpos = 40;


int flag = 0;



// -----------------------------------------------------------------Bitmap image - character arrays ------------------------------------------------------------------------------


const uint8_t PROGMEM chari[] = { 
  0x0c, 0x00, 0x36, 0x00, 0xfa, 0x00, 0x12, 0x00, 0x12, 0x00, 0x0c, 0x00, 0x08, 0x00, 0x1c, 0x00, 
  0x23, 0x80, 0x7c, 0x00, 0x5e, 0x00, 0x52, 0x00, 0x12, 0x00, 0x33, 0x00, 0x72, 0x80, 0x73, 0x80
};




//const uint8_t PROGMEM revchari[] = { 
//  0x00, 0x00, 0x1e, 0xa3, 0xe5, 0x9e, 0x06, 0x04, 0x04, 
//  0xc1, 0xa1, 0xfd, 0x06, 0x06, 0xfe, 0xe3, 0xce, 0x00
//};
const uint8_t PROGMEM poori[] = { 
 0x00, 0x7c, 0xc6, 0xc6, 0x7c
};


const unsigned char introchari [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0e, 
  0x00, 0x00, 0x00, 0x70, 0x3b, 0x20, 0x00, 0x00, 0x70, 0x20, 0x20, 0x7e, 0x00, 0x00, 0x60, 0x20, 
  0x03, 0x20, 0x00, 0x40, 0x20, 0x01, 0x2f, 0x70, 0x40, 0x3f, 0x1e, 0xa9, 0x70, 0x40, 0x31, 0x31, 
  0xb0, 0x70, 0x40, 0x21, 0x20, 0x90, 0x70, 0x40, 0x21, 0x20, 0xd0, 0x70, 0x21, 0x61, 0x3f, 0x50, 
  0x70, 0x1f, 0x41, 0x00, 0x50, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
};


const unsigned char introand [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0e, 0x00, 0x00, 0x00, 0x08, 0x31, 
  0x80, 0x00, 0x00, 0x08, 0x60, 0xc2, 0x30, 0x00, 0x08, 0x00, 0x42, 0xfe, 0x00, 0x08, 0x00, 0x43, 
  0x82, 0x03, 0xc8, 0x00, 0x23, 0x03, 0x06, 0x38, 0x7f, 0xe2, 0x01, 0x04, 0x08, 0x40, 0x22, 0x01, 
  0x0c, 0x08, 0x40, 0x22, 0x01, 0x08, 0x08, 0x40, 0x22, 0x01, 0x08, 0x08, 0x40, 0x22, 0x01, 0x08, 
  0x08, 0x7f, 0xe2, 0x01, 0x0f, 0xf8, 0x00, 0x22, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
};



const unsigned char intropoori [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x1e, 
  0x00, 0x00, 0x00, 0x28, 0x63, 0x00, 0x00, 0x00, 0x38, 0x41, 0x00, 0x00, 0x00, 0x00, 0x41, 0x00, 
  0x00, 0x00, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x43, 0x00, 0x3c, 0x2e, 0x38, 0x7e, 0x7c, 0x62, 
  0x33, 0x08, 0x40, 0x86, 0x42, 0x21, 0x18, 0x40, 0x82, 0x42, 0x20, 0x30, 0x40, 0x82, 0x42, 0x20, 
  0x60, 0x40, 0x82, 0x42, 0x20, 0x44, 0x40, 0x46, 0x42, 0x20, 0x6c, 0x40, 0x3c, 0x7e, 0x20, 0x38, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00
};


const uint8_t PROGMEM gameover[] = { 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xf0, 0x00, 0xff, 0x80, 0x80, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x38, 0x1c, 0x01, 0xe3, 0x80, 0xdf, 0x0f, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x20, 0x00, 0x03, 0x00, 0x80, 0xd9, 0x19, 0xc0, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x40, 0x00, 0x07, 0x00, 0x80, 0xb1, 0xe0, 0xc0, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x40, 0x00, 0x06, 0x00, 0xc0, 0xf0, 0xc0, 0xc0, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x40, 0x00, 0x04, 0x00, 0xc0, 0xe0, 0xc0, 0xc0, 0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x40, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xc0, 0xc0, 0x67, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xc0, 0xc0, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x00, 0x01, 0xfc, 0xc0, 0xe0, 0xc0, 0xc0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x00, 0x03, 0xff, 0xe0, 0xe0, 0xc0, 0xc0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x00, 0x03, 0x80, 0x40, 0xe0, 0x80, 0xc0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x81, 0xff, 0x83, 0x80, 0x60, 0xc0, 0x80, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x81, 0xff, 0x83, 0x80, 0x60, 0xc0, 0x80, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x18, 0x03, 0x80, 0x20, 0xc0, 0x80, 0xc0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0x10, 0x03, 0x00, 0x60, 0xc0, 0x80, 0xc0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xc0, 0x10, 0x03, 0x01, 0xe0, 0xc0, 0xc0, 0x40, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xe0, 0x10, 0x03, 0x03, 0xa0, 0xc0, 0xc0, 0x60, 0x30, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xff, 0x18, 0x03, 0xff, 0xb8, 0xc0, 0xc0, 0x60, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xff, 0xf0, 0x03, 0xf8, 0x00, 0x40, 0xc0, 0x40, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0xf0, 0x60, 0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xff, 0xb0, 0x03, 0x9f, 0x7f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x06, 0x0f, 0xb0, 0x06, 0x1c, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x0c, 0x00, 0xb8, 0x0e, 0x38, 0x01, 0x01, 0x7f, 0x00, 0x06, 0x01, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0x00, 0xf8, 0x0e, 0x38, 0x01, 0x01, 0x63, 0x80, 0x02, 0x01, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0x00, 0xdc, 0x0c, 0x30, 0x01, 0x01, 0x40, 0x80, 0x03, 0x01, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x10, 0x00, 0xdc, 0x0c, 0x30, 0x01, 0x81, 0x40, 0x80, 0x01, 0x01, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x10, 0x00, 0xdc, 0x0c, 0x3a, 0x01, 0x81, 0xc0, 0x00, 0x01, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x10, 0x00, 0xce, 0x1c, 0x3f, 0xff, 0x81, 0x80, 0x00, 0x01, 0x02, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0xce, 0x18, 0x38, 0x00, 0x01, 0x80, 0x00, 0x00, 0x82, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0xcf, 0x38, 0x38, 0x00, 0x01, 0x80, 0x00, 0x00, 0x82, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0xc7, 0x38, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x86, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0xc7, 0xb8, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x84, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0xc7, 0xf0, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0xc4, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x00, 0x81, 0xf0, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x64, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x30, 0x01, 0x81, 0xf0, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x2c, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x18, 0x01, 0x01, 0xe0, 0x30, 0x00, 0x01, 0x80, 0x00, 0x00, 0x28, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1c, 0x07, 0x01, 0xe0, 0x1f, 0x01, 0x81, 0x80, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0xe0, 0x0f, 0xff, 0xe1, 0x80, 0x00, 0x00, 0x30, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 0x01, 0xff, 0xe1, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};







// ---------------------------------------------------------------- The setup() routine   ------------------------------------------------------------------------------


void MQTT_connect();

void setup()
{

Serial.begin(115200);
WiFi.begin(ssid, pass);
 
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff & slider feed.

  mqtt.subscribe(&charipoori);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

   
    
  display.clearDisplay(); // Make sure the display is cleared
  
  display.setTextSize(1);
  display.setTextColor(WHITE);

       display.drawBitmap(0, 0, introchari, 40, 20, WHITE);
       
       display.display();
       delay(500);

       display.drawBitmap(40, 21, introand, 40, 20, WHITE);
       
       display.display();
       delay(500);
       
       display.drawBitmap(82, 41, intropoori, 40, 20, WHITE);
       
  
       display.display();
       
       delay(2000);

     display.clearDisplay();
     display.setCursor(0,32);
     display.print("Press any key to continue.....");

     display.display();



}




// ---------------------------------------------------------------------- Main infinite loop -----------------------------------------------------------------------------------------------




 
void loop()
{

 MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
 
    
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {

       display.clearDisplay();
       display.drawBitmap(chariXpos, chariYpos, chari, chariWidth, chariHeight, WHITE);
       display.drawBitmap(pooriXpos, pooriYpos, poori, pooriWidth, pooriHeight, WHITE);  
       display.display();   
     if (subscription == &charipoori) {
      
      if (strcmp((char *)charipoori.lastread, "5") == 0) {
        chariYpos -= 5;
     
      Serial.println("Chari moved UP");}

      else if (strcmp((char *)charipoori.lastread, "13") == 0) {
        chariYpos += 5;
     
      Serial.println("Chari moved DOWN ");}

      else if (strcmp((char *)charipoori.lastread, "8") == 0) {
        chariXpos -= 5;
     
      Serial.println("Chari moved LEFT ");}

      else if (strcmp((char *)charipoori.lastread, "10") == 0) {
        chariXpos += 5;
     
      Serial.println("Chari moved RIGHT ");}
      

    
    if(chariXpos == pooriXpos && (chariYpos == pooriYpos<-3 || chariYpos+6 >= pooriYpos+5)  )
    {
      display.clearDisplay();
      display.drawBitmap(0,0,gameover,128,64,WHITE);
      display.display();
      delay(3000);
       chariXpos = 10;
       chariYpos = 10;
       pooriXpos = 60;
       pooriYpos = 40;

    }

    
    
    
    }
  
  }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
