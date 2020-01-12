#include <ESP8266WIFI.H>
#include <WIFICLIENTSECURE.H>
#include <EWIFIUDP.H>
#include <AZUREIOTHUB.H>
#include <AZUREIOTPROTOCOOL_MOTT.H>
#include <AZUREIOTTUTILITY.H>
#include <ARDUINOJSON.H>

static char * iotHubconnectionString = ""; // hub primary key azure
static char *ssid = "Nackademin Guest GB";
static char *password = "SnartSommar!";

static bool messagePending = false;
static bool messageSending = true;
bool devicestatus = false;

void initWiFi(){
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    uint8_t max[6];
    WiFi.macAddress(mac);
    WiFi.begin(ssid,password);
    delay(5000);
  }
  Serial.printf("Connected to WiFi %s.\r\n", ssid);
}

void initiTIme(){
  time_t epochTime;
  configTime(0,0, "pool.ntp.org", "time.nist.gov");

    while(true)
    {
      epochTime = time(NULL);
      if(epochTime == 0)
      {
        delay(2000);  
      } else{
        Serial.println("Getting NTP scceeded.");
        break;
      }
    }
}

static IOTHUB_CLIENT_LL_Handle iotHubClientHandle;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  initWiFi();
  initTime();


  iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, MOTT_Protocool);
  if(iotHubClientHandle == NULL){
    Serial.println("Failed to connect to IoT HUB");
    while(1);
  }
  IotHubCLient_LL_SetMessageCallBack(iotHubClientHandle, reciveMessageCallBack, NULL);
  Serial.println("Device online and waiting instrucions....");
}


void loop() {
  // put your main code here, to run repeatedly:
  
}
