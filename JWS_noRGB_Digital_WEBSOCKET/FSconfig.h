void writeFile(fs::FS &fs, const char * path, const char * message);
void deleteFile(fs::FS &fs, const char * path);

String parsing(String& pesan){
  String a=pesan.substring(0, pesan.indexOf("*"));
  pesan = pesan.substring(pesan.indexOf("*")+1);
  return a;
}
//==========================================JWS===================================================

const char *filejws = "/parameter_JWS.json";

String p_defaultJWS() {
  String defaultJWS = "";
  defaultJWS += "3*";
  defaultJWS += "12*";
  defaultJWS += "8*";
  defaultJWS += "6*";
  defaultJWS += "5*";
  defaultJWS += "5*";
  defaultJWS += "45*";
  defaultJWS += "2*";
  defaultJWS += "4*";
  defaultJWS += "0*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true*";
  defaultJWS += "true";
  Serial.println(defaultJWS);
  return defaultJWS;
}


void print_p_jws() {
  Serial.println();
  Serial.println("===================== PARAMETER JWS ==================");
  Serial.println();
  Serial.printf("versi \t\t\t : %d\n", p_jws.versi);
  Serial.printf("jeda iqomah subuh \t : %d\n", p_jws.is);
  Serial.printf("jeda iqomah dzuhur \t : %d\n", p_jws.id);
  Serial.printf("jeda iqomah ashar \t : %d\n", p_jws.ia);
  Serial.printf("jeda iqomah maghrib \t : %d\n", p_jws.im);
  Serial.printf("jeda iqomah isya' \t : %d\n", p_jws.ii);
  Serial.printf("durasi adzan \t\t : %d\n", p_jws.durasiAdzan);
  Serial.printf("faktor Hijriah \t\t : %d\n", p_jws.f_hjr);
  Serial.printf("durasi kutbah \t\t : %d\n", p_jws.durasikutbah);
  Serial.printf("faktor waktu Sholat \t : %d\n", p_jws.f_ws);
  Serial.printf("display iqomah \t\t : %d\n", p_jws.dispiqmh);
  Serial.printf("display imsyak \t\t : %d\n", p_jws.dispimsyak);
  Serial.printf("ring imsyak \t\t : %d\n", p_jws.ringimsyak);
  Serial.printf("display puasa \t\t : %d\n", p_jws.disppuasa);
  Serial.printf("display dhuha \t\t : %d\n", p_jws.dispdhuha);
  Serial.printf("display terbit \t\t : %d\n", p_jws.dispterbit);
  Serial.printf("display splash screen\t : %d\n", p_jws.dispsplash);
}

void readFileJWS(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
    String dataJson;

    File file = fs.open(path, "r");
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
//    while(file.available()){
//        Serial.write(file.read());
//    }

    String hasil[17];
  String pesan = file.readString();
  for(int i=0;i<17;i++){
    hasil[i] = parsing(pesan);
  }
  p_jws.versi         = hasil[0].toInt();
  p_jws.is            = hasil[1].toInt();
  p_jws.id            = hasil[2].toInt();
  p_jws.ia            = hasil[3].toInt();
  p_jws.im            = hasil[4].toInt();
  p_jws.ii            = hasil[5].toInt();
  p_jws.durasiAdzan   = hasil[6].toInt();
  p_jws.f_ws          = hasil[7].toInt();;
  p_jws.durasikutbah  = hasil[8].toInt();;
  p_jws.f_hjr         = hasil[9].toInt();;
  p_jws.dispiqmh      = (hasil[10]=="true");
  p_jws.dispimsyak    = (hasil[11]=="true");
  p_jws.ringimsyak    = (hasil[12]=="true");
  p_jws.disppuasa     = (hasil[13]=="true");
  p_jws.dispdhuha     = (hasil[14]=="true");
  p_jws.dispterbit    = (hasil[15]=="true");
  p_jws.dispsplash    = (hasil[16]=="true");

    file.close();
//    print_p_jws();
    
}

//=============================================ADMIN=============================================

const char *fileAdmin = "/parameter_Admin.json";

String p_defaultAdmin() {
  String defaultAdmin = "";
  defaultAdmin += "-6.26350*";
  defaultAdmin += "106.96157*";
  defaultAdmin += "7*";
  defaultAdmin += "2*";
  defaultAdmin += "SII-Cikunir*";
  defaultAdmin += "admin.admin*";
  defaultAdmin += "JWS_AP*";
  defaultAdmin += "jwsmasjid01*";
  defaultAdmin += "100";
  Serial.println(defaultAdmin);
  return defaultAdmin;
}

