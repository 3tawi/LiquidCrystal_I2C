// - Lien vidéo: https://youtu.be/9XcizjmSZNY
// - Time Library: https://github.com/3tawi/PicoEspTime
// - LiquidCrystal I2C Library: https://github.com/3tawi/LiquidCrystal_I2C
// - Getting Started Raspberry Pi Pico : https://youtu.be/KiM6-Hmxf3s
// - Find All "Great Projects" Videos : https://www.youtube.com/c/GreatProjects

#include <PicoEspTime.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
PicoEspTime rtc;

uint32_t lastTime; 
String   texttime;
bool     flasher;

void setup() {
  lcd.init();   
  lcd.backlight();    
  Serial.begin(115200);
  rtc.adjust(13, 16, 30, 2022, 6, 4); // 01:28:30 04 Jun 2022
// rtc.adjust(1654219721); // Friday, June 03 2022 01:28:41
}
void loop() {
   if(millis() - lastTime >= 1000) {
    rtc.read(); 
    PrintTime();
    flasher = !flasher; 
    lastTime = millis();
    }
}
void PrintTime()
{ 
    Serial.println((flasher) ? rtc.getTime("%A, %d %B %Y %H %M:%S") : rtc.getTime("%A, %d %B %Y %H:%M:%S"));
// Serial.println(rtc.getTime("%A, %d %B %Y %H:%M:%S"));   // (String) returns time with specified format   
// formating options  https://www.cplusplus.com/reference/ctime/strftime/

    texttime = (flasher) ? rtc.getTime("%I %M:%S") : rtc.getTime("%I:%M:%S");
    lcd.setCursor(3,0);
    lcd.print(texttime);
    lcd.setCursor(14,0);
    lcd.print(rtc.getTime("%p"));
    lcd.setCursor(0,1);
    lcd.print(rtc.getTime("%a %d-%b-%Y"));
} 
