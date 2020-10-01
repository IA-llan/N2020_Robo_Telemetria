#include <Servo.h>
//Declaracao dos servos motores
Servo mcotovelo; 
Servo mpulso;

//Variavel pulso_robo declarada como falsa
bool pulso_robo = false;

//Definido porta 11 como echoPin
#define echoPin 11
//definido porta 10 como trigPin
#define trigPin 10

//Determinadas as variaveis 
String entrada;
long tempo;
int dist;

int motor1_h = 6;
//motor superior sentido horario
int motor1_ah = 5;
//motor superior sentido antihorario
int motor2_ah = 4;
//motor inferior sentido horario
int motor2_h = 3;
//motor inferior sentido antihorario

void setup()
{
  Serial.begin(9600); //Inicia a comunicacao com o monitor serial
  Serial.println("Digite o comando para mover o braco, e, t ou x !");
  
  //define as portas para o sensor de distancia 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
 
  //define as saidas que controlam a diracao dos motores
  pinMode(motor1_h, OUTPUT);
  pinMode(motor1_ah, OUTPUT);
  pinMode(motor2_h, OUTPUT);
  pinMode(motor2_ah, OUTPUT);
}

void loop()
{
  //SENSOR DISTANCIA
  
  digitalWrite(trigPin, LOW); //Desliga o trigger do sensor
   delay(2);
  digitalWrite(trigPin, HIGH); //Liga o trigger do sensor gerando um pulso sonoro
   delay(10);
  digitalWrite(trigPin, LOW); //Desliga o trigger novamente
  
  tempo = pulseIn(echoPin, HIGH); //A variavel tempo recebe o valor da demora para um pulso
    
  dist = (tempo * 0.0343)/2; //Calculo para descobrir a distancia
  
  Serial.println(String("Distancia de um objeto: ") + dist + String("cm"));
    delay(2000);
 
  /*Caso a distancia for menor que 60cm, todos os motores das rodas
  vao ser desligados para nao oferecer nenhum risco a colidir em algo*/
  if(dist < 60)
    {
      digitalWrite(motor1_h,LOW);
      digitalWrite(motor1_ah,LOW);
      digitalWrite(motor2_h,LOW);
      digitalWrite(motor2_ah,LOW);
    }

  //BRACO MECANICO E MOTORES DA RODA
  if(Serial.available() > 0)
  {
    entrada = Serial.readString(); //A variavel entrada recebe o valor digitado no monitor serial
    /*
    seta o veiculo para ir para frente,para isso, 
    o motor 1 deve estar no sentido antihorario e o motor 2
    como horario
     */
    if(entrada == "f" || entrada == "F")
    {
      if(dist > 40) //Para que o motor seja ligado é necessario que nao possua nada em uma distancia de 40cm
      {
        Serial.println("Indo para frente:");
       digitalWrite(motor1_h,LOW);
       digitalWrite(motor1_ah,HIGH);
       digitalWrite(motor2_h,HIGH);
       digitalWrite(motor2_ah,LOW);
      }
    }
    /*
    seta o veiculo para tras,para isso, 
    o motor 1 deve estar com sentido horario e o motor 2
    como antihorario
    */
    else if(entrada == "b" || entrada == "B")
    {
       Serial.println("Indo para tras:");
      digitalWrite(motor1_h,HIGH);
      digitalWrite(motor1_ah,LOW);
      digitalWrite(motor2_h,LOW);
      digitalWrite(motor2_ah,HIGH);
    }
    /*
    seta o veiculo para ir para a direita,para isso, 
    o motor 1 deve estar no sentido antihorario e o motor 2
    desligado
   */
    else if(entrada == "r" || entrada == "R")
    {
       Serial.println("Indo para direita:");
      digitalWrite(motor1_h,LOW);
      digitalWrite(motor1_ah,HIGH);
      digitalWrite(motor2_h,LOW);
      digitalWrite(motor2_ah,LOW);
   }
   /*
    seta o veiculo para ir para a esquerda,para isso, 
    o motor 1 deve estar desligado e o motor 2
    no sentido horario
   */
    else  if(entrada == "l" || entrada == "L")
   {
       Serial.println("Indo para esquerda:");
      digitalWrite(motor1_h,LOW);
      digitalWrite(motor1_ah,LOW);
      digitalWrite(motor2_h,HIGH);
      digitalWrite(motor2_ah,LOW);
   }
    //seta o veiculo para desligar todos os motores das rodas
    else if(entrada  == "s" || entrada == "S")
    {
        Serial.println("Parando todos os motores das rodas");
      digitalWrite(motor1_h,LOW);
      digitalWrite(motor1_ah,LOW);
      digitalWrite(motor2_h,LOW);
      digitalWrite(motor2_ah,LOW);
    }
   //caso nao se observe os anteriores, motores sao desligados
   else{
      digitalWrite(motor1_h,LOW);
      digitalWrite(motor1_ah,LOW);
      digitalWrite(motor2_h,LOW);
      digitalWrite(motor2_ah,LOW);
   }
    //Controles voltados para o braco do robo
    if(entrada == "e" || entrada == "E")//Caso o valor digitado seja e, o braco sera estendido
    {
      Serial.println("Estendendo o braco:");
       mcotovelo.attach(9);
       mcotovelo.write(90);
         delay(15);
    }
    else if(entrada == "t" || entrada == "T")//Caso o valor digitado seja t, o braco sera retraido
    {
     Serial.println("Retraindo o braco:");
       mcotovelo.attach(9);
       mcotovelo.write(0);
        delay(15);
    }
    /*Caso o valor digitado seja x, o pulso ira girar 180 graus 
    para alternar entre termometro e medidor de pressao*/
    else if(entrada == "x" || entrada == "X")
    {
      if(pulso_robo == false)
      {
      Serial.println("Girando o pulso:");
      mpulso.attach(8);
      mpulso.write(180);
        delay(15);
        pulso_robo = !pulso_robo;
      }
      else
      {
      Serial.println("Voltando pulso:");
        mpulso.attach(8);
        mpulso.write(0);
        delay(15);
        pulso_robo = !pulso_robo;
      }
    }
  }
}