void print_p_admin() {
  Serial.println();
  Serial.println("=========== DATA PARAMETER ADMIN ============");
  Serial.println();
  Serial.printf("latitude \t \t : %f\n", p_admin.lat);
  Serial.printf("longitude \t \t : %f\n", p_admin.lon);
  Serial.printf("zona waktu \t \t : %d\n", p_admin.z_w);
  Serial.printf("hilal \t \t \t : %d\n", p_admin.hilal);
//  Serial.printf("ssid \t \t \t : p_admin.ssid", p_admin.ssid);
  Serial.println("ssid \t \t \t : "+p_admin.ssid);
//  Serial.printf("password ssid \t \t : %s\n", p_admin.p_ssid);
  Serial.println("password ssid \t \t : "+p_admin.p_ssid);
//  Serial.printf("akses point \t \t : %s\n", p_admin.ap);
  Serial.println("akses point \t \t : "+p_admin.ap);
//  Serial.printf("password akses poin \t : %s\n", p_admin.p_ap);
  Serial.println("password akses poin \t : "+p_admin.p_ap);
  Serial.printf("batas tombol \t \t : %d\n", p_admin.batastombol);
}

void readFileAdmin(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path,"r");
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[9];
  String pesan = file.readString();
  for(int i=0;i<9;i++){
    hasil[i] = parsing(pesan);
  }
  p_admin.lat             = hasil[0].toFloat();
  p_admin.lon             = hasil[1].toFloat();
  p_admin.z_w             = hasil[2].toInt();
  p_admin.hilal           = hasil[3].toInt();
  p_admin.ssid            = hasil[4];
  p_admin.p_ssid          = hasil[5];
  p_admin.ap              = hasil[6];
  p_admin.p_ap            = hasil[7];
  p_admin.batastombol     = hasil[8].toInt();
  file.close();
  
  file.close();
//  print_p_admin();
}

//============================================INFO================================================


const char *fileInfo = "/parameter_Info.json";


String p_defaultInfo(){
  String defaultInfo = "";
  defaultInfo += "info_1*";
  defaultInfo += "info_2*";
  defaultInfo += "info_3*";
  defaultInfo += "info_4*";
  defaultInfo += "info_5*";
  defaultInfo += "info_6*";
  defaultInfo += "info_7*";
  defaultInfo += "info_8*";
  defaultInfo += "info_9*";
  defaultInfo += "info_10*";
  defaultInfo += "info_11*";
  defaultInfo += "info_12*";
  defaultInfo += "info_13*";
  defaultInfo += "info_14*";
  defaultInfo += "info_15*";
  defaultInfo += "Masjid Jami' Alhuda Bittaqwa*";
  defaultInfo += "49665";
  Serial.println(defaultInfo);
  return defaultInfo;
}

void print_p_info(){
  Serial.println();
  Serial.println("=========== DATA PARAMETER INFO ============");
  Serial.println();
  Serial.printf("info1 \t \t : %s\n", p_info.info1);
  Serial.printf("info2 \t \t : %s\n", p_info.info2);
  Serial.printf("info3 \t \t : %s\n", p_info.info3);
  Serial.printf("info4 \t \t : %s\n", p_info.info4);
  Serial.printf("info5 \t \t : %s\n", p_info.info5);
  Serial.printf("info6 \t \t : %s\n", p_info.info6);
  Serial.printf("info7 \t \t : %s\n", p_info.info7);
  Serial.printf("info8 \t \t : %s\n", p_info.info8);
  Serial.printf("info9 \t \t : %s\n", p_info.info9);
  Serial.printf("info10 \t \t : %s\n", p_info.info10);
  Serial.printf("info11 \t \t : %s\n", p_info.masjid);
} 

