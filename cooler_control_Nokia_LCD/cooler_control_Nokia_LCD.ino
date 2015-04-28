
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define FAN_PIN  2

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);

int countPulses;
int rpm;

int fan_hall_sensor = 4;

void setup()
{
  pinMode(FAN_PIN, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, countTurns, RISING);

  display.begin();
  display.setContrast(45);
}

void countTurns ()
{
  countPulses++;
}


void showRPM ( int rpm )
{

  display.clearDisplay();
  display.setCursor(20, 0);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println("Speed");
  display.setCursor(15, 8);
  display.setTextSize(2);
  display.println(rpm);
  display.setCursor(24, 20);
  display.println("rpm");  
  display.display();
}


void loop ()
{
  countPulses = 0;

  sei();
  delay (1000);

  cli();

  rpm = (countPulses / fan_hall_sensor) * 60;
  showRPM(rpm);
}




