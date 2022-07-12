int8_t jumlah_beep = 0;
bool type = true;
bool tndaBuzzer = false;
uint8_t cycle=0;
int tmpilJdwal = 1;
uint8_t dtk3=0;
uint8_t dtk5=0;
uint16_t text_speed=30;
int width = Disp.width();

String tampil_waktu[]={"WAKTU", "ADZAN", "WAKTU", "WAKTU", "ADZAN", "ADZAN", "ADZAN", "ADZAN"};

void buzz(int8_t n){
  time2 = millis();
  jumlah_beep=(n*2)-1;
}

void drawMasjid(int x, int y) { //dibuat di dotmatrixtool.com 16x8 row major, big endian
  static const uint8_t masjid[] PROGMEM =
  {
    15, 8,
    0x01, 0x02, 0x43, 0x8a, 0xe7, 0xc4, 0xef, 0xee, 0xaf, 0xea, 0xe7, 0xce, 0xbf, 0xfa, 0xff, 0xfe
  };
  Disp.drawBitmap(x, y, masjid);
}

void jamNormal(uint8_t x, uint8_t y) {
  char buff[6];
  Disp.setFont(Font6x7);
  if (kdp) {
    sprintf(buff, "%02d;%02d", rJam, rMen);
  }else {
    sprintf(buff, "%02d|%02d", rJam, rMen);
  }
  Disp.drawText(x, y, buff);
}

void Disp_Azzan(int8_t sholat) {
  static uint8_t    det;
  static uint8_t    x;
  static uint8_t    s; // 0=in, 1=out
  static uint32_t   lsRn;
  uint32_t          Tmr = millis();
  char              msg[6];
  static bool       scroll;
  static uint8_t    lsDtk;
  char Msg[8];
  Disp.setFont(Font6x7);
  sprintf(Msg, "%s", namaWaktuSholat[sholat]);
  int selisih = int(Disp.width() - Disp.textWidth(Msg));
  if (selisih < 0) {
    scroll = true;
    selisih -= 2;
  }else {
    scroll = false;
  }
  if (scroll) { //penanda
    if ((Tmr - lsRn) > 100){
      if (s == 0 and x < (-selisih)) {
        lsRn = Tmr;
        x++;
        Disp.clear();
      }
      if (s == 1 and x > 0) {
        lsRn = Tmr;
        x--;
        Disp.clear();
      }
    }
    if ((Tmr - lsRn) > 500 and x == (-selisih)) {
      s = 1;
    }
    if ((Tmr - lsRn) > 500 and x == 0 and s == 1) {
      s = 0;
    }
    Disp.drawText(1 - x, 9, Msg);
  }else {
    uint8_t center = selisih / 2;
    Disp.drawText(center, 9, Msg);
  }
  Disp.setFont(Font4x6b);
  sprintf(msg, "%02s", tampil_waktu[sholat]);
  uint8_t center = int((Disp.width() - Disp.textWidth(msg)) / 2);
  if(kdp) Disp.drawText(center, 0, msg);
  Disp.drawRect(3, 7, 28, 7); // garis doang
  if (lsDtk != rDet) {
    lsDtk = rDet;
    det++;
  }
}

void tampilIqomah(){
  static bool lKdp=kdp;
  static int8_t i_menit = timer_iqomah();
  static int8_t i_detik = 0;
  char Msg[8];
  sprintf(Msg, "%s", "IQOMAH");
  Disp.setFont(Font4x6b);
  uint8_t center = int((Disp.width() - Disp.textWidth(Msg)) / 2);
  if(kdp) Disp.drawText(center, 0, Msg);
  char buff[6];
  sprintf(buff, "%02d;%02d", i_menit, i_detik);
  Disp.setFont(Font6x7);
  Disp.drawText(1, 9, buff);
  if(lKdp!=kdp){
    lKdp=kdp;
    if(!lKdp)return;
    i_detik--;
    if(i_detik<0){
      i_menit--;
      if(i_menit<0){
        cycle++;
        iqmh = false;
        return;
      }
      i_detik=59;
    }
  }
}

