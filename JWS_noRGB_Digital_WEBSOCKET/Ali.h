bool kdp, lsKdp;
void kedip() {
  static uint32_t   timerSave, lastSecond;
  uint32_t          nowmilis = millis();
  if (lastSecond != rDet) {
    lastSecond = rDet;
    kdp = true;
    timerSave = nowmilis;
  }
  if ((nowmilis - timerSave) > 500) {
    kdp = false;
  }
}

float derajat(float deg) {
  float rad = (deg * 3.1415 / 180);
  return rad;
}

void jamAnalog() {
  //  static uint16_t   lsRn;
  //    uint16_t          Tmr = millis();
  //    fType(1);
  int cx = 31;
  int cy = 32;
  int h  = 14;
  //
  //    int r_sec = 26;  // Length of second-hand
  //    int r_min = 24;  // Length of minute-hand
  //    int r_hr  = 18;  // Length of hour-hand
  //
  //    byte detik = rDet;
  //    byte menit = rMen+detik/60;
  //    byte jam = rJam+menit/60;
  //
  //    int x_sec = r_sec * cos(derajat((detik-15) * (360/60))) + cx;
  //    int y_sec = r_sec * sin(derajat((detik-15) * (360/60))) + cy;
  //
  //    int x_min = r_min * cos(derajat((menit-15) * (360/60))) + cx;
  //    int y_min = r_min * sin(derajat((menit-15) * (360/60))) + cy;
  //
  //    int x_hr = r_hr * cos(derajat((jam-3) * (360/12))) + cx;
  //    int y_hr = r_hr * sin(derajat((jam-3) * (360/12))) + cy;

  // virtualDisp.clearDisplay();
  // virtualDisp.fillScreen(0);

//  virtualDisp->drawCircle(cx, cy, 31, 0B1111111110000000);
//  virtualDisp->drawCircle(cx, cy, 30, 0B1111111110000000);
//  virtualDisp->drawCircle(cx, cy, 28, 0B1111001110101100);


  //    virtualDisp->drawLine(cx,cy,x_sec,y_sec,virtualDisp->color333(7,7,0));//detik
  //    virtualDisp->drawLine(cx,cy,x_min,y_min,virtualDisp->color333(0,128,21));//menit
  //    virtualDisp->drawLine(cx,cy,x_hr,y_hr,virtualDisp->color565(255,0,0));
  //    virtualDisp->drawCircle(x_hr,y_hr,1,virtualDisp->color565(255,0,0));//jam
  //
  //    virtualDisp->drawCircle(cx,cy,0,virtualDisp->color565(0,0,0));
  //    virtualDisp->drawCircle(cx,cy,2,virtualDisp->color565(0,255,0));
  //    virtualDisp->drawCircle(cx,cy,1,0B1111100000000000);//merah titik tengah
}
