#include <LiquidCrystal.h> //inclui a biblioteca de reconhecimento do LCD

LiquidCrystal LCD(7,6,5,4,3,2); //portas do arduino com conexão do lcd

int Lampada=13; //define pino que aciona a lâmpada de aquecimento
int Cooler=8; //define pino que aciona o cooler para resfriamento
int TempBaixa=20; //define valor para temperatura baixa
int TempAlta=25; //define valor para temperatura alta
int Umidade=A2; //define pino que monitora a umidade do solo
int Temp=A5; //define pino que monitora a temperatura 

void setup() //função principal
{
 pinMode(Umidade, INPUT);//sensor de umidade do solo 
 pinMode(12, OUTPUT);//define a bomba de água como saída 
 pinMode(11, OUTPUT);//define o LED vermelho como saída
 pinMode(10, OUTPUT);//define o LED amarelo como saída
 pinMode(9, OUTPUT);//define o LED verde como saída 

 pinMode(Temp, INPUT); //define o LM35 como entrada
 pinMode(Lampada, OUTPUT); //define a lâmpada IR como saída
 pinMode(Cooler, OUTPUT); //define o cooler como saída
 LCD.begin (16,2); //define o número de linhas e colunas do LCD
 LCD.setCursor(0,0); //define posição inicial para o cursor do LCD
 LCD.print("           C    "); //escreve no LCD
}

void loop() //função looping
{
 //faz a leitura da temperatura lida pelo LM35 e converte em um sinal elétrico
 int SensorTempTensao=analogRead(Temp); 

 // Converte a tensao lida
 float Tensao=SensorTempTensao*5;
 Tensao/=1024;

 // Converte a tensao lida em Graus Celsius
 float TemperaturaC=(Tensao)*100;

 // Muda o cursor para a quinta coluna e primeira linha do LCD
 LCD.setCursor(5,0);

 // Imprime a temperatura em Graus Celsius
 LCD.print(TemperaturaC);
  
 if (analogRead(Umidade) > 500) //se a umidade estiver abaixo de 500KPa (kilo pascal)
 {
  digitalWrite(12, HIGH); //aciona a bomba de água
  digitalWrite(11, HIGH); //acende o LED vermelho
  digitalWrite(10, LOW); //apaga o LED amarelo
  digitalWrite(9, LOW); //apaga o LED verde
  LCD.setCursor(0,1);
  LCD.print("      SECO      "); 
 }
 if (analogRead(Umidade) > 250 && analogRead(Umidade) < 500) 
 {
  digitalWrite(12, LOW); //apaga a bomba de água
  digitalWrite(11, LOW); //apaga o LED vermelho
  digitalWrite(10, HIGH); //acende o LED amarelo
  digitalWrite(9, LOW);//apaga o LED verde
  LCD.setCursor(0,1); //movimenta o cursor do LCD
  LCD.print(" NIVEL RAZOAVEL ");//escreve no LCD  
 }
 if (analogRead(Umidade) < 250) //se a umidade estiver abaixo de 250KPa
 {
  digitalWrite(12, LOW);//apaga a bomba de água
  digitalWrite(11, LOW);//apaga o LED vermelho
  digitalWrite(10, LOW);//apaga o LED amarelo
  digitalWrite(9, HIGH);//acende o LED verde
  LCD.setCursor(0,1);//movimenta o cursor do LCD
  LCD.print("    IRRIGADO    "); //escreve no LCD
 }
    
 if (TemperaturaC>=TempAlta) //Se a temperatura estiver maior que 25°C
 {
  digitalWrite(Lampada, LOW); //desliga a lâmpada IR
  digitalWrite(Cooler, HIGH); //aciona o cooler
 }
 else if (TemperaturaC<=TempBaixa)
 {
  digitalWrite(Lampada, HIGH); //aciona a lâmpada IR
  digitalWrite(Cooler, LOW); //desliga o cooler
 }
 else //senão
 {
 digitalWrite(Lampada, LOW); //desliga a lâmpada IR
 digitalWrite(Cooler, LOW); //desliga o cooler
 }
 
 delay(10); //define uma espera de 10 mili segundos
}
