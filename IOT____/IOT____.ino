#include <Debug.h>
#include <JSN270.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


#define SSID      "601"    // your wifi network SSID
#define KEY       "sealab2018"    // your wifi network password
#define AUTH       "WPA2"     // your wifi network security (NONE, WEP, WPA, WPA2)
#define USE_DHCP_IP 1

#if !USE_DHCP_IP
#define MY_IP          "192.168.1.133"
#define SUBNET         "255.255.255.0"
#define GATEWAY        "192.168.1.254"
#endif

#define HOST_IP        "74,125,232,128"  // 여기서 미리 서버 설정해주기
#define REMOTE_PORT    80
#define PROTOCOL       "TCP"

SoftwareSerial mySerial(3, 2); // RX, TX

JSN270 JSN270(&mySerial);

void setup() {
  // put your setup code here, to run once:
char c;
  String hostname;
  char hostip[32];

  mySerial.begin(9600);
  Serial.begin(9600);

  Serial.println("--------- JSN270 Web Client Test --------");

  // wait for initilization of JSN270
  delay(5000);
  //JSN270.reset();
  delay(1000);

  //JSN270.prompt();
  JSN270.sendCommand("at+ver\r");
  delay(5);
  while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
    Serial.print((char)c);
  }
  delay(1000);

#if USE_DHCP_IP
  JSN270.dynamicIP();
#else
  JSN270.staticIP(MY_IP, SUBNET, GATEWAY);
#endif    
    
  if (JSN270.join(SSID, KEY, AUTH)) {
    Serial.println("WiFi connect to " SSID);
  }
  else {
    Serial.println("Failed WiFi connect to " SSID);
    Serial.println("Restart System");

    return;
  }
  delay(1000);

  JSN270.sendCommand("at+wstat\r");
  delay(5);
  while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
    Serial.print((char)c);
  }
  delay(1000);        

  JSN270.sendCommand("at+nstat\r");
  delay(5);
  while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
    Serial.print((char)c);
  }
  delay(1000);

  
}

void loop() {
  // put your main code here, to run repeatedly:

}