void readFileInfo(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
    String dataJson;

    File file = fs.open(path, "r");
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return;
    }
    String hasil[17];
    String pesan = file.readString();
    for(int i=0;i<17;i++){
      hasil[i] = parsing(pesan);
    }
    p_info.info1            = hasil[0];
    p_info.info2            = hasil[1];
    p_info.info3            = hasil[2];
    p_info.info4            = hasil[3];
    p_info.info5            = hasil[4];
    p_info.info6            = hasil[5];
    p_info.info7            = hasil[6];
    p_info.info8            = hasil[7];
    p_info.info9            = hasil[8];
    p_info.info10           = hasil[9];
    p_info.jumat[0]         = hasil[10];
    p_info.jumat[1]         = hasil[11];
    p_info.jumat[2]         = hasil[12];
    p_info.jumat[3]         = hasil[13];
    p_info.jumat[4]         = hasil[14];
    p_info.masjid           = hasil[15];
    p_info.enable_info      = hasil[16].toInt();
    
    file.close();
//    print_p_info();
    
}

void resetjumat(fs::FS &fs, const char * path){
    //    Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[17];
  String pesan = file.readString();
  for(int i=0;i<17;i++){
    hasil[i] = parsing(pesan);
  }
  for(int i = 10; i<15; i++){
    hasil[i]="-";
  }
  pesan="";
  for(int i=0;i<17;i++){
    pesan+=hasil[i];
    if(i!=16){
      pesan+="*";
    }
  }
  file.close();
  writeFile(LittleFS, fileInfo, pesan.c_str());
  readFileInfo(LittleFS, fileInfo);
}

void gantiInfo(fs::FS &fs, const char * path, String x) {
  //    Serial.printf("Reading file: %s\r\n", path);
  String a = x.substring(0, x.indexOf("="));
  int b = a.toInt();
  String c = x.substring(x.indexOf("=")+1);
  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[17];
  String pesan = file.readString();
  for(int i=0;i<17;i++){
    hasil[i] = parsing(pesan);
  }
  hasil[b] = c;
  pesan="";
  for(int i=0;i<17;i++){
    pesan+=hasil[i];
    if(i!=16){
      pesan+="*";
    }
  }
  file.close();
  writeFile(LittleFS, fileInfo, pesan.c_str());
  readFileInfo(LittleFS, fileInfo);
}

void change_enable(fs::FS &fs, const char * path, uint16_t x) {
  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[17];
  String pesan = file.readString();
  for(int i=0;i<17;i++){
    hasil[i] = parsing(pesan);
  }
  hasil[16] = String(x);
  pesan="";
  for(int i=0;i<17;i++){
    pesan+=hasil[i];
    if(i!=16){
      pesan+="*";
    }
  }
  file.close();
  writeFile(LittleFS, fileInfo, pesan.c_str());
  readFileInfo(LittleFS, fileInfo);
  bit_data = p_info.enable_info;
//  Serial.println(p_info.enable_info);
}

//======================================Cerah & Volume============================================
const char *fileAtur = "/parameter_Atur.json";

String p_defaultAtur() {
  String defaultAtur = "";
  defaultAtur += "100*";
  defaultAtur += "10*";
  return defaultAtur;
}

void readFileAtur(fs::FS &fs, const char * path) {
  //    Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path, "r");
  if (!file || file.isDirectory()) {
    //        Serial.println("- failed to open file for reading");
    return;
  }
  String hasil[2];
  String pesan = file.readString();
  for(int i=0;i<2;i++){
    hasil[i] = parsing(pesan);
  }
  p_atur[0]             = hasil[0].toInt();
  p_atur[1]             = hasil[1].toInt();
  file.close();
}

//=========================================CONFIG================================================


void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  //    Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname, "r");
  if (!root) {
    //        Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    //        Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      //            Serial.print("  DIR : ");
      //            Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      //            Serial.print("  FILE: ");
      //            Serial.print(file.name());
      //            Serial.print("\tSIZE: ");
      //            Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if (!file) {
    //        Serial.println("- failed to open file for writing");
    return;
  }

  if (file.print(message)) {
    //        Serial.println("- file written");
  } else {
    //        Serial.println("- write failed");
  }
  file.close();

}

void deleteFile(fs::FS &fs, const char * path) {
  //    Serial.printf("Deleting file: %s\r\n", path);
  if (fs.remove(path)) {
    //        Serial.println("- file deleted");
  } else {
    //        Serial.println("- delete failed");
  }
}

void DataDefault() {
  writeFile(LittleFS, filejws, p_defaultJWS().c_str());
  writeFile(LittleFS, fileAdmin, p_defaultAdmin().c_str());
  writeFile(LittleFS, fileInfo, p_defaultInfo().c_str());
  writeFile(LittleFS, fileAtur, p_defaultAtur().c_str());
}
