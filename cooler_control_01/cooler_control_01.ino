
#define FAN_PIN  2

int countPulses;
int rpm;

int fan_hall_sensor = 2;

void setup()
{
  pinMode(FAN_PIN, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, countTurns, RISING);
}

void countTurns () 
{
  countPulses++;
}


void showRPM ( int rpm ) 
{
  Serial.print(rpm);
  Serial.println(" rmp");
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



  
