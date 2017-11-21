// Este ejemplo demuestra que el motor 28BYJ-48 opera de forma
// bidireccional, usando un módulo ULN2003.
//La frecuencia de operación es 100Hz. Y la corriente de 92mA. 
////////////////////////////////////////////////

//declaración de las variables para los pines del motor
// motor 1
int motorPin11 = 4;    // Azul   - 28BYJ48 pin 1 motor
int motorPin12 = 5;    // Rosa   - 28BYJ48 pin 2 motor
int motorPin13 = 6;    // Amarillo - 28BYJ48 pin 3 motor
int motorPin14 = 7;    // Naranja - 28BYJ48 pin 4 motor

// motor 2
int motorPin21 = 8;
int motorPin22 = 9;
int motorPin23 = 10;
int motorPin24 = 11;

int motorSpeed = 1500;  //variable para fijar la velocidad del motor (el retraso entre cada secuencia) Original = 1200 
int counts = 500;          // cuenta de los pasos dados
int countsL = 1000; // número de pasos por vuelta completa
int rewindSteps = 500;

bool limitM = false;
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
int delayTime = 250;
int verticalDelay = 400;
int steps = 10;
int verticalSteps = 20;

// Acelerometro
int x; // x axis variable
int y; // y axis variable
int z; // z axis variable
double angleYZ = 0;
double angleXZ = 0;

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
  int chosenDelay;
  refresh();
  // prints();
  readAngle();
  
  for (int i=0; i < 6; i++){
    if ((maxi + 50) < values [i]){
     maxi = values [i];
     pos = i;
    } 
  }

  switch (pos) {
    case 0:
      north();
      chosenDelay = verticalDelay;
      break;
      
    case 1:
      northWest();
      chosenDelay = delayTime;
      break;
      
    case 2:
      southWest();
      chosenDelay = delayTime;
      break; 
          
    case 3:
      south();
      chosenDelay = verticalDelay;
      break;
      
    case 4:
      southEast();
      chosenDelay = delayTime;
      break;  
         
    case 5:
      northEast();
      chosenDelay = delayTime;
      break;
      
    case 6: //arriba
      UP();
      chosenDelay = delayTime;
      break; 

  }
  delay(chosenDelay);
}


//creación funciones giro horario y antihorario
void anticlockwise1() 
{
  for(int i = 0; i <= 7 ; i++)
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
  for(int i = 0; i <= 7; i++)
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
  limitM = false;
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
  for(int i = 0; i < verticalSteps; i++)
  {
    if (isValidAngle()) {
      anticlockwise1();
    } else {
      clockwise1();
    }
  }
}

void northWest() //función secuencia giro
{
  int i = 0;
  while(i < steps && !limitM){
    anticlockwise2();
    limit ();
    counts ++;
    i ++;
  }
}


void southWest() //función secuencia giro
{
  int i = 0;
  while(i < steps && !limitM){
    clockwise2();
    limit ();
    counts --;
    i ++;
  }
}

void south() //función secuencia giro
{
  for(int i = 0; i < verticalSteps; i++)
  {
    if (isValidAngle()) {
     clockwise1(); 
    } else {
      anticlockwise1();
    }
  }
}

void southEast() //función secuencia giro
{
  int i = 0;
  while(i < steps && !limitM){
    anticlockwise2();
    limit ();
    counts ++;
    i ++;
  }
}

void northEast() //función secuencia giro
{
  int i = 0;
  while(i < steps && !limitM){
    clockwise2();
    limit ();
    counts --;
    i ++;
  }
}

void UP() //función secuencia giro
{
  delay(delayTime);
}

void limit ()
{
  if (counts > countsL)
  {
    for(int i = 0; i < rewindSteps; i++)
    {
      clockwise2();
      counts --;  
    }
    limitM = true;
  } 
  if (counts < 0)
  {
    for(int i = 0; i < rewindSteps; i++)
    {
      anticlockwise2();
      counts ++;
    }
    limitM = true;
  } 

   Serial.println("############");
   Serial.println(counts);
}

void readAngle() {
  x = analogRead(8);
  y = analogRead(9);
  z = analogRead(10);

  /*Para calcular angulos*/
   x = map(x, 0, 1023, -500, 500);
   y = map(y, 0, 1023, -500, 500);
   z = map(z, 0, 1023, -500, 500);

   angleYZ = atan((double)y / (double)z);
   angleYZ = angleYZ*(57.2958);

   angleXZ = atan((double)x / (double)z);
   angleXZ = angleXZ*(57.2958);
   delay(delayTime);
}

bool isValidAngle() {
  if (angleXZ <= 10 or angleYZ <= 10) {
    return false;
  } else {
    return true;
  }
}

