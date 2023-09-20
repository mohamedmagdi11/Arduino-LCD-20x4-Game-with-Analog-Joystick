
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20,4);



int joyXpin = A1; 
int joyYpin = A0; 

int arrowX = 0; 
int arrowY = 3; 
byte score = 0 ;
byte row ;
int deadband = 100;


unsigned long time;
unsigned long currentTime;
bool millisCounter = false;


byte pl[8] = {
	0b01110,
	0b10001,
	0b11011,
	0b10101,
	0b11111,
	0b01110,
	0b01110,
	0b01010
};

byte fee[8] = {
	0b00000,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b01110,
	0b00000
};






int x=0;
int y=3;
void setup() {

  Serial.begin(9600);
  pinMode(joyXpin, INPUT);
  pinMode(joyYpin, INPUT);
 

lcd.init();
lcd.backlight();

  lcd.createChar(0, pl);
  lcd.createChar(1, fee);

  lcd.setCursor(0,3);
  lcd.write(0);
  
  


}




void player() {

int joyX = analogRead(joyXpin);
  int joyY = analogRead(joyYpin);

  if (joyX < (512 - deadband) && arrowX > 0) {
    lcd.setCursor(arrowX, arrowY);
    lcd.print(" ");
    arrowX--;
    lcd.setCursor(arrowX, arrowY);
    lcd.write((byte)0);
    delay(200);
  }
  if (joyX > (512 + deadband) && arrowX < 19) {
    lcd.setCursor(arrowX, arrowY);
    lcd.print(" ");
    arrowX++;
    lcd.setCursor(arrowX, arrowY);
    lcd.write((byte)0);
    delay(200);
  }
  if (joyY < (512 - deadband) && arrowY > 0) {
    lcd.setCursor(arrowX, arrowY);
    lcd.print(" ");
    arrowY--;
    lcd.setCursor(arrowX, arrowY);
    lcd.write((byte)0);
    delay(200);
  }
  if (joyY > (512 + deadband) && arrowY < 3) {
    lcd.setCursor(arrowX, arrowY);
    lcd.print(" ");
    arrowY++;
    lcd.setCursor(arrowX, arrowY);
    lcd.write((byte)0);
    delay(200);
  }
}



void loop() {
   row = random(4);

for(int i =20 ; i>=0 ; i--)
{
lcd.setCursor(i,row);
lcd.write(1);
player();


if((arrowX == i) && (arrowY == row))
{

score++;
Serial.println(score);
lcd.setCursor(arrowX,arrowY);
     lcd.write(byte(0));
     i = 19;
     break;

}

if((arrowX == (i-1)) && (arrowY == row))
{
lcd.setCursor(i,row);
lcd.write(1);
lcd.setCursor(arrowX,arrowY);
lcd.write(0);
for(int t = 0;t<=7000;t++)
     {
      if(millisCounter == false)
     {
      time = millis();
      millisCounter = true;
     }
     player();
     currentTime = millis() - time;
     if(currentTime >= 3000)
     {

Serial.println("Game Over");
delay(500);
   lcd.clear();
score = 0;
 arrowX = 0 ;
 arrowY = 3 ;
 i =20 ;

 millisCounter = false;
lcd.setCursor(0,3);
lcd.write(0);

row = random(4);
break ;

     }
     if((arrowX == i) && (arrowY == row))
{

score++;
Serial.println(score);
lcd.setCursor(arrowX,arrowY);
     lcd.write(byte(0));
     i = 19;
            millisCounter = false;
row =random(4);
     break;

}
delay(1);
}
}
 delay(200);
    lcd.setCursor(i,row);
    lcd.print(" ");
    player();
    if(i==0)break;
}
}




