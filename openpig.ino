#include <Servo.h>

int LDR1; //Variável para a leitura do LDR1
int cont1; //Variável utilizada para armazenar os valores lidos pelo sensor
int LDR2; //Variável para a leitura do LDR2
int cont2; //Variável utilizada para armazenar os valores lidos pelo sensor
int LDR3; //Variável para a leitura do LDR3
int cont3; //Variável utilizada para armazenar os valores lidos pelo sensor
int LDR4; //Variável para a leitura do LDR4
int cont4; //Variável utilizada para armazenar os valores lidos pelo sensor
int i; //Variável para contagem
Servo myservo;  // objeto para controlar o servo1
Servo dispenser; // objeto para controlar o servo2

void setup()
{
  Serial.begin(9600); //Inicia a serial
  myservo.attach(9);  // inicia o servo1 no pino 9
  myservo.write(80);  // posiciona o servo1 na posicao 80 (porta aberta)
  dispenser.attach(8); // inicia o servo2 no pino8
  dispenser.write(120); // posiciona o servo2 na posicao 120
  delay(2000);

}

void servo_inicio()
{
  myservo.write(22);
}

void servo_libera()
{
  myservo.write(80);
}


void loop()
{
  //Serial.println("Inicio do programa"); // utilizado para debug
  servo_inicio();

  LDR1 = 0; //Zera a variável LDR1
  LDR2 = 0; //Zera a variável LDR2
  LDR3 = 0; //Zera a variável LDR3
  LDR4 = 0; //Zera a variável LDR4

  for (i = 0; i <= 10; i++) //Faz 10 vezes a leitura do sensor
  {
    cont1 = analogRead(A0); //Lê o valor do sensor (LDR1 ligado ao pino A0) e guarda na variável cont1
    cont2 = analogRead(A1); //Lê o valor do sensor (LDR2 ligado ao pino A1) e guarda na variável cont2
    cont3 = analogRead(A2); //Lê o valor do sensor (LDR3 ligado ao pino A2) e guarda na variável cont3
    cont4 = analogRead(A3); //Lê o valor do sensor (LDR4 ligado ao pino A3) e guarda na variável cont4
    LDR1 = LDR1 + cont1; //Armazenamento na varíavel LDR1 o valor lido + o valor anterior
    LDR2 = LDR2 + cont2; //Armazenamento na varíavel LDR2 o valor lido + o valor anterior
    LDR3 = LDR3 + cont3; //Armazenamento na varíavel LDR3 o valor lido + o valor anterior
    LDR4 = LDR4 + cont4; //Armazenamento na varíavel LDR4 o valor lido + o valor anterior
    delay(10); //Delay se 10 milissegundos
  }
  LDR1 = LDR1 / 10; //Divide o valor armazenado por 10
  LDR2 = LDR2 / 10; //Divide o valor armazenado por 10
  LDR3 = LDR3 / 10; //Divide o valor armazenado por 10
  LDR4 = LDR4 / 10; //Divide o valor armazenado por 10

  // verifica se alguma moeda foi inserida
  if (LDR1 <= 900  || LDR2 <= 900 || LDR3 <= 900 || LDR4 <= 800) {
    Serial.println("Detectado moeda");
    delay(500);
    LDR1 = 0; //Zera a variável LDR1
    LDR2 = 0; //Zera a variável LDR2
    LDR3 = 0; //Zera a variável LDR3
    LDR4 = 0; //Zera a variável LDR4
    for (i = 0; i <= 10; i++) //Faz 10 vezes a leitura do sensor
    {
      cont1 = analogRead(A0); //Lê o valor do sensor (LDR1 ligado ao pino A0) e guarda na variável cont1
      cont2 = analogRead(A1); //Lê o valor do sensor (LDR2 ligado ao pino A1) e guarda na variável cont2
      cont3 = analogRead(A2); //Lê o valor do sensor (LDR3 ligado ao pino A2) e guarda na variável cont3
      cont4 = analogRead(A3); //Lê o valor do sensor (LDR4 ligado ao pino A3) e guarda na variável cont4
      LDR1 = LDR1 + cont1; //Armazenamento na varíavel LDR1 o valor lido + o valor anterior
      LDR2 = LDR2 + cont2; //Armazenamento na varíavel LDR2 o valor lido + o valor anterior
      LDR3 = LDR3 + cont3; //Armazenamento na varíavel LDR3 o valor lido + o valor anterior
      LDR4 = LDR4 + cont4; //Armazenamento na varíavel LDR4 o valor lido + o valor anterior
      delay(10); //Delay se 10 milissegundos
    }
    LDR1 = LDR1 / 10; //Divide o valor armazenado por 10
    LDR2 = LDR2 / 10; //Divide o valor armazenado por 10
    LDR3 = LDR3 / 10; //Divide o valor armazenado por 10
    LDR4 = LDR4 / 10; //Divide o valor armazenado por 10
    // debug - desativado por enquanto
    Serial.print(LDR1);
    Serial.print(";");
    Serial.print(LDR2);
    Serial.print(";");
    Serial.print(LDR3);
    Serial.print(";");
    Serial.println(LDR4);
    //     verifica se é moeda de 1 real
    if (LDR1 >= 900 && LDR2 >= 100 && LDR2 <= 350 && LDR3 >= 100 && LDR3 <= 650 && LDR4 >= 800) {
      Serial.println("Moeda 1 real");
      dispenser.write(130);
      servo_libera();
      delay(200);
      servo_inicio();
      delay(300);
    }
    // verifica se é moeda de 25c
    if (LDR1 >= 800 && LDR2 >= 150 && LDR2 <= 450 && LDR3 >= 800 && LDR3 <= 900 && LDR4 >= 800) {
      Serial.println("Moeda 25 centavos");
      dispenser.write(100);
      //myservo.write(80);
      servo_libera();
      delay(200);
      servo_inicio();
      delay(300);
    }
    // verifica se é moeda de 50c
    if (LDR1 >= 400 && LDR1 <= 900 && LDR2 >= 700 && LDR2 <= 900 && LDR3 >= 900 && LDR4 >= 800) {
      Serial.println("Moeda 50 centavos");
      dispenser.write(80);
      servo_libera();
      delay(200);
      servo_inicio();
      delay(300);
    }
    // verifica se é moeda de 10c
    if (LDR1 >= 200 && LDR1 <= 550 && LDR2 >= 900 && LDR3 >= 900 && LDR4 >= 800) {
      Serial.println("Moeda 10 centavos");
      dispenser.write(70);
      servo_libera();
      delay(200);
      servo_inicio();
      delay(300);
    }

  }
}
