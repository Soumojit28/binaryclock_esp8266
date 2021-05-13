/*
 * Binary Clock With ESP8266 and
 * WS2812b RGB Leds
 * Code By - Soumojit Ash
 * soumojitash#gmail.com
 */
//Hello123


#include <FastLED.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define NUM_LEDS 20
#define DATA_PIN 3

CRGB leds[NUM_LEDS];
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "1.pool.ntp.org", 19800, 60000);
const char *ssid     = "********";
const char *password = "*******";
  static uint8_t hue = 0;
int h,h1,h2;
int m,m1,m2;
int s,s1,s2;
int l0,l1,l2,l3;

void setled(int i,int d, int col)
{ l0=0+i;
  l1=1+i;
  l2=2+i;
  l3=3+i;
  col=col+hue;

  switch(d)
    {
      case 0:
        leds[l3] = CRGB::Black;
        leds[l2] = CRGB::Black;
        leds[l1] = CRGB::Black;
        leds[l0] = CRGB::Black;
        break;
      case 1:
        leds[l3] = CRGB::Black;
        leds[l2] = CRGB::Black;
        leds[l1] = CRGB::Black;
        leds[l0] = CHSV(col, 255, 255);
      break;
      case 2:
        leds[l3] = CRGB::Black;
        leds[l1] = CRGB::Black;
        leds[l1] = CHSV(col, 255, 255);
        leds[l0] = CRGB::Black;
        break;
      case 3:
        leds[l3] = CRGB::Black;
        leds[l2] = CRGB::Black;
        leds[l1] = CHSV(col, 255, 255);
        leds[l0] = CHSV(col, 255, 255);
        break;
      case 4:
        leds[l3] = CRGB::Black;
        leds[l2] = CHSV(col, 255, 255);
        leds[l1] = CRGB::Black;
        leds[l0] = CRGB::Black;
        break;
      case 5:
        leds[l3] = CRGB::Black;
        leds[l2] = CHSV(col, 255, 255);
        leds[l1] = CRGB::Black;
        leds[l0] = CHSV(col, 255, 255);
        break;
      case 6:
        leds[l3] = CRGB::Black;
        leds[l2] = CHSV(col, 255, 255);
        leds[l1] = CHSV(col, 255, 255);
        leds[l0] = CRGB::Black;
        break;
      case 7:
        leds[l3] = CRGB::Black;
        leds[l2] = CHSV(col, 255, 255);
        leds[l1] = CHSV(col, 255, 255);
        leds[l0] = CHSV(col, 255, 255);
        break;
      case 8:
        leds[l3] = CHSV(col, 255, 255);
        leds[l2] = CRGB::Black;
        leds[l1] = CRGB::Black;
        leds[l0] = CRGB::Black;
        break;
      case 9:
        leds[l3] = CHSV(col, 255, 255);
        leds[l2] = CRGB::Black;
        leds[l1] = CRGB::Black;
        leds[l0] = CHSV(col, 255, 255);
        break;

}}

void setup () {
 
 Serial.begin(115200);
FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
 WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();

}
void loop () {

  if(hue==255)
  {
    h=0;
  }
   timeClient.update();
   h= timeClient.getHours();
   m= timeClient.getMinutes();
   s= timeClient.getSeconds();
   Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.println(s);
  

   if(h>12)
   {
    h=h-12;
   }
    h1=h/10;
    h2=h%10;
    m1=m/10;
    m2=m%10;
    s1=s/10;
    s2=s%10;

    setled(0,s2,0);
    setled(4,s1,0);
    setled(7,m2,85);
    setled(11,m1,85);
    setled(14,h2,170);
    setled(18,h1,170);



   FastLED.show();
       hue++;
      delay(50);
}
