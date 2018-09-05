#include <nRF905.h>

#define RXADDR 0x586F2E10 // Address of this device
#define TXADDR 0xFE4CA6E5 // Address of device to send to

#define PACKET_NONE		0
#define PACKET_OK		1
#define PACKET_INVALID	2

int zwrotna = 9;
boolean odpalac = false;

static volatile uint8_t packetStatus;

void NRF905_CB_RXCOMPLETE(void)
{
	packetStatus = PACKET_OK;
	nRF905_standby();
}

void NRF905_CB_RXINVALID(void)
{
	packetStatus = PACKET_INVALID;
	nRF905_standby();
}

void setup()
{
	Serial.begin(115200);
	Serial.println(F("Server started"));

	// Start up
	nRF905_init();
	
	// Set address of this device
	nRF905_setListenAddress(RXADDR);

	// Put into receive mode
	nRF905_RX();
}

void loop()
{
	while(packetStatus == PACKET_NONE);

		packetStatus = PACKET_NONE;

		// Make buffer for data
		uint8_t buffer[NRF905_MAX_PAYLOAD];
		nRF905_read(buffer, sizeof(buffer));

    if(Serial.available())
      {
        char temp = Serial.read();
        if(temp =='x')
          zwrotna = 0;
        else if (temp == 's')
          zwrotna = 9;
      }
    char data[NRF905_MAX_PAYLOAD] = {0};
    sprintf(data, "%d", zwrotna);

    if (zwrotna == 0)
      Serial.println("===================xdddd==========");
    

		// Send back the data, once the transmission has completed go into receive mode
		//while(!nRF905_TX(TXADDR, buffer, sizeof(buffer), NRF905_NEXTMODE_RX)); // oryginal
    while(!nRF905_TX(TXADDR, data, sizeof(data), NRF905_NEXTMODE_RX)); // moje*/
    delay(40);
		// Print out ping contents
		Serial.print(F("Data from server: "));
		Serial.write(buffer, sizeof(buffer));
		Serial.println();

}
