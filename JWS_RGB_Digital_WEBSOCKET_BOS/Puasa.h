int indeks_puasa;
int hd_puasa;
/*
 char namaPuasa[][13]={
  "SYAWAL",//1
  "SYA'BAN",//2
  "SENIN",//3
  "KAMIS",//4
  "TENGAH BULAN",//5
  "AROFAH",//6
  "DZULHIJAH",//7
  "TASU'A",//8
  "ASYURA",//9
  "RAMADHAN"//10
};
*/
const char namaPuasa[][80]={
  "Mari Menunaikan Puasa Sunnah Tasu'a Esok Hari",//8
  "Mari Menunaikan Puasa Sunnah Puasa Asyura Esok Hari",//9
  "Mari Menunaikan Puasa Sunnah Puasa Sya'ban Esok Hari",//2
  "Selama Bulan Ramadhan Jangan Lupa Niat Puasa untuk Esok Hari",//10
  "Mari Perbanyak Menunaikan Puasa Sunnah Syawal",//1
  "Jangan Lupa Menunaikan Puasa Sunnah Arofah Esok Hari",//6
  "Jangan Lupa Menunaikan Puasa Sunnah Dzulhijah Esok Hari",//7
  "Mari Menunaikan Puasa Sunnah Tengah Bulan Esok Hari",//5
  "Mari Menunaikan Puasa Sunnah Senin Esok Hari",//3
  "Mari Menunaikan Puasa Sunnah Kamis Esok Hari",//4
};
//8,9,2,10,1,6,7,5,3,4

uint8_t check_puasa()
  {
    if(floatnow>stimeFloat[0] and floatnow<stimeFloat[6]){//puasa ditampilkan hanya pada malam hari
      indeks_puasa = 0;
      return indeks_puasa;
    }
//    Serial.println(Hjr_Month);
    indeks_puasa = 0;
    // cek hari dilarang puasa
    if (  ((Hjr_Month == 12)  &&   (Hjr_Date == 10)) ||   // Idul Adha
          ((Hjr_Month == 12)  &&   (Hjr_Date == 11)) ||   // Hari tasyrik 1
          ((Hjr_Month == 12)  &&   (Hjr_Date == 12)) ||   // Hari tasyrik 2
          ((Hjr_Month == 12)  &&   (Hjr_Date == 13)) ||   // Hari tasyrik 3
          ((Hjr_Month == 10)  &&   (Hjr_Date ==  1)) ||   // Idul Fitri
          ((Hjr_Month ==  8)  &&   (Hjr_Date == 29)) ||   // Akhir bulan Sya'ban
          ((Hjr_Month ==  8)  &&   (Hjr_Date == 30)))
        {
          indeks_puasa = 0;
          return indeks_puasa;
        }
    else 
        {
          if ((Hjr_Month == 1) and (Hjr_Date == 9))  // 9 Muharram --> Puasa Arofah
            {
//              indeks_puasa = 8;  //8,9,2,10,1,6,7,5,3,4
              indeks_puasa = 1;
            }
          else if ((Hjr_Month == 1) and (Hjr_Date == 10))  // 10 Muharram --> Puasa Asura
            {
//              indeks_puasa = 9;
              indeks_puasa = 2;
            }
          else if ((Hjr_Month == 8) and (Hjr_Date >= 1))  // Perbanyak puasa sunnah bulan Sya'ban
            {
//              indeks_puasa = 2;
              indeks_puasa = 3;
            }
          else if (Hjr_Month == 9)  // Puasa Ramadhan
            {
//              indeks_puasa = 10;
              indeks_puasa = 4;
            }
          else if ((Hjr_Month == 10) and (Hjr_Date > 2))  // Bulan Syawal --> Puasa 6 Hari Sawal
            {
//              indeks_puasa = 1; 
              indeks_puasa = 5; 
            }
          else if ((Hjr_Month == 12) and (Hjr_Date == 9))  // 9 Dzulhijah --> Puasa Arofah
            {
//              indeks_puasa = 6;
              indeks_puasa = 6;
            }
          else if ((Hjr_Month == 12) and (Hjr_Date < 9))  // 9 hari pertama Dzulhijah --> Puasa Awal Dzulhijah
            {
//              indeks_puasa = 7;
              indeks_puasa = 7;
            }
          else if(Hjr_Date == 13 or Hjr_Date == 14 or Hjr_Date == 15)   // Puasa Tengah Bulan tgl 13,14,15
            {
//              indeks_puasa = 5;
              indeks_puasa = 8;
            }
          else if(Hjr_Hari== 2)  // Jika sekarang Minggu --> besok puasa Senin
            {
//              indeks_puasa = 3;
              indeks_puasa = 9;
            }
          else if(Hjr_Hari== 5)  // Jika sekarang Rabu --> besok puasa Kamis
            {
//              indeks_puasa = 4;
              indeks_puasa = 10;
            }
          return indeks_puasa;
        }
  }