void tekanTombol(uint8_t& cycl){
  static bool state = false;
  bool out=digitalRead(tombol);
//  Serial.println(out);
  if(out){
    state=HIGH;
  }
  if(state){
    if(!out){
      if(!iqmh){
        iqmh=true;
//        tarhim = false;
        cycl++;
        buzz(1);
      }
      state=LOW;
    }
  }
}

void sebelumSholat(String pesan, uint16_t y){
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 30;
  static uint32_t x;
  jamNormal(1, 1);
  //  int width = Disp.width();
  Disp.setFont(huruf6x7);
  int fullScroll = Disp.textWidth(pesan.c_str()) + width;
  if (cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      //      tmpjws = 0;
      cycle += 1;
    }
    Disp.drawText(width - x, y, pesan.c_str());
  }
}

void Disp_Info(String pesan, uint16_t y) {
  if(!bitRead(bit_data, cycle-3)){
    cycle++;
    return;
  }
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 30;
  static uint32_t x;
  jamNormal(1, 1);
  //  int width = Disp.width();
  Disp.setFont(huruf6x7);
  int fullScroll = Disp.textWidth(pesan.c_str()) + width;
  if (cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      //      tmpjws = 0;
      cycle += 1;
    }
    Disp.drawText(width - x, y, pesan.c_str());
  }
}

void info_puasa(uint16_t y){
  static bool rst=true;
  static uint8_t i_p=0;
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 30;
  static uint32_t x;
  if(!p_jws.disppuasa){
    cycle++;
    return;
  }
  if(rst){
    i_p = check_puasa();
    Serial.println(i_p);
    if(i_p==0){
      cycle++;
      rst = true;
      return;
    }
    rst = false;
  }
  jamNormal(1, 1);
  Disp.setFont(huruf6x7);
  int fullScroll = Disp.textWidth(namaPuasa[i_p-1]) + width;
  if (cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      cycle += 1;
      rst = true;
    }
    Disp.drawText(width - x, y, namaPuasa[i_p-1]);
  }
}

void Disp_Main() {
  static int    y = 0;
  static uint8_t    s; // 0=in, 1=out
  static uint32_t   lsRn;
  static uint8_t    sNum;
  uint32_t          Tmr = millis();
  if (sNum == 0 and !p_jws.dispimsyak) sNum = 1;
  if (sNum == 2) sNum = 3;
  if (sNum == 3 and !p_jws.dispdhuha) sNum = 4;
  if ((Tmr - lsRn) > 30){
    if (s == 0 and y < 26) {
      lsRn = Tmr;
      y++;
      Disp.clear();
    }
    if (s == 1 and y > 0) {
      lsRn = Tmr;
      y--;
      Disp.clear();
    }
  }
  if ((Tmr - lsRn) > 2000 and y == 26) {
    s = 1;
  }
  char buffJ[6];
  char buffN[4];
  char buff[8];
  sprintf(buffN, "%02s", namaSholat[sNum]);
  sprintf(buffJ, "%02i:%02i", stimeInt[sNum][0], stimeInt[sNum][1]);
  if (kdp) {
    sprintf(buff, "%02d:%02d", rJam, rMen);
  }else {
    sprintf(buff, "%02d|%02d", rJam, rMen);
  }
  int   tw = Disp.textWidth((String)buffJ);
  int   c = int((width - tw) / 2);
  Disp.setFont(Font3x5);
  Disp.drawText(y-25, 0, buffN);
  Disp.drawText(15, -2, buff);
  Disp.setFont(Font4x6ali);
  Disp.drawText(y-25, 8, buffJ);
  Disp.drawFilledRect(0, 1, 13, 1, 1); // garis doang
  Disp.drawFilledRect(15, 7, 31, 7, 1);
  if (y == 0 and s == 1) {
    s = 0;
    if (sNum < 7) {
      sNum++;
    } else {
      sNum = 0;
      cycle+=1;
      Disp.clear();
    }
  }
}


