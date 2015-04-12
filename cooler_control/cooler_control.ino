

/*
  Portiguese: 
  
    Moniroramento da velocidade em RPM de um ventilador utilizando em cooler de CPU
  
  English...:
  
    Monitoring the speed (RPM) of a CPU cooler   
  
  Reference:

  About Hall Sensor

  http://en.wikipedia.org/wiki/Hall_effect_sensor
  http://pcbheaven.com/wikipages/The_Hall_Sensor/  
  

  About CPU cooler
  
  http://en.wikipedia.org/wiki/Computer_fan
  http://pcbheaven.com/wikipages/How_PC_Fans_Work/

*/

// Portugues: Pino que sera conectado a fio de sinal do ventilador (em geral amarelo)
// English..: The pin that will be connected the yellow (usually) wire of the fan

#define FAN_PIN  2

//Varibles used for rpmulations
int countPulses;
int rpm;

// Portuguese: fan_hall_sensor indica o comportamento do sensor do ventilador utilizado. Em geral pode ser 1, 2 ou 8 pulsos gerados por volta.
//             Voce deve verificar essa informacao na descricao do fabricante do cooler e ajustar o valor desta variavel. 
// Emglish...: fan_hall_sensor tell to the system how many pulses are generated by turns.
//             You should verify it by reading the tehcnical specification of the cooler.
//             In general, it can be 1, 2 or 8 pulses per turn.

int fan_hall_sensor = 4;


void setup()
{
  
  pinMode(FAN_PIN, INPUT);
  Serial.begin(9600);
  
  // Portugues: Conecta a funcao countTurns a interrupcao 0
  // English..: Attach interrupt 0 to the countTurn function
  attachInterrupt(0, countTurns, RISING);
}


/* countTurns 
 Portugues: Esta funcao eh executada a cada interrupcao
 English..: This function is executed every pulse get from cooler
 
*/ 
void countTurns () 
{
  countPulses++;
}


/* showRPM

 Portuguese: Apresenta a velocidade em RPM (Veja no menu Tools "Serial Monitor")
 English...: This function shows the current fan speed in RPM (See "Serial Monitor" on Tools Menu) 

*/
void showRPM ( int rpm ) 
{
  Serial.print(rpm);
  Serial.println(" rmp");
}


void loop ()
{
  countPulses = 0; 
  
  // Portuguese: Habilita interupcoes e para o fluxo desta funcao (loop) por 1 segundo.
  //             Enquanto isso, a funcao countTurns () sera executada a cada pulso.
  // English...: Enable interrupts and stop this loop (function loop) for one secound. 
  //             Meanwhile the countTurns () funcion will be called for each pulse.
  sei(); 
  delay (1000); 
  
  // Portuguese: Desabilita interrupcoes.
  // English...: Disable interrupts
  cli(); 
  
  // Portuguese: rpm armazena o valor calculado do numero de voltas por MINUTO do ventilador. 
  // English...: rpm stores  the number of turns per minute of the fan.
  rpm = (countPulses / fan_hall_sensor) * 60; // * 60 here convert from seconds (delay(1000) above) to minutes;
  showRPM(rpm); 
}



  
