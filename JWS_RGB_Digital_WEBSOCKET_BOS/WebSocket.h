IPAddress local_ip(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress netmask(255, 255, 255, 0);

bool batas=false;

void notifyClients(String x, String y) {
  String pesan = y + x + "#";
  ws.textAll(pesan);
}

void sendJWS() {
  String pesan;
  char out[20];
  String hari = String(namaHari[rHar]);
  String bulan = String(namaBulan[rBul]);
  sprintf(out, "%s,%02d %s %d", hari, rTgl, bulan, rTah);
  pesan = String(out);
  for (int i = 0; i <= 7; i++) {
    sprintf(out, ";%02d:%02d:%02d", stimeInt[i][0], stimeInt[i][1], stimeInt[i][2]);
    pesan += String(out);
  }
  char outt[12];
  sprintf(outt, ";%d:%d:%02d", rBul, rTah, rTgl);
  pesan+=String(outt);
  //  Serial.println(pesan);
  notifyClients(pesan, "2");
}

void dTeks(){
  String pesan="";
  for(int i=0;i<10;i++){
//    pesan+=String(dInfo[i]);
    if(i!=9){
      pesan+=";";
    }
  }
//  notifyClients(pesan, "5");
}

void kirimdata(fs::FS &fs, const char * path, String x) {
  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    //      Serial.println("- failed to open file for reading");
    return;
  }
  String pesan = file.readString();
  //  Serial.println(buf.get());
  //  Serial.println(pesan);
  notifyClients(pesan, x);
}

int keInt(String& x, String y) {
  String a = x.substring(0, x.indexOf(y));
  int b = a.toInt();
  x = x.substring(x.indexOf(y)+1);
  return b;
}
void handleWaktu(String x) {
  uint16_t tahun = keInt(x, "-");
  uint8_t bulan = keInt(x, "-");
  uint8_t tgl = keInt(x, ",");
  uint8_t jam = keInt(x, ":");
  uint8_t menit = keInt(x, ":");
  uint8_t detik = x.toInt();
  Rtc.SetDateTime(RtcDateTime(tahun, bulan, tgl, jam, menit, detik));
  BacaRTC();
  updateJWS();
  TanggalHijriah();
}

void handleText(String x) {
  gantiInfo(LITTLEFS, fileInfo, x);
}

void handleAtur(String x) {
  File file = LITTLEFS.open(fileAtur);
  String a = x.substring(0,1);
  String b = x.substring(1);
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[2];
  String pesan = file.readString();
  hasil[0] = parsing(pesan);
  hasil[1] = pesan;
  hasil[a.toInt()]=b;
  if(a=="0"){
    p_atur[0]             = hasil[0].toInt();
    dma_display->setBrightness8(p_atur[0]);
  }else{
    p_atur[1]             = hasil[1].toInt();
    myDFPlayer.volume(p_atur[1]);
//    Serial.println(String(p_atur[1]+100));
  }
  pesan="";
  for(int i=0;i<2;i++){
    pesan+=hasil[i];
    if(i!=1){
      pesan+="*";
    }
  }
  file.close();
  writeFile(LITTLEFS, fileAtur, pesan.c_str());
  readFileAtur(LITTLEFS, fileAtur);
}

void handleJWS(String x) {
  x = String(p_jws.versi)+"*"+x;
  writeFile(LITTLEFS, filejws, x.c_str());
  readFileJWS(LITTLEFS, filejws);
}

void handleAdmin(String x) {
  writeFile(LITTLEFS, fileAdmin, x.c_str());
  readFileAdmin(LITTLEFS, fileAdmin);
  updateJWS();
}

void handleDtext(String x){
   String a = x.substring(0, x.indexOf("="));
  int b = a.toInt();
  String c = x.substring(x.indexOf("=")+1);
//   Serial.println(b);
//   dInfo[b]=(c=="true");
   uint16_t buff = p_info.enable_info;
   bitWrite(buff, b, (c=="true"));
   change_enable(LITTLEFS, fileInfo, buff);
}

void handleWebSocketMessage(void *arg, unsigned char *data, size_t len) {
  batas=true;
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    //    Serial.print(data);
    char in[512];
    sprintf(in, "%s", data);
    if (String(in).substring(0, 1) == "#") {
      String a = String(in).substring(1, 2);
      String b = String(in).substring(3);
      b = b.substring(0, b.indexOf(";"));
//      Serial.println(String(in));
//      Serial.println(a);
//      Serial.println(b);
      switch (a.toInt()) {
        case 0:
          handleAdmin(b);
          batas=false;
          ESP.restart();
          break;
        case 1:
          handleWaktu(b);
          batas=false;
          sendJWS();
          break;
        case 2:
          handleText(b);
          batas=false;
          kirimdata(LITTLEFS, fileInfo, "4");
          break;
        case 3:
          handleJWS(b);
          batas=false;
          break;
        case 4:
          handleAtur(b);
          batas=false;
          break;
        case 5:
          handleDtext(b);
          batas=false;
          break;
        case 6:
          cycle=0;
          iqmh=false;
          batas=false;
          break;
        case 7:
          ESP.restart();
          batas=false;
          break;
        default:
          batas=false;
          break;
      }
      buzz(1);
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, unsigned char *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      //      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      sendJWS();
      kirimdata(LITTLEFS, fileInfo, "4");
      kirimdata(LITTLEFS, filejws, "3");
      kirimdata(LITTLEFS, fileAdmin, "0");
      dTeks();
      break;
    case WS_EVT_DISCONNECT:
      //      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var) {
  return String();
}

void setup_websocket() {
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  int a = (p_admin.ssid).length();
  int b = (p_admin.p_ssid).length();
  char c[a+1];
  char d[b+1];
  (p_admin.ssid).toCharArray(c,a+1);
  (p_admin.p_ssid).toCharArray(d,b+1);
  WiFi.begin(c, d);
  unsigned long st = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
        Serial.println("Connecting to WiFi..");
    if (millis() - st > 10000) {
      break;
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
//    Serial.print("MAC: ");
//    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    String ip = WiFi.localIP().toString();
    Serial.println(ip);
  } else {
    WiFi.mode(WIFI_AP);
    a = (p_admin.ap).length()+1;
    b = (p_admin.p_ap).length()+1;
    char e[a+1];
    char f[b+1];
    (p_admin.ap).toCharArray(e,a+1);
    (p_admin.p_ap).toCharArray(f,b+1);
    WiFi.softAPConfig(local_ip, gateway, netmask);
    WiFi.softAP(e, f);
//    Serial.print("MAC: ");
//    Serial.println(WiFi.macAddress());
    Serial.print("IP: ");
    Serial.println(local_ip);
  }

  initWebSocket();

  // Route for root / web page
  server.on("/admin", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", admin_html, processor);
  });
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  AsyncElegantOTA.begin(&server);
  // Start server
  server.begin();
}
