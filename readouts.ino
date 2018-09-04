#include <nRF905.h>
#include "HX711.h"
#include "max6675.h"

//thermocouples config
// pins
int ktcSO = 11;
int ktcCS = 12;
int ktcCLK = 13;
//???
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

//tensometer config
//pins
#define DOUT  46
#define CLK  44
//???
HX711 scale(DOUT, CLK);

//communication addresses
#define RXADDR 0xFE4CA6E5 // Address of this device
#define TXADDR 0x586F2E10 // Address of device to send to

//calibration value
const float calibration_factor = -96650;

float currentThrust;
float currentTemp;

//communication config
#define TIMEOUT 1000

#define PACKET_NONE 0
#define PACKET_OK 1
#define PACKET_INVALID 2

#define NRF905_MAX_PAYLOAD 32

static volatile uint8_t packetStatus;

boolean started = False;

void NRF905_CB_RXCOMPLETE(void)
{
  packetStatus = PACKET_OK;
}

void NRF905_CB_RXINVALID(void)
{
  packetStatus = PACKET_INVALID;
}

void setup() {
  //tare the scale
  scale.set_scale(-96650);  //Calibration adjustment
  scale.tare();             //Reset the scale to 0  
  
  //Set up the serial port
  Serial.begin(115200);
  Serial.println(F("Transmiter is up"));

  //Initiate communication
  nRF905_init();

  //Set receaver address
  // Set address of this device
  nRF905_setListenAddress(RXADDR);
  //Change to RX mode
  nRF905_RX();
  delay(500);
}

void loop() {
  
  while(!started){
    // Wait for data
    while(packetStatus == PACKET_NONE);
    if(packetStatus == PACKET_OK)
    {
      //Reset package status
      packetStatus = PACKET_NONE;

      // Make buffer for data
      uint8_t buffer[NRF905_MAX_PAYLOAD];
      nRF905_read(buffer, sizeof(buffer));
    
      if(buffer == 'x')
      {
        //Change the started value
       started = True;
      }
     }
  }
  // Read temp data
  currentTemp = ktc.readCelsius(); 
  // Read thurst data
  currentThrust = scale.get_units();
  
  // Make data
  char data[NRF905_MAX_PAYLOAD] = {0};
  sprintf(data, "%d, %d", (int)currentThrust, (int)currentTemp);

  //Reset packet status
  packetStatus = PACKET_NONE;

  //Send the data (send fails if other transmissions are going on, keep trying until success) and enter RX mode on completion
  while(!nRF905_TX(TXADDR, data, sizeof(data), NRF905_NEXTMODE_RX));

  uint8_t success;
  // Wait for reply
  uint32_t sendStartTime = millis();
  while(1)
  {
    success = packetStatus;
    if(success != PACKET_NONE)
      break;
    else if(millis() - sendStartTime > TIMEOUT)
      break;
  }
  delay(300);
}
