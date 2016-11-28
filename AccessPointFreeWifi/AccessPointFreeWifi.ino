#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h> //This library you can add via Include Library > Manage Library > 
LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String responseHTML = ""
                      "<!DOCTYPE html><html><head><title>Free WIFI</title></head><body>"
                      "<body bgcolor='black'><p style='text-align: center;'><span style='font-size:48px;'><span style='color:#AFEEEE;'>Now...<br></span></span></p><p style='text-align: center;'><span style='font-size:48px;'><span style='color:#AFEEEE;'>you have been&nbsp;<br></span></span></p><p style='text-align: center;'><span style='font-size:72px;'><span style='color:#FF0000;'>HACKED...!</span></span></p></p></body></html>";

void setup() {
  lcd.begin();

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("FREE WIFI");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();

  lcd.setCursor(0,0);
  lcd.print("Free Wifi"); // Start Print text to Line 1

  lcd.setCursor(0,1);
  lcd.print("connect"); // Start Print text to Line 1
    lcd.setBacklight(HIGH);
    delay(500);
    lcd.setBacklight(LOW);
    delay(500);  // Nothing Absolutely Nothing!
}
//<body bgcolor='black'><p style='text-align: center;'><span style='font-size:48px;'><span style='color:#AFEEEE;'>Now...</span></span></p><p style='text-align: center;'><span style='font-size:48px;'><span style='color:#AFEEEE;'>you have been&nbsp;</span></span></p><p style='text-align: center;'><span style='font-size:72px;'><span style='color:#FF0000;'>HACKED...!</span></span></p>




