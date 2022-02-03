#include <mcp_can.h>
#include <SPI.h>

#ifdef Arduino_SAMD_VARIANT_COMPILANCE
  #define SERIAL SerialUSB
#else 
  #define SERIAL Serial
#endif

#define UP A1
#define DOWN A3
#define LEFT A2
#define Right A5
#define CLLICK A4

#define LED2 8
#define LED3 7

#define StepValue 130

const int SPI_CS_PIN = 10;

MCP_CAN CAN(SPI_CS_PIN);

void setup() {
  Serial.begin(115200);
  delay(1000);

  while (CAN_OK != CAN.begin(CAN_1000KBPS))
  {
    Serial.println("CAN BUS Shield init fail!");
    Serial.println("Init CAN BUS Shield again");
    delay(1000);
  }
  Serial.println("CAN BUS Shield init OK!")

  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LED2, INPUT);
  pinMode(LED3, INPUT);

  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);

  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  
}

long GenPos = 0;

void loop() 
{
  unsigned char len = 0;
  unsigned char buf[8];


  if(digitalRead(UP)==LOW)
  {
    GenPos = GenPos + StepValue;
    if(GenPos > 35999)
    {
      GenPos = max(GenPos - 35999, 0);
    }
    if(GenPos < 0)
    {
      GenPos = 0;
    }

    Serial.println(GenPos);

    buf[0] = 0xA6;
    buf[1] = 0x00;
    buf[2] = 0x02;
    buf[3] = 0x02;
    buf[4] = GenPos;
    buf[5] = GenPos >> 8;
    buf[6] = 0x00;
    buf[7] = 0x00;

    CAN.sendMsgBuf(0x141, 0, 8, buf);
  }

  if(CAN_MSGAVAIL == CAN.checkReceive())
  {
    CAN.readMsgBuf(&len, buf);

    unsigned long canID = CAN.getCanID();

    for(int i=0; i<len; i++)
    {
      Serial.print(buf[i], HEX);
      Serial.print("\t");
    }
    Serial.println();
    
  }

  //delay(1000);
}
