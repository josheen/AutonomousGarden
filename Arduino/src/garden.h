#include <LiquidCrystal.h>
#include "DHT.h"
#include "Adafruit_seesaw.h"
#define DHTPIN 13    // Humidity sensor output
#define DHTTYPE DHT22
#define LOWMOIST 350 //Low range for soil moisture
#define HIGHMOIST 500


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);
int analogPin = A7; //photoresistor output
int button = 53;
int light;
int k = 0;
int value;
float h;
float t;
float tempC;
float soil_humidity;
Adafruit_seesaw soil_sensor;

void setup();
void show_air();
void show_light();
void check_water();
void soil_info();


class control {
    public:
        void LED_control();
        void water_control();
        int button_press();
};

control auto_garden;


    
