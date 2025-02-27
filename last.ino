#include <LiquidCrystal_I2C.h>
#define USE_ARDUINO_INTERRUPTS true    // 가장 정확한 BPM 연산을 위해 낮은 수준의 인터럽트를 설정
#include <PulseSensorPlayground.h>        

const int lcdAddress = 0x27;
const int lcdColumns = 16; 
const int lcdRows = 2; 
const int PulseWire = 0;
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // "비트로 카운트"할 신호와 무시할 신호를 결정
                               // "Gettting Started Project"를 사용하여 임계값을 기본 설정 이상으로 미세 조정
                               // 그렇지 않으면 기본 "550" 값을 그대로 유지 
LiquidCrystal_I2C lcd(lcdAddress, lcdColumns, lcdRows);
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"
int joyx;    //조이스틱 x방향
int joyy;    //조이스틱 y방향
int sex=0;     //성별
int age=0;     //나이
int bpm_total=0;  // bpm 값 다 더하기


byte heart[8] = {    //'♥' 문자 사용자 정의
   B00000,
   B01010,
   B11111,
   B11111,
   B11111,
   B01110,
   B00100,
   B00000
};


void setup() {

  //pulseSensor.analogInput(PulseWire);   
  //pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  //pulseSensor.setThreshold(Threshold);   
  //if (pulseSensor.begin()) {
 //   Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
 // }    //심박수 센서 정상 작동 확인
  
 lcd.init();
 lcd.backlight();
 lcd.begin(16, 2);
}

void loop() {
 //성별 정하기
 sex=0;
 age=0;
  if(sex==0){
    lcd.clear();
 lcd.home(); // 커서 이동
 lcd.print("Choose your sex");
 lcd.setCursor(0,1);
 lcd.print("(U)man");   //위로 하면 man
 lcd.setCursor(8,1);
 lcd.print("(D)woman");  //밑으로 하면 woman
 joyx = analogRead(A1);   //VRx - A1
 joyy = analogRead(A2);   //VRy - A2
 delay(200);
 if (joyx < 400) {
    sex = 1;  // man
  }
  else if (joyx > 600) {
    sex = 2;  // woman
  }
  delay(5000);
  }
  lcd.clear();
 lcd.home();
  if(sex == 1)
  lcd.print("man");
  else
  lcd.print("woman");
   delay(5000);
  //나이 정하기
   lcd.clear();
 lcd.home(); // 커서 이동
 if(age==0){
 lcd.print("Choose your age");
 lcd.setCursor(0,1);
 lcd.print("(L)18-35");  //왼쪽으로 하면 18-35세
 lcd.setCursor(8,1);
 lcd.print("(R)36-65");   //오른쪽으로 하면 36-65세
 joyx = analogRead(A1);   //VRx - A1
 joyy = analogRead(A2);   //VRy - A2
 delay(200);
  if (joyy < 400) {
    age = 1; //18-35세
  }
  else if (joyy > 600) {
    age = 2; //36-65세
  }
 delay(5000);
 }
 lcd.clear();
 lcd.home();
 if(age == 1)
  lcd.print("18-35");
  else
  lcd.print("36-65");
   delay(5000);
  //심박수 출력 10초
  /*
//bpm_total = 0;
// for(int i=0; i<5; i++){
//  lcd.clear();
// lcd.home();
 // int myBPM = pulseSensor.getBeatsPerMinute();
//  
 //   Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 //   Serial.print("BPM: ");                        // Print phrase "BPM: " 
 //   Serial.println(myBPM);                        // Print the value inside of myBPM. - 시리얼 모니터에
 //   lcd.setCursor(2,0);
 //   lcd.print("My Heartbeat");
//    lcd.print(i);
 //   lcd.createChar(4, heart);
   lcd.setCursor(4,1);
    lcd.write(byte(4));      //'♥' 출력
    lcd.print("BPM : ");
    bpm_total += myBPM;  //bpm 다 합하기
    lcd.print(myBPM);
    Serial.println(bpm_total);
    delay(500);

 }
 */
 int i = 1;
  int add =0;
  int new_b =0; int old_b=0;
 for(int k =0; k<100; k++){
  lcd.clear();
 new_b = digitalRead(7);
 if(new_b==LOW){
    if(new_b != old_b){
       add++;
      old_b=new_b;}
 }
 else if(new_b != old_b)
      old_b=new_b;
 lcd.setCursor(3,0);
 lcd.print("! PUSH !");
 Serial.println(add); 
  delay(100);

 }
 lcd.clear();
 lcd.setCursor(2,0);
  lcd.print("My Heartbeat");
  lcd.setCursor(2,1);
  lcd.print(add);
  lcd.print(" times");
  
  
   delay(5000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Your health is..");
lcd.setCursor(0,1);
    if(add >= 8)  //심박수 표를 기준으로 범위 4개로 나누기(평균 이상, 평균, 평균 이하, 나쁨)
       lcd.print("PERPECT ! :D");
     else if(add >= 5 && add <= 7)
       lcd.print("NOMAL ~ :>");
     else if(add >= 2 && add <= 4) 
       lcd.print("below average :(");
     else lcd.print("bad! --^");
  
  
   /*
int bpm_avg = bpm_total/5;  // bpm 10초 동안 평균
Serial.println(bpm_avg);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Your health is..");
lcd.setCursor(0,1);
if(sex == 1){   //man
  if(age == 1){  //18-35세
    if(bpm_avg <= 70)  //심박수 표를 기준으로 범위 4개로 나누기(평균 이상, 평균, 평균 이하, 나쁨)
       lcd.print("PERPECT ! :D");
     else if(bpm_avg >= 71 && bpm_avg <= 74)
       lcd.print("NOMAL ~ :>");
     else if(bpm_avg >= 75 && bpm_avg <= 81) 
       lcd.print("below average :(");
     else lcd.print("bad! --^");
  }
  else {  // 36-65세
   if(bpm_avg <= 71) 
      lcd.print("PERPECT ! :D");
    else if(bpm_avg >= 72 && bpm_avg <= 76)
      lcd.print("NOMAL ~ :>");
    else if(bpm_avg >= 76 && bpm_avg <= 83) 
      lcd.print("below average :(");
      else lcd.print("bad! --^");
      }
  }
if(sex == 2){    // woman
  if(age == 1){  //18-35세
    if(bpm_avg <= 73) 
      lcd.print("PERPECT ! :D");
    else if(bpm_avg >= 74 && bpm_avg <= 77)
      lcd.print("NOMAL ~ :>");
    else if(bpm_avg >= 78 && bpm_avg <= 83) 
      lcd.print("below average :(");
    else lcd.print("bad! --^");
  }
  else {  // 36-65세
   if(bpm_avg <= 73) 
      lcd.print("PERPECT ! :D");
    else if(bpm_avg >= 74 && bpm_avg <= 78)
      lcd.print("NOMAL ~ :>");
    else if(bpm_avg >= 79 && bpm_avg <= 84) 
      lcd.print("below average :(");
      else lcd.print("bad! --^");
      }
   }
   */
delay(5000);
}
