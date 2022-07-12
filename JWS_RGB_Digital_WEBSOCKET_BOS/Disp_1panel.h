int8_t jumlah_beep = 0;
bool tndaBuzzer = false;
uint8_t cycle=0;
int tmpilJdwal = 1;
//uint8_t dtk3=0;
//uint8_t dtk5=0;
uint16_t text_speed=30;

String tampil_waktu[]={"Waktu Imsyak", "Waktu Adzan", "Waktu Terbit", "Waktu Dhuha", "Waktu Adzan", "Waktu Adzan", "Waktu Adzan", "Waktu Adzan"};

void buzz(int8_t n){
  time2 = millis();
  jumlah_beep=(n*2)-1;
}
void Disp_Azzan(String x, uint16_t y) {
  if(jumat) return;
  virtualDisp->setCursor(2, y);
  virtualDisp->print(x);
}

int16_t textWidth(const char* text)
{
  int16_t x1, y1;
  uint16_t w, h;
  virtualDisp->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  return w;
}


void tampilIqomah(uint16_t y, uint8_t& cycl){
  static bool lKdp=kdp;
  static int8_t i_menit = timer_iqomah();
  static int8_t i_detik = 0;
  virtualDisp->setFont(&Picopixel);
  virtualDisp->setCursor(3, y-1);
  virtualDisp->printf("IQOMAH :");
  virtualDisp->setFont(&Font5x78pt7b);
  virtualDisp->setCursor(32, y);
  virtualDisp->printf("%02d:%02d", i_menit, i_detik);
  if(kdp)virtualDisp->fillRect(3, 25, 27, 6, 0B0000000000000000);
  if(lKdp!=kdp){
    lKdp=kdp;
    if(!lKdp)return;
    i_detik--;
    if(i_detik<0){
      i_menit--;
      if(i_menit<0){
        cycl++;
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
        tarhim = false;
        cycl++;
        buzz(1);
      }
      state=LOW;
    }
  }
}

void sebelumSholat(String msg, uint16_t y, uint8_t& cycl){
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  static bool rst=true;
  static int8_t beep_sholat;
  if(rst){
    pTeks = msg.length();
    beep_sholat = 3;
    buzz(3);
    rst=false;
  }
  if ((Tmr - lsRn) > text_speed) {
    lsRn = Tmr;
    x--;
    if (x < (pTeks * (-6))) {
      x = lebar;
      cycl++;
      rst=true;
      tarhim = false;
      return;
    }
  }
  virtualDisp->setCursor(x, y);
  virtualDisp->print(msg);
}

void Disp_Info(String msg, uint16_t y, uint8_t& cycl) {
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  static bool rst=true;
  if(!bitRead(bit_data, cycl)){
    cycl++;
    return;
  }
  if(rst){
    pTeks = msg.length()*(-6);
    lsRn = Tmr;
    x = lebar;
    rst = false;
  }
  if ((Tmr - lsRn) > 30) {
    lsRn = Tmr;
    x--;
    if (x < pTeks) {
      cycl++;
      rst=true;
    }
  }
  virtualDisp->setCursor(x, y);
  virtualDisp->print(msg.c_str());
}

void info_puasa(uint16_t y, uint8_t& cycl){
  if(jumat) return;
  static String msg = "";
  uint32_t Tmr = millis();
  static uint32_t lsRn;
  static int16_t x = lebar;
  static bool rst=true;
  static uint8_t i_p;
  static int16_t s_pTeks;
  if(!p_jws.disppuasa){
    cycl++;
    return;
  }
  if(rst){
    i_p = check_puasa();
    if(i_p==0){
      cycl++;
      rst = true;
      return;
    }
    msg = String(namaPuasa[i_p-1]);
    x = lebar;
    s_pTeks = *(&namaPuasa[i_p-1] + 1) - namaPuasa[i_p-1];
    rst = false;
  }
  if ((Tmr - lsRn) > 30) {
    lsRn = Tmr;
    x--;
    if (x < (s_pTeks * (-5))) {
      cycl++;
      rst=true;
    }
  }
  virtualDisp->setCursor(x, y);
  virtualDisp->print(msg.c_str());
  Serial.println("puasa");
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
    case 0://menampilkan nama penceramah
//      Serial.println(cycle);
      Disp_Info(String(p_info.info1), 30, cycle);
      break;
    case 1:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info2), 30, cycle);
      break;
    case 2:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info3), 30, cycle);
      break;
    case 3:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info4), 30, cycle);
      break;
    case 4:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info5), 30, cycle);
      break;
    case 5:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info6), 30, cycle);
      break;
    case 6:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info7), 30, cycle);
      break;
    case 7:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info8), 30, cycle);
      break;
    case 8:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info9), 30, cycle);
      break;
    case 9:
//      Serial.println(cycle);
      Disp_Info(String(p_info.info10), 30, cycle);
      break;
    case 10:{
//      Serial.println(cycle);
      int j=5;
      for(int i=0;i<5;i++){
        String a = p_info.jumat[i];
        int b = (a.substring(14,16)).toInt();
        if(rTgl<=b&&b>0){
          j=i;
        }
      }
      Disp_Info(String(p_info.jumat[j]), 30, cycle);
      break;}
    case 11:
