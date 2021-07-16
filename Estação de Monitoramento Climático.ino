/* Este programa se destina apenas ao monitoramento climatico
    Usando o seguinte comando: tail -c0 -f /dev/ttyACM0 | tee Área\ de\ Trabalho/Clima.csv
    (no linux) gera-se uma tabela .csv na area de trabalho para ser usada em algoritimos de AI */
    
#include <dht.h>   //biblioteca do sensor de umidade e temperatura


#define    dht_pin    4   //pino de sinal do dht11 ligado no digital 5
#define    ldr_pin    A0  // pino do Fotoresistor

//  Variáveis Globais DHT11
dht   my_dht;   //objeto para o sensor
int    temperatura = 0x00;   //armazena a temperatura em celcius
int    umidade     = 0x00,   //armazena a umidade em inteiro
       tOrvalho    = 0x00;   //armazena a temperatura de orvalho em celcius
// Variáveis Globais Fotoresistor
int MMovel,                  //Media aritimetica de duas temperaturas medidas
    lumInstantanea,
    lumAnterior;
void setup() {

  Serial.begin(9600);   //serial em 9600 baud rate

  pinMode(ldr_pin, INPUT);
  lumInstantanea = analogRead(ldr_pin);

  int static k = 1;
  if (k == 1) {
    Serial.println("InicioDoMonotoramento");
    Serial.println("Temperatura,Umidade Relativa do Ar %,Temperatura de Orvalho,Numero de Luminuosidade");
  }
  k++;
}

void loop() {
  // Modulo DHT
  my_dht.read11(dht_pin);

  temperatura = my_dht.temperature;
  umidade     = my_dht.humidity;
  tOrvalho = (temperatura - (100 - umidade) / 5);

  // Fotoresistor
  lumAnterior = lumInstantanea;
  lumInstantanea = analogRead(ldr_pin);
  MMovel = (lumInstantanea + lumAnterior) / 2;

  // DHT11
  Serial.print(temperatura);
  Serial.print(",");
  Serial.print(umidade);
  Serial.print(",");
  Serial.print(tOrvalho);
  Serial.print(",");

  // Fotoresistor
  Serial.print(MMovel);

  Serial.println();


  delay(60*2500);
  lumAnterior = lumInstantanea;
  lumInstantanea = analogRead(ldr_pin);
  delay(60*2500);


}
