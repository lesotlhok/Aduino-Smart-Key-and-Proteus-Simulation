# 1 "C:\\Users\\Koorapetse Lesotlho\\Desktop\\Smart Key\\smartkey\\smartkey.ino"
# 2 "C:\\Users\\Koorapetse Lesotlho\\Desktop\\Smart Key\\smartkey\\smartkey.ino" 2
# 3 "C:\\Users\\Koorapetse Lesotlho\\Desktop\\Smart Key\\smartkey\\smartkey.ino" 2
# 4 "C:\\Users\\Koorapetse Lesotlho\\Desktop\\Smart Key\\smartkey\\smartkey.ino" 2

LiquidCrystal lcd(8,9,10,11,12,13);
SoftwareSerial SIM900(7,8);
TinyGPS gps;

float flat, flon;
unsigned long age;
int buttonPin = 7;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, 0x0);
  SIM900.begin(9600);
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Smart Key GPS");
  delay(2000);

}

void loop() {
  buttonState = digitalRead(buttonPin);

  bool newdata = false;
  unsigned long chars;
  unsigned short sentences, failed;


for(unsigned long start = millis (); millis () -start < 1000;)

  {
    while(Serial.available()){
      char c = Serial.read();
      if(gps.encode(c));
      newdata = true;
      }
   }
  if(newdata){
    gps.f_get_position (&flat, &flon, &age);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Smart Key GPS");
    lcd.setCursor(0,1);
    lcd.print("YOUR GPS LOCATION");
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LATITUDE:");lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    lcd.setCursor(0,1);
    lcd.print("LONGITUDE:");lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);



    }
  if(buttonState == 0x0){
    SendMessage();

    }
    else if(buttonState == 0x1){

        noMessage();
        }



  delay(2000);

}


void SendMessage(){

    SIM900.println("AT+CMGF=1");
    SIM900.println("Message from SMART KEY GPS System..");
    SIM900.println("AT+CMGS=\"+267 72500000\"\r");
    SIM900.println("Smart Key GPS");
    SIM900.println("-----------------------------------");
    delay(100);
    SIM900.println("YOUR GPS LOCATION");
    delay(100);
    SIM900.println("LATITUDE:");
    SIM900.println(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    SIM900.println("LONGITUDE:");
    SIM900.println(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    SIM900.println((char)26);
    delay(100);


  }
void noMessage(){
  SIM900.println(" ");
  }