void Disp_Jam() {
  static uint8_t    y;
  static uint8_t    s; // 0=in, 1=out
  static uint32_t   lsRn;
  uint32_t          Tmr = millis();
  char buffdet[3];
  if ((Tmr - lsRn) > 100){
    if (s == 0 and y < 8) {
      lsRn = Tmr;
      y++;
      Disp.clear();
    }
    if (s == 1 and y > 0 and !jumat) {
//    if (s == 1 and y > 0) {
      lsRn = Tmr;  //waktu khotbah akan menunjukan waktu saja
      y--;
      Disp.clear();
    }
  }
  if ((Tmr - lsRn) > 10000 and y == 8) {
    lsRn = Tmr;
    if (!jumat) { //waktu khotbah akan menunjukan waktu saja
      s = 1;
    }
  }
  sprintf(buffdet, "%02d", rDet);
  jamNormal(1, 17 - y);
  Disp.drawCircle(27, y - 8, 7, 1);
  Disp.setFont(Font3x5);
  Disp.drawText(24, y - 11, buffdet);
  drawMasjid(3, y - 8);
  if (y == 0 and s == 1) {
    cycle += 1;
    s = 0;
    y = 0;
  }
}

void Disp_Tgl() {
  static uint32_t pM;
  uint32_t cM = millis();
  static uint8_t Kecepatan = 30;
  static uint32_t x;
  char msg[20];
  jamNormal(1, 1);
  if (type) {
    sprintf(msg, "%s, %d %s %i", namaHari[rHar], rTgl, namaBulan[rBul], rTah);
  }
  else{
    sprintf(msg, "%d %s %i", Hjr_Date, bulanHijriah[Hjr_Month], Hjr_Year);
  }
  Disp.setFont(huruf6x7);
  int fullScroll = Disp.textWidth(msg) + width;
  if (cM - pM > Kecepatan) {
    pM = cM;
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      Disp.clear();
      cycle += 1;
      type=!type;
    }
    Disp.drawText(width - x, 9, msg);
  }
}

void cycle_info(){
  if(jumat) return;
  static bool lKdp=kdp;
  static int8_t n_beep=10;
  if (lsKdp != kdp) {
    lsKdp = kdp;
    check_azzan(cycle, n_beep);
    check_imsyak(cycle, n_beep);
  }
  switch(cycle){
    case 0:
//      Serial.println(cycle);
      Disp_Jam();
      break;
    case 1:
//      Serial.println(cycle);
      Disp_Main();
      break;
    case 2:
//      Serial.println(cycle);
      Disp_Tgl();
      break;
    case 3:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info1), 9);
      break;
    case 4:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info2), 9);
      break;
    case 5:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info3), 9);
      break;
    case 6:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info4), 9);
      break;
    case 7:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info5), 9);
      break;
    case 8:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info6), 9);
      break;
    case 9:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info7), 9);
      break;
    case 10:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info8), 9);
      break;
    case 11:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info9), 9);
      break;
    case 12:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info10), 9);
      break;
    case 13:{
//      Serial.println(cycle);
      int j=5;
      for(int i=0;i<5;i++){
        String a = p_info.jumat[i];
        int b = (a.substring(14,16)).toInt();
        if(rTgl<=b&&b>0){
          j=i;
        }
      }
      Disp_Info(String(p_info.jumat[j]), 9);
      break;}
    case 14:
//      Serial.println(cycle);
      info_puasa(9);
      break;
    case 18:
      Disp_Azzan(0);
      if(lKdp!=kdp){
        lKdp=kdp;
        if(n_beep>0){
          n_beep--;
          digitalWrite(buzzer, !kdp);
        }else{
          digitalWrite(buzzer, LOW);
          cycle=0;
        }
      }
      break;
    case 20:
//      Serial.println(cycle);
      Disp_Azzan(SholatNow);
      tekanTombol(cycle);
      if(lKdp!=kdp){
        lKdp=kdp;
        if(n_beep>0){
          n_beep--;
          digitalWrite(buzzer, !kdp);
        }else{
          digitalWrite(buzzer, LOW);
          if (rHar == 5 and SholatNow == 4) {
            jumat = true;
//            tarhim = false;
            iqmh = false;
            cycle = 0;
          }
        }
      }
      break;
    case 21:
//      Serial.println(cycle);
      tampilIqomah();
      break;
    case 22:
//      Serial.println(cycle);
      sebelumSholat("Lurus dan Rapatkan Shaf Demi Kesempurnaan Sholat Berjamaah", 9);
      break;
    default:
      cycle = 0;
      break;   
  }
//      Serial.println("cycleend");
}
