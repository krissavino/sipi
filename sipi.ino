#include <Wire.h>                             // библиотека для протокола I2C
#include <LiquidCrystal_I2C.h>       // библиотека для LCD 1602 
LiquidCrystal_I2C LCD(0x27,20,2);  // присваиваем имя дисплею

int mq3;

void setup() {
  pinMode(A1, INPUT);    // пин для подключения сенсора
  analogWrite(A1, LOW);

  Serial.begin(9600);        // запускаем монитор порта
  LCD.init();                        // инициализация дисплея
  LCD.backlight();              // включение подсветки


  //кнопка
  pinMode(9, INPUT);   
  pinMode(8, OUTPUT);   
  digitalWrite(8, HIGH);
  //rgb
  pinMode(10, OUTPUT);   
  pinMode(11, OUTPUT);   
  //buzzer
  pinMode(12, OUTPUT); 
  Serial.begin(9600); // open the serial port at 9600 bps:
 }

  
int val = 0;
int count = 0;
int sum = 0;
bool isTurnedOn = false;

void checkTurnedOn() {
  val = digitalRead(9);
  sum += val;
  count++;
  if(count > 10) {
    if(sum < 10)
      isTurnedOn = false;
    else
      isTurnedOn = true;
    count = 0;
    sum = 0;
  }
  if(isTurnedOn == false) {
    delay(200);
  }
}

void loop() {
  checkTurnedOn();

  if(isTurnedOn) {
    mq3 = analogRead(A1);   // считываем данные с порта A1

    Serial.print("Alcohol: ");
    Serial.println(mq3);          // выводим значение на монитор

    LCD.setCursor(0,0);          // ставим курсор на 1 символ первой строки
    LCD.print("Alcohol: ");
    LCD.print(mq3);                // выводим значение на дисплей

    delay(500);
    LCD.clear();  // очищаем экран дисплея

    if(mq3 > 2) {
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      tone(12, 100);
    } else {
      digitalWrite(11, HIGH);
      digitalWrite(10, LOW);
    }
  } else {
    LCD.clear();  // очищаем экран дисплея
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    noTone(12);
  }
}