/**
 * 受信用
 */

/**
char latastRecv[255];
int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  while(Serial.available()){    // 受信中
    char inChar = char(Serial.read());
    latastRecv[counter] = inChar;   // データをバッファに保存
    counter++;
    if(inChar == '\0'){   // null文字が来たら受信データを表示
      Serial.println(latastRecv);
      counter = 0;
    }
  }
}
*/
#include <SoftwareSerial.h>
// #include <LiquidCrystal_I2C.h>
SoftwareSerial TWE(2, 3);  // RX, TX
#define LED LED_BUILTIN

// const char disp_spd_str_x = 0;        //速度表示位置 (LCD用)
// const char disp_spd_str_y = 0;
// const char disp_spd_val_x = 0;
// const char disp_spd_val_y = 1;
unsigned long pastReceiveTime = 0;

// LiquidCrystal_I2C lcd(0x27, 16, 2);   //I2Cアドレスの設定

void setup() {
  TWE.begin(38400);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  // lcd.begin();                    //液晶ディスプレイの初期化
  // lcd.backlight();      
}


void loop() {
  static char recv[60] = {};
  static byte count = 0;
  static char latastRecv = 0;

  // Initialization
  // for (int i = 0; i < 60; ++i) recv[i] = 0;
  latastRecv = 0;

  // Receives data
  while (TWE.available()) {
    // digitalWrite(LED, HIGH);
    // Serial.print("available");
    latastRecv = (char)TWE.read();
    Serial.print(latastRecv);
    if (latastRecv == ':') {
      count = 0;
    }
    recv[count] = latastRecv;
    ++count;
    // Serial.print(count);
  }
  if (count && recv[3] == '0' && recv[4] == '1') {
    digitalWrite(LED, HIGH);
    pastReceiveTime = millis();
    for (byte i = 0; i != count; ++i) {
      // Serial.print("(");
      // Serial.print(i);
      // Serial.print(")");
      Serial.print(recv[i]);
    }
  }
  // 最後の送信から1 s以上経過しているとき、タイムアウト判定
  if (millis() - pastReceiveTime < 1000){
    if(count && recv[3] == '0' && recv[4] == '1'){
      // lcd.setCursor(disp_spd_str_x, disp_spd_str_y);
      // lcd.print("SPD");
      // lcd.setCursor(disp_spd_val_x, disp_spd_val_y);  //カーソル指定
      // lcd.print(recv[9]);
      // lcd.print(recv[10]);
      // lcd.print(".");
      // lcd.print(recv[11]);
    }
  } else {
      // lcd.setCursor(disp_spd_str_x, disp_spd_str_y);
      // lcd.print("SPD");
      // lcd.setCursor(disp_spd_val_x, disp_spd_val_y);  //カーソル指定
      // lcd.print("TOUT");
    }
  digitalWrite(LED, LOW);
}
