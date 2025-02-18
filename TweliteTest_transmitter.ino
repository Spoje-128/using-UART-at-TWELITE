/**
 * 子機(送信側)
 */
/**
String sendstr = "Hello World!!";

void setup() {
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i != sendstr.length(); i++){
    Serial.write(sendstr.charAt(i));
  }
  Serial.write(0);
  delay(1000);
}
*/
#include <SoftwareSerial.h>
// Arduino Uno用なのでUARTピンを指定 (HardwareSerialだと書き込み時にピンを抜かなければいけないので面倒)
SoftwareSerial TWE(2, 3);  // RX, TX
#define LED LED_BUILTIN


void setup() {
  TWE.begin(38400);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
#define DATA_SIZE 20 /*7*/
  // byte DATA[DATA_SIZE] = {':', 0x78, 0x01, 0x55, 0x58, '\r', '\n'};
  static byte DATA[DATA_SIZE] = { ':', '7', '8', '0', '1', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'E', 'X', '\r', '\n' }; ///< 送信パケット
  // static unsigned long lastMillis;
  // if (millis() - lastMillis > 500) {
  //   lastMillis = millis();
    // SPD (0.0 ~ 10.0)
    float spd = random(67, 75) / 10.0;
    int spdInt = (int)(spd * 10);
    DATA[5] = '0' + (spdInt / 100);
    DATA[6] = '0' + (spdInt / 10 % 10);
    DATA[7] = '0' + (spdInt % 10);

    // ALT (0.0 ~ 10.0)
    float alt = random(50, 80) / 10.0;
    int altInt = (int)(alt * 10);
    DATA[8] = '0' + (altInt / 100);
    DATA[9] = '0' + (altInt / 10 % 10);
    DATA[10] = '0' + (altInt % 10);

    // CDS (0 ~ 85)
    int cds = random(82, 87);
    DATA[11] = '0' + (cds / 10);  // CDSの10の位
    DATA[12] = '0' + (cds % 10);  // CDSの1の位

    byte flightNumber = 0;
    DATA[13] = '0' + flightNumber / 10 % 10;
    DATA[14] = '0' + flightNumber % 10;
  // }
  digitalWrite(LED, HIGH);
  // while (millis() - lastMillis < 500) {
  // DATA[11] = (byte)random(65, 75);
  for (byte i = 0; i < DATA_SIZE; ++i) TWE.write(DATA[i]);  // Tweliteに送信
  for (byte i = 0; i < DATA_SIZE; ++i) Serial.print((char)DATA[i]);
  Serial.println();
  // delay(10);
  // Serial.println("trasmit!!");
  // }

  // TWE.write(':');
  // TWE.write(0x78);
  // TWE.write(0x01);
  // TWE.write(0x55);

  // TWE.write('X');
  // TWE.write('\r');
  // TWE.write('\n');

  // TWE.print("X");
  // TWE.print("\r");
  // TWE.print("\n");
  delay(50);
  digitalWrite(LED, LOW);
}
