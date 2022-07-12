#define PANEL_RES_X 64
#define PANEL_RES_Y 32
#define NUM_ROWS 1
#define NUM_COLS 1
#define PANEL_CHAIN NUM_ROWS*NUM_COLS
#define SERPENT false
#define TOPDOWN false
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
MatrixPanel_I2S_DMA *dma_display = nullptr;
VirtualMatrixPanel  *virtualDisp = nullptr;
#include <Fonts/Font5x7.h>
#include <Fonts/Font3x5.h>
#include <Fonts/Picopixel.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/BigNumber.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#define f1 &Font5x78pt7b

// Waktu
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
#include <JadwalSholat.h>
#include <F1kM_Hisab.h>
#include <TimeLib.h>//menghitung hari berikutnya untuk perhitungan hijriah
//// DFPlayer
//#include "Arduino.h"
//#include <DFRobotDFPlayerMini.h>
//DFRobotDFPlayerMini myDFPlayer;


#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <LITTLEFS.h>
#include <ArduinoJson.h>

#include <SoftwareSerial.h>

//const char* ssid = "SII-Cikunir";
//const char* password = "admin.admin";
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

#include "Font05x7.h"
#include "Config.h"
#include "DFplayer.h"
#include "DF.h"
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

void setup() {
  Serial.begin(115200);
  //  Serial.println("setup selesai");
  pinMode(buzzer, OUTPUT);
  pinMode(tombol, INPUT);
  if (!LITTLEFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    //    Serial.println("LITTLEFS Mount Failed");
    return;
  }
//  DataDefault();
  readFileJWS(LITTLEFS, filejws);
  readFileAdmin(LITTLEFS, fileAdmin);
  readFileInfo(LITTLEFS, fileInfo);
  readFileAtur(LITTLEFS, fileAtur);
  bit_data = p_info.enable_info;

  Serial.printf("versi : %d", p_jws.versi);
  if(p_jws.versi<3){
//    DataDefault();
    readFileJWS(LITTLEFS, filejws);
  readFileAdmin(LITTLEFS, fileAdmin);
  readFileInfo(LITTLEFS, fileInfo);
  readFileAtur(LITTLEFS, fileAtur);
  bit_data = p_info.enable_info;
  }
//  setDF();
  setupDFplayer();
  mulaiRTC();
  BacaRTC();
  updateJWS();

  HUB75_I2S_CFG mxconfig(
    PANEL_RES_X,   // module width
    PANEL_RES_Y,   // module height
    PANEL_CHAIN    // chain length
  );
  mxconfig.double_buff = true;
  mxconfig.clkphase = false;
  if (NUM_ROWS <= 1) {
    Serial.println(F("There is no reason to use the VirtualDisplay class for a single horizontal chain and row!"));
  }
  dma_display = new MatrixPanel_I2S_DMA(mxconfig);
  dma_display->setBrightness8(p_atur[0]);
  if ( not dma_display->begin() )
    Serial.println("** !KABOOM! I2S memory allocation failed *****");

  virtualDisp = new VirtualMatrixPanel((*dma_display), NUM_ROWS, NUM_COLS, PANEL_RES_X, PANEL_RES_Y, SERPENT, TOPDOWN);
  lebar = virtualDisp->width();

  setup_websocket();
  
  lsKdp = kdp;
  virtualDisp->setTextColor(0B1111111111111111);
  LBul=rBul;
}

void loop() {
  ws.cleanupClients();
  if(!batas){
    //tanda terima data dari web
    if (jumlah_beep>0) {   
      if (millis() - time2 >= 500) {
        time2=millis();
        tndaBuzzer = false;
        jumlah_beep--;
      }
      digitalWrite(buzzer, jumlah_beep%2);
    }
//    BacaRTC();
    UpdateWaktu();
    kedip();
    virtualDisp->flipDMABuffer();
    
    virtualDisp->clearScreen();
    Disp_Main();
    cycle_info();
    Disp_Jam();

    //kirim waktu websocket
    if (LDet != rDet) {
      LDet = rDet;
      char z[8];
      sprintf(z, "%02d:%02d:%02d", rJam, rMen, rDet);
      notifyClients(String(z), "1");
      disableJumat();
    }
    if(LBul!=rBul){
      LBul=rBul;
      resetjumat(LITTLEFS, fileInfo);
    }
    runtarhim2();
  }
}
