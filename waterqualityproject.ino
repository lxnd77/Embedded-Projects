#include <GravityTDS.h>
#include <DS18B20.h>

#define  PHPin A1
#define TDSPin A0
#define TrigPin 12
#define EchoPin 13
DS18B20 ds1(2);
DS18B20 ds2(4);
GravityTDS gravityTds;

unsigned long int avgPH;
float b1, b2;
int buf1[10], buf2[10], buf3[10], temp1;
float temperature1 = 0, temperature2 = 0, tdsValue = 0, temp1Value=0, temp2Value=0;

void setup() {

  pinMode(TDSPin, INPUT);
  pinMode(PHPin, INPUT);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  Serial.begin(9600);

  gravityTds.setPin(TDSPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization

}

void loop(){

  float t=0, h=0;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TrigPin, LOW);

  t = pulseIn(EchoPin, HIGH);
  h=t/58;
  h=h-10; //how far above the tank
  h=50-h;
  h=(int)h*4;
  
  temp1Value = ds1.getTempC();
  temp2Value = ds2.getTempC();
  gravityTds.setTemperature(temp1Value);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate
  
  tdsValue = gravityTds.getTdsValue();  // then get the value
  for(int i=0;i<10;i++){
    buf1[i] = analogRead(PHPin);
    delay(10);
  }

  for(int i=0;i<9;i++){
    for(int j=i+1;j<10;j++){
      if(buf1[i]>buf1[j]){
        temp1=buf1[i];
        buf1[i]=buf1[j];
        buf1[j]=temp1; 
      }
    }
  }
  avgPH=0; 
  for(int i=2;i<8;i++){    
    avgPH+=buf1[i];
  }
  avgPH=avgPH/6;
  
  float pHVol=(float)avgPH*5.0/1024/6;
  //float phValue = -5.70 * pHVol + 8.65;
  float phValue = -5.70 * pHVol + 9.05;
  Serial.flush();
  Serial.println(String("PH: ") + phValue + 
                String(" TDS: ") + tdsValue + 
                String(" PPM") + String(" Water: ") + h + String(" Liters") + 
                String(" Temp1: ") + temp1Value + 
                String(" Temp2: ") + temp2Value + 
                String(" "));
  delay(4000);
}
