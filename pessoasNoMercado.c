const int trigPin = 4;
const int echoPin = 5;
const int botaoContador = 7;
const int piezo = 9;
const int ledRed = 2;
const int ledYellow = 13;
const int ledGreen = 12;
const int distanciaParede = 40;
long duracao, distancia;
int pessoas = 0;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(botaoContador, INPUT);
  pinMode(piezo, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
}

void contagemPessoas(){
  if(pessoas <= 5){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
  } else if(pessoas > 5 && pessoas <=10){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
  } else if(pessoas > 10){
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    tone(piezo, 1000);
  }
  
  if(digitalRead(botaoContador) == HIGH){
    pessoas--;
    delay(100);
  }
  
  if(pessoas < 0){
    pessoas = 0;
  }
}

void medidorPessoas(){
  if(distancia < distanciaParede){
    pessoas++;
    delay(100);
  }
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracao = pulseIn(echoPin, HIGH);
  
  distancia = (duracao/2) / 29.1;
  delayMicroseconds(10);

  Serial.print(distancia);
  Serial.println(" cm");
  Serial.println(pessoas);
  
  contagemPessoas();
  medidorPessoas();
}