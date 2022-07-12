#include "font/Font6x7.h"
#include "font/Font5x6a.h"
#include "font/huruf6x7.h"
#include "font/Font3x5.h"
#include "font/Font4x6ali.h"
#include "font/kecil3x6.h"
#include "font/ElektronMartArabic5x6.h"
#include "font/Font4x6b.h"

// Waktu
#include <SPI.h>
#include <FS.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <JadwalSholat.h>
#include <F1kM_Hisab.h>
#include <TimeLib.h>
#include <HJS589.h>

#define DISPLAYS_WIDE 1 
#define DISPLAYS_HIGH 1
HJS589 Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

void ICACHE_RAM_ATTR refresh() { 
    Disp.refresh();
    timer0_write(ESP.getCycleCount() + 40000);  
}

void Disp_init() {
  Disp.start();
  timer0_attachInterrupt(refresh);
  timer0_write(ESP.getCycleCount() + 40000);
  Disp.clear();
}

#include <fonts/ElektronMart5x6.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/ElektronMart6x12.h>
#include <fonts/ElektronMart6x16.h>
#include <fonts/ElektronMartArabic5x6.h>
#include <fonts/ElektronMartArabic5x6.h>
#include <fonts/ElektronMartArabic6x16.h>
int pTeks;
uint32_t time1, time2;
int lebar;
uint8_t buzzer = 32;
uint8_t tombol = 34;

uint16_t bit_data = 0B1100001000000001;

//LittleFS
struct parameterJWS {
  int versi;
  int is; // iqomah subuh
  int id;
  int ia;
  int im;
  int ii;
  int durasiAdzan;
  int f_ws;//faktor penambah waktu sholat
  int durasikutbah;
  int f_hjr;
  bool dispiqmh;
  bool dispimsyak;
  bool ringimsyak;
  bool disppuasa;
  bool dispdhuha;
  bool dispterbit;
  bool dispsplash;

}; parameterJWS p_jws;

struct parameterAdmin {
  double lat;
  double lon;
  int z_w; //zona waktu
  int hilal;
  String ssid;
  String p_ssid;
  String ap;
  String p_ap;
  int batastombol;
}; parameterAdmin p_admin;

struct parameterInfo {
  String info1;
  String info2;
  String info3;
  String info4;
  String info5;
  String info6;
  String info7;
  String info8;
  String info9;
  String info10;
  String jumat[6]={"","","","","","Menunggu Bulan Baru"};
  String masjid;
  uint16_t enable_info;
}; parameterInfo p_info;

int p_atur[2];

#include "Config.h"
//#include "DFplayer.h"
//#include "DF.h"
#include "RTC.h"
#include "Ali.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
#include "FSconfig.h"
#include "Hijriah.h"
#include "JWS.h"
#include "Puasa.h"
#include "WebPage.h"
#include "Disp_1panel.h"
#include "WebSocket.h"

bool Disp_mode=true;

void setup() {
  Serial.begin(115200);
  
  pinMode(buzzer, OUTPUT);
  pinMode(tombol, INPUT);
  
  if(analogRead(A0)>=200){
    Disp_mode = false;
  }
  
  mulaiRTC();
  BacaRTC();
  updateJWS();
  
  if (!LittleFS.begin()) {
        Serial.println("LittleFS Mount Failed");
    return;
  }
//  DataDefault();
  readFileJWS(LittleFS, filejws);
  readFileAdmin(LittleFS, fileAdmin);
  readFileInfo(LittleFS, fileInfo);
  readFileAtur(LittleFS, fileAtur);
  bit_data = p_info.enable_info;

  Serial.printf("versi : %d", p_jws.versi);
  if(p_jws.versi<3){
//    DataDefault();
    readFileJWS(LittleFS, filejws);
    readFileAdmin(LittleFS, fileAdmin);
    readFileInfo(LittleFS, fileInfo);
    readFileAtur(LittleFS, fileAtur);
    bit_data = p_info.enable_info;
  }
  //mode=========================================================
  if(Disp_mode){
    Disp_init();
    lebar = Disp.width();
    Disp.setBrightness(p_atur[0]);
  }else{
    setup_websocket();
  }
  
//  setDF();
//  setupDFplayer();
  lsKdp = kdp;
  LBul=rBul;
  Serial.println("selesai");
  delay(5000);
}

void loop() {
  UpdateWaktu();
  kedip();
  //untuk display====================================
  if(Disp_mode){
    cycle_info();
  }
  //untuk web========================================
  else{
    ws.cleanupClients();
    if (LDet != rDet) {
      LDet = rDet;
      char z[8];
      sprintf(z, "%02d:%02d:%02d", rJam, rMen, rDet);
      notifyClients(String(z), "1");
      disableJumat();
      dtk5++;
      if(dtk5>=10){
        dtk5=0;
      }
    }
  }
  //tanda terima data dari web
  if (jumlah_beep>0) {   
    if (millis() - time2 >= 500) {
      time2=millis();
      tndaBuzzer = false;
      jumlah_beep--;
    }
    digitalWrite(buzzer, jumlah_beep%2);
  }
    if(LBul!=rBul){
      LBul=rBul;
      resetjumat(LittleFS, fileInfo);
    }
//    runtarhim2();
}