//      Serial.println(cycle);
      info_puasa(30, cycle);
      break;
    case 15:
      if(kdp) Disp_Azzan(tampil_waktu[0], 30);
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
      tekanTombol(cycle);
      !kdp ? Disp_Azzan(tampil_waktu[SholatNow], 30) : virtualDisp->fillRect(33, 1, 30, 14, 0B0000000000000000);
      if(lKdp!=kdp){
        lKdp=kdp;
        if(n_beep>0){
          n_beep--;
          digitalWrite(buzzer, !kdp);
        }else{
          digitalWrite(buzzer, LOW);
          if (rHar == 5 and SholatNow == 4) {
            jumat = true;
            tarhim = false;
            iqmh = false;
            cycle = 0;
          }
        }
      }
      break;
    case 21:
//      Serial.println(cycle);
      tampilIqomah(30, cycle);
      break;
    case 22:
//      Serial.println(cycle);
      sebelumSholat("Lurus dan Rapatkan Shaf Demi Kesempurnaan Sholat Berjamaah", 30,  cycle);
      break;
    default:
      cycle = 0;
      break;
      
  }
  
//      Serial.println("cycleend");
  
}

void Disp_Main() {
  if(jumat) return;
  if(azzan){
    virtualDisp->setFont(&Picopixel);
    virtualDisp->setTextColor( 0B0000011111100000);
    virtualDisp->setCursor(35, 5);
    virtualDisp->print(namaWaktuSholat[SholatNow]);
    virtualDisp->setFont(&Font5x78pt7b);
    virtualDisp->setTextColor( 0B1111111111111111);
    virtualDisp->setCursor(33, 14);
    virtualDisp->printf("%02d:%02d", stimeInt[SholatNow][0],stimeInt[SholatNow][1]);
  }else{
    static int    x = 0;
    static uint8_t    s; // 0=in, 1=out
    static uint32_t   lsRn;
    static uint8_t    tmpilJdwal;
    uint32_t          Tmr = millis();
    if (!p_jws.dispimsyak and tmpilJdwal == 0) { //optional skip imsyak
      tmpilJdwal++;
    }
    if (!p_jws.dispterbit and tmpilJdwal == 2) { //optional skip terbit
      tmpilJdwal++;
    }
    if (!p_jws.dispdhuha and tmpilJdwal == 3) { //optional skip dhuha
      tmpilJdwal++;
    }
    if ((Tmr - lsRn) > 30){
      if (s == 0 and x < 20) {
        lsRn = Tmr;
        x++;
      }
      if (s == 1 and x > 0) {
        lsRn = Tmr;
        x--;
      }
    }
    if ((Tmr - lsRn) > 3000 and x >= 20) {
      s = 1;
    }
    virtualDisp->setFont(&Picopixel);
    virtualDisp->setTextColor( 0B0000011111100000);
    virtualDisp->setCursor(35, x-15);
    virtualDisp->print(namaWaktuSholat[tmpilJdwal]);
    virtualDisp->setFont(&Font5x78pt7b);
    virtualDisp->setTextColor( 0B1111111111111111);
    virtualDisp->setCursor(34, x-6);
    virtualDisp->printf("%02d:%02d", stimeInt[tmpilJdwal][0],stimeInt[tmpilJdwal][1]);
    if (x == 0 and s == 1) {
      s = 0;
      if (tmpilJdwal < 7) {
        tmpilJdwal++;
      } else {
        tmpilJdwal = 0;
      }
    }
  }
}


void Disp_Jam() {
  virtualDisp->setTextColor( 0B0000011111100000);
  if(!jumat){
    static int    x = 0;
    static uint8_t    s; // 0=in, 1=out
    static uint32_t   lsRn;
    static bool    tmpilJdwal;
    uint32_t          Tmr = millis();
    if ((Tmr - lsRn) > 10){
      if (s == 0 and x < 60) {
        lsRn = Tmr;
        x++;
      }
      if (s == 1 and x > 0) {
        lsRn = Tmr;
        x--;
      }
    }
    if ((Tmr - lsRn) > 5000 and x >= 60) {
      s = 1;
    }
    
    virtualDisp->setFont(&Font5x78pt7b0);
    virtualDisp->setCursor(x-57, 22);
    if(tmpilJdwal){
      virtualDisp->printf("%02d %s %d", rTgl, namaBulan[rBul], rTah);
    }else{
      virtualDisp->printf("%02d %s %d", Hjr_Date, bulanHijriah[Hjr_Month], Hjr_Year);
    }
    if (x == 0 and s == 1) {
      s = 0;
      tmpilJdwal=!tmpilJdwal;
    }
  }
  virtualDisp->setFont(&BigNumber7pt7b);
  if (kdp) {
    virtualDisp->setCursor(15, 11);
    virtualDisp->printf(":");
  }
  virtualDisp->setTextColor( 0B1111111111111111);
  virtualDisp->setCursor(2, 11);
  virtualDisp->printf("%02d %02d", rJam, rMen);
}
