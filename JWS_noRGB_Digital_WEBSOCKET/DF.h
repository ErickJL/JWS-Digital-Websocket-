bool tarhim = false;
int tarhim2=-1;

void runtarhim(int x) {
  if (!tarhim) {
    Serial.println("********** TARHIM **********");
    myDFPlayer.playMp3Folder(x);
    tarhim = true;
    tarhim2=millis();
  }
}



void runtarhim2(){
  if(tarhim2>-1){
    if(millis()-tarhim2>=4500){
      myDFPlayer.pause();
      myDFPlayer.stop();
      myDFPlayer.playMp3Folder(3);
      tarhim2=-1;
    }
  }
}

void setDF(){
  while (!myDFPlayer.begin(Serial)) {
  }
  delay(200);
  myDFPlayer.reset();
  delay(500);
  myDFPlayer.volume(p_atur[1]);
  delay(200);
  myDFPlayer.playMp3Folder(3);
}
