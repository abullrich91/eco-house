// Este ejemplo demuestra que el motor 28BYJ-48 opera de forma
// bidireccional, usando un módulo ULN2003.
//La frecuencia de operación es 100Hz. Y la corriente de 92mA. 
////////////////////////////////////////////////

//declaración de las variables para los pines del motor
// motor 1
int motorPin11 = 8;    // Azul   - 28BYJ48 pin 1 motor
int motorPin12 = 9;    // Rosa   - 28BYJ48 pin 2 motor
int motorPin13 = 10;    // Amarillo - 28BYJ48 pin 3 motor
int motorPin14 = 11;    // Naranja - 28BYJ48 pin 4 motor

// motor 2
int motorPin21 = 4;
int motorPin22 = 5;
int motorPin23 = 6;
int motorPin24 = 7;

int motorSpeed = 1500;  //variable para fijar la velocidad del motor (el retraso entre cada secuencia) Original = 1200 
int count = 0;          // cuenta de los pasos dados
int countsperrev = 512; // número de pasos por vuelta completa 
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

int sensorPin0 = A0; // select the input pin for LDR
int sensorPin1 = A1;
int sensorPin2 = A2;
int sensorPin3 = A3;
int sensorPin4 = A4;
int sensorPin5 = A5;
int sensorPin6 = A6;
int values [7] = {0,0,0,0,0,0,0};
int maxi = 0;
int pos = 6;


void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin11, OUTPUT);
  pinMode(motorPin12, OUTPUT);
  pinMode(motorPin13, OUTPUT);
  pinMode(motorPin14, OUTPUT);

  pinMode(motorPin21, OUTPUT);
  pinMode(motorPin22, OUTPUT);
  pinMode(motorPin23, OUTPUT);
  pinMode(motorPin24, OUTPUT);
  
  Serial.begin(9600);
}

void loop(){
  refresh();
  prints();

  
  for (int i=0; i < 6; i++){
    if ((maxi + 50) < values [i]){
     maxi = values [i];
     pos = i;
    } 
  }

  switch (pos) {
    case 0:
      north();
      break;
      
    case 1:
      northWest();
      break;
      
    case 2:
      southWest();
      break; 
          
    case 3:
      south();
      break;
      
    case 4:
      southEast();
      break;  
         
    case 5:
      northEast();
      break;
      
    case 6: //arriba
      UP();
      break; 

  }
  delay(1000);
   
}


//creación funciones giro horario y antihorario
void anticlockwise1() 
{
  for(int i = 0; i < 8; i++)
  {
    setOutput1(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise1()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput1(i);
    delayMicroseconds(motorSpeed);
  }
}

void anticlockwise2() 
{
  for(int i = 0; i < 8; i++)
  {
    setOutput2(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise2()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput2(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput1(int out) //función secuencia giro
{
  digitalWrite(motorPin11, bitRead(lookup[out], 0));
  digitalWrite(motorPin12, bitRead(lookup[out], 1));
  digitalWrite(motorPin13, bitRead(lookup[out], 2));
  digitalWrite(motorPin14, bitRead(lookup[out], 3));
}

void setOutput2 (int out) {
  digitalWrite(motorPin21, bitRead(lookup[out], 0));
  digitalWrite(motorPin22, bitRead(lookup[out], 1));
  digitalWrite(motorPin23, bitRead(lookup[out], 2));
  digitalWrite(motorPin24, bitRead(lookup[out], 3));
}

void refresh() //función secuencia giro
{
  values [0] = analogRead(sensorPin0); // read the value from the sensor
  values [1] = analogRead(sensorPin1);
  values [2] = analogRead(sensorPin2);
  values [3] = analogRead(sensorPin3);
  values [4] = analogRead(sensorPin4);
  values [5] = analogRead(sensorPin5);
  values [6] = analogRead(sensorPin6);

  maxi = values [6];
  pos = 6;

}

void prints() //función secuencia giro
{
  for (int i=0; i < 7; i++){
    Serial.println(values [i]); //prints the values coming from the sensor on the screen
  }
  Serial.println("############");
}


void north() //función secuencia giro
{
  /*for(int i = 0; i < 800; i++)
  {
     anticlockwise1();
  }*/
}

void northWest() //función secuencia giro
{
  for(int i = 0; i < 85; i++)
  {
    clockwise2();
  }
}


void southWest() //función secuencia giro
{
for(int i = 0; i < 85; i++)
  {
    anticlockwise2();
  }
}

void south() //función secuencia giro
{
  /*for(int e = 0; e < 10; e++){
    for(int i = 0; i < 50; i++)
    {
      anticlockwise2();
    }
    for(int i = 0; i < 50; i++)
    {
      clockwise1();
    }
  }*/
}

void southEast() //función secuencia giro
{
for(int i = 0; i < 85; i++)
  {
    clockwise2();
  }
}

void northEast() //función secuencia giro
{
for(int i = 0; i < 85; i++)
  {
    anticlockwise2();
  }
}

void UP() //función secuencia giro
{
  delay(1000);
}


