// Carro Bluetooth Arduino 
// Definindo os pinos do Driver L298.

const int motorA1  = 9;    // Pin A1-A ou (IN1) do Driver da ponte H.
const int motorA2  = 3;    // Pin A1-B ou (IN2) do Driver da ponte H.
const int motorB1  = 11;   // Pin B1-B ou (IN4) do Driver da ponte H.
const int motorB2  = 10;   // Pin B1-A ou (IN3) do Driver da ponte H.
const int atuador = 13 ;   // Define o Pino 13 como saída para algum atuador.
const int BTState = 2;    // Define o Pino 2 como o pino de comunicação do Bluetooth. (não necessário conectar, normalmente LOW)

// Variáveis Úteis
int i = 0;
int j = 0;
int state_rec;
int vSpeed = 200;   // Define velocidade padrão 0 < x < 255.
char state;

void setup() {
  // Inicializa as portas como entrada e saída.
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(atuador, OUTPUT);
  pinMode(BTState, INPUT);

  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
}

void loop() {
  // Para o robo quando a conexão com Bluetooth é perdida ou desconectada.
  if (digitalRead(BTState) == LOW) {
    state_rec = 'S';
  }

  // Salva os valores da variável 'state'
  if (Serial.available() > 0) {
    state_rec = Serial.read();
    state = state_rec;
    //   Serial.println(vSpeed);
  }

  // Altera a velocidade de acordo com valores recebidos via aplicativo bluetooth.
  if (state == '0') {
    vSpeed = 0;
  }
  else if (state == '4') {
    vSpeed = 100;
  }
  else if (state == '6') {
    vSpeed = 155;
  }
  else if (state == '7') {
    vSpeed = 180;
  }
  else if (state == '8') {
    vSpeed = 200;
  }
  else if (state == '9') {
    vSpeed = 230;
  }
  else if (state == 'q') {
    vSpeed = 255;
  }

  if (state != 'S') {
    Serial.print(state);
  }

  // Se o estado recebido for igual a 'F', o robo se movimenta para frente.
  if (state == 'F') {
    analogWrite(motorB1, vSpeed);
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB2, 0);
  }

    else if (state == 'I') {  // Se o estado recebido for igual a 'I', movimenta-se para Frente Esquerda.
    analogWrite(motorA1, vSpeed); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 100);    
    analogWrite(motorB2, 0);
  }

    else if (state == 'G') {   // Se o estado recebido for igual a 'G', movimenta-se para Frente Direita.
    analogWrite(motorA1, 100); 
    analogWrite(motorA2, 0);
    analogWrite(motorB1, vSpeed);      
    analogWrite(motorB2, 0);
  }

  else if (state == 'B') { // Se o estado recebido for igual a 'B', movimenta-se para trás.
    analogWrite(motorA1, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
    analogWrite(motorA2, vSpeed);
  }

   else if (state == 'H') {  // Se o estado recebido for igual a 'H', movimenta-se para Trás Esquerda.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, 0); 
    analogWrite(motorB2, 100);
  }
  
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', movimenta-se para Trás Direita.
    analogWrite(motorA1, 0);   
    analogWrite(motorA2, 100);
    analogWrite(motorB1, 0);   
    analogWrite(motorB2, vSpeed);
  }

  else if (state == 'L') {   // Se o estado recebido for igual a 'L', movimenta-se para esquerda.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, vSpeed);
    analogWrite(motorB1, vSpeed);
    analogWrite(motorB2, 0);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', movimenta-se para direita.
    analogWrite(motorA1, vSpeed);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, vSpeed);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', permanece parado.
    analogWrite(motorA1, 0);
    analogWrite(motorA2, 0);
    analogWrite(motorB1, 0);
    analogWrite(motorB2, 0);
  }


  else if (state == 'V') { // Se o estado recebido for igual a 'V', aciona o atuador.
    if (j == 0) {
      digitalWrite(atuador, 1);
      j = 1;
    }
    else if (j == 1) {
      digitalWrite(atuador, 0);
      j = 0;
    }
    state = 'n';
  }


}
