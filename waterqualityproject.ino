#define  PHPin A1
#define TDSPin A0

#include <TVout.h>
#include <fontALL.h>

TVout TV;

unsigned long int avgPH;
unsigned long int avgTDS;
float b1, b2;
int buf1[10], buf2[10], temp1, temp2;

void setup() {

//  pinMode(13,OUTPUT);
  pinMode(TDSPin, INPUT);
  pinMode(PHPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("Ready");
  TV.begin(NTSC,120,96);
  TV.select_font(font6x8);

}

void loop(){
  for(int i=0;i<10;i++){
    buf1[i] = analogRead(PHPin);
    buf2[i] = analogRead(TDSPin);
    Serial.println("ph: "); Serial.println(buf1[i]);
    Serial.println("tds: "); Serial.println(buf2[i]);  
    delay(10);
  }

  for(int i=0;i<9;i++){
    for(int j=i+1;j<10;j++){
      if(buf1[i]>buf1[j]){
        temp1=buf1[i];
        buf1[i]=buf1[j];
        buf1[j]=temp1; 
      }
      if(buf2[i]>buf2[j]){
        temp2=buf2[i];
        buf2[i]=buf2[j];
        buf2[j]=temp2;
      }
    }
  }

  avgPH=0; avgTDS=0;
  for(int i=2;i<8;i++){
    
    avgPH+=buf1[i];
    avgTDS+=buf2[i];
  }
  avgPH=avgPH/6;
  avgTDS=avgTDS/6;

  TV.clear_screen();
  TV.select_font(font6x8);
  TV.println("PH Value:");
  TV.println(avgPH);
  TV.println("TDS Value:");
  TV.println(avgTDS);

  float PH = 7 - (avgPH/59.16);
  float TDS = (avgTDS*100/16)-4;
  
//  Serial.println("PH READING:");
//  Serial.println(PH);
//  Serial.println("TDS READING:");
//  Serial.println(TDS);
  delay(800);
}
