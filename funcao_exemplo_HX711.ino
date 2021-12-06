// Mapeamento de Hardware
#define  ADDO  3    //Data Out
#define  ADSK  2    //SCK


// Protótipo das Funções Auxiliares
unsigned long ReadCount(); //conversão AD do HX711


// Variáveis Globais
unsigned long convert;
int cont = 0;


// Configurações Iniciais
void setup()
{
   pinMode(ADDO, INPUT_PULLUP);   //entrada para receber os dados
   pinMode(ADSK, OUTPUT);         //saída para SCK
   
   Serial.begin(9600);

} //end setup


// Loop Infinito
void loop()
{
  if(cont < 20){
    convert = ReadCount();
    Serial.println(convert);
    cont++;
  }
  delay(1000);
} //end loop


// Funções
unsigned long ReadCount()
{
  unsigned long Count = 0;
  unsigned char i;
 
  digitalWrite(ADSK, LOW);
 
  while(digitalRead(ADDO));
 
  for(i=0;i<24;i++)
  {
     digitalWrite(ADSK, HIGH);
     Count = Count << 1;
     digitalWrite(ADSK, LOW);
     if(digitalRead(ADDO)) Count++;
 
  } //end for
 
  digitalWrite(ADSK, HIGH);
  Count = Count^0x800000;
  digitalWrite(ADSK, LOW);
 
  return(Count);
} //end ReadCount
