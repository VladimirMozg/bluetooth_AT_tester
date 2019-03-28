/* Для корректного сканирования ещё не проверенных блютусов рекомендуется использовать платы Arduino с аппаратными UART
 *  например, Arduino Mega. Данная программа расчитана на подключения блютуса к UART3 на Arduino Mega
 * Для работы программы нужно подключить блютус следующим образом:
 * VCC - к 5 В на Arduino
 * GND - к GND на Arduino
 * Tx - к RX на Arduino
 * RX - к TX на Arduino
*/

char buf[20];
int len = 0;

uint32_t baudRates[] = {300, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 74880, 115200, 230400, 250000};

void setup() 
{
  Serial.begin(9600);
  //delay(10);
  Serial.println("  ARDUINO >> START 1");
  
  for (uint8_t i = 0; i < 11; i++)
  {
    Serial.print("  ARDUINO >> BAUD[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(baudRates[i]);

    
    Serial3.begin(baudRates[i]);
    delay(10);
    Serial3.print("AT\r\n");

    uint64_t Time = millis();
    while (Time+1 > millis()){}
    
    Serial3.print("AT\r\n");

    Time = millis();
    while (Time+1 > millis()){}
    
    if (Serial3.available()) 
    {
        delay(10);
        Serial.print("BLUETOOTH << ");
        while (Serial3.available()) Serial.write(Serial3.read());
        
        Serial.print("  ARDUINO >> REAL_BAUD = ");
        Serial.println(baudRates[i]);
        break;
     }
  }
  
  Serial.println("  ARDUINO >> START 10");  
  for (uint8_t i = 0; i < 11; i++)
  {
    Serial.print("  ARDUINO >> BAUD[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(baudRates[i]);

    
    Serial3.begin(baudRates[i]);
    delay(100);
    Serial3.print("AT\r\n");

    uint64_t Time = millis();
    while (Time+10 > millis()){}

    Serial3.print("AT\r\n");

    Time = millis();
    while (Time+10 > millis()){}
    
    if (Serial3.available()) 
    {
        delay(200);
        Serial.print("BLUETOOTH << ");
        while (Serial3.available()) Serial.write(Serial3.read());
        
        Serial.print("  ARDUINO >> REAL_BAUD = ");
        Serial.println(baudRates[i]);
        break;
     }
  }
  

  Serial.println("  ARDUINO >> START 100");  
  for (uint8_t i = 0; i < 11; i++)
  {
    Serial.print("  ARDUINO >> BAUD[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(baudRates[i]);

    
    Serial3.begin(baudRates[i]);
    delay(100);
    Serial3.print("AT\r\n");

    uint64_t Time = millis();
    while (Time+100 > millis()){}

    Serial3.print("AT\r\n");

    Time = millis();
    while (Time+10 > millis()){}
    
    if (Serial3.available()) 
    {
        delay(200);
        Serial.print("BLUETOOTH << ");
        while (Serial3.available()) Serial.write(Serial3.read());
        
        Serial.print("  ARDUINO >> REAL_BAUD = ");
        Serial.println(baudRates[i]);
        break;
     }
  }
  //Serial3.begin(57600);
  Serial.println("TEST FINISHED...");
  Serial.println("");
  Serial.println("");
  
  Serial3.print("AT+NAME\r\n");
  Serial.print("BLUETOOTH_NAME: ");
  delay(100);
  while (Serial3.available()) Serial.write(Serial3.read());
  
  Serial3.print("AT+PIN\r\n");
  Serial.print("BLUETOOTH_PIN: ");
  delay(100);
  while (Serial3.available()) Serial.write(Serial3.read());

  Serial3.print("AT+BAUD\r\n");
  Serial.print("BLUETOOTH_BAUD: ");
  delay(100);
  while (Serial3.available()) Serial.write(Serial3.read());

  Serial3.print("AT+VERSION\r\n");
  Serial.print("BLUETOOTH_VER: ");
  while (Serial3.available()) Serial.write(Serial3.read());
}

void loop() 
{
    if (Serial3.available()) 
    {
      delay(10);
      Serial.print("BLUETOOTH << ");
      while (Serial3.available()) Serial.write(Serial3.read());
      //Serial.println();
    }

    if (Serial.available()) 
    {
        delay(100);

        String cmd="";

        while (Serial.available())
        {
          cmd = cmd + char(Serial.read());
          delay(10);
        }
        Serial.print("  ARDUINO >> ");
        Serial.println(cmd);
        
        cmd = cmd + "\r\n";
        
        Serial3.print(cmd);
        delay(100);
    }
    
}
