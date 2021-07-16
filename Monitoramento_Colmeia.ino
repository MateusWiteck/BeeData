/* Este programa se destina ao monitoramento completo das colmeias
    Usando o seguinte comando: tail -c0 -f /dev/ttyACM0 | tee Área\ de\ Trabalho/BeeData.csv
    (no linux) gera-se uma tabela .csv na area de trabalho para ser estudada ou usada em algoritimos de AI */
#include <dht.h>   //biblioteca do sensor de umidade e temperatura

#define    dht_pin    4   //pino de sinal do dht11 ligado no digital 5
#define    ldr_pin    A0  // pino do Fotoresistor
#define    ftrIn_pin A1   // Fototransistor Dentro da Colmeia
#define    ftrOut_pin A2  // Fototransistor Fora da Colmeia
#define    timeDelay 10000 // Tempo para repitir o loop global em ms
#define    timeDelayFototransistor 1000 // Tempo que a abelha tem para entrar ou sair

dht   my_dht;   //objeto para o sensor

//Funcoes
void entrada(unsigned int *quantasFora, unsigned int *TotalDeAbelhas)
{
  if (*quantasFora == 0) {
    *TotalDeAbelhas++;
    return;
  }

  *quantasFora--;
}
void saida(unsigned int *quantasFora, unsigned int *TotalDeAbelhas)
{
  if (*quantasFora == *TotalDeAbelhas) *TotalDeAbelhas++;
  *quantasFora ++;

}

//  Variáveis Globais DHT11
int    temperatura = 0x00,   //armazena a temperatura em inteiro
       umidade     = 0x00,   //armazena a umidade em inteiro
       tOrvalho    = 0x00;   //armazena a temperatura de orvalho
// Variáveis Globais Fotoresistor
int MMovel,
    lumInstantanea,
    lumAnterior;
// Variáveis Globais Fototransistor
unsigned long int tempoAnterior,
         tempoAtual,
         TempoPrimeiroContato,
         TempoApos;
unsigned int quantasFora,
         TotalDeAbelhas;
int isFora = 0x00,
    leituraFora,
    leituraDentro; // 0 se nao passou por nenhum, 1 se passou por fora primeiro, 2 por segundo

// Setup
void setup()
{
  Serial.begin(9600);   //serial em 9600 baud rate
  Serial.println("Fora,Dentro,Total,Temperatura *C,Umidade,Temperatura De Orvalho,num de Luminecencia");
  pinMode(ldr_pin, INPUT);
  pinMode(ftrIn_pin, INPUT);
  pinMode(ftrOut_pin, INPUT);
  tempoAnterior = 0;
  quantasFora = 0;
  TotalDeAbelhas = 0;
  lumInstantanea = analogRead(ldr_pin);
  isFora = 0;


} //end setup


// Loop
void loop()
{

  //  Serial.println(isFora);
  leituraFora = analogRead(ftrOut_pin);
  leituraDentro = analogRead(ftrIn_pin);
  tempoAtual = millis();

  //Serial.print(leituraFora) ; Serial.print(" "); Serial.println(leituraDentro);


  //Serial.print(tempoAtual); Serial.print(" "); Serial.println(TempoPrimeiroContato + timeDelayFototransistor);
  if (isFora != 0 && tempoAtual > TempoPrimeiroContato + timeDelayFototransistor) {
    isFora = 0;

  }

  // Fototransistor de Fora da Colmeia

  if (leituraFora < 870 && isFora != 1 && tempoAtual - TempoApos > timeDelayFototransistor) {
    if (isFora == 2) {
      if (quantasFora == TotalDeAbelhas) TotalDeAbelhas++;
      quantasFora ++;
      isFora = 0;
      TempoApos = millis();
    } else {
      isFora = 1; TempoPrimeiroContato = millis();
    }
  }

  // Fototransistor de Dentro da Colmeia
  else if (leituraDentro < 870 && isFora != 2 && tempoAtual - TempoApos > timeDelayFototransistor) {
    if (isFora == 1) {
      if (quantasFora == 0) {
        TotalDeAbelhas++;
      } else {
        quantasFora--;
      }
      isFora = 0;
      TempoApos = millis();
    } else {
      isFora = 2; TempoPrimeiroContato = millis();
    }

  } else {


    if (tempoAtual >= tempoAnterior + timeDelay) {

      // Modulo DHT
      my_dht.read11(dht_pin);

      temperatura = my_dht.temperature;
      umidade     = my_dht.humidity;
      tOrvalho = (temperatura - (100 - umidade) / 5);

      // Fotoresistor
      lumAnterior = lumInstantanea;
      lumInstantanea = analogRead(ldr_pin);
      MMovel = (lumInstantanea + lumAnterior) / 2;

      // Fototransistor
      Serial.print(quantasFora);
      Serial.print(",");
      Serial.print(TotalDeAbelhas - quantasFora);
      Serial.print(",");
      Serial.print(TotalDeAbelhas);
      Serial.print(",");

      // DHT11
      Serial.print(temperatura);
      Serial.print(",");
      Serial.print(umidade);
      Serial.print(",");
      Serial.print(tOrvalho);

      // Fotoresistor
      Serial.println(MMovel);

      tempoAnterior = tempoAtual;
    }
  }

} //end loop
