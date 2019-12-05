control::LED_control(){
     soil_humidity = soil_sensor.touchRead(0);
  if(soil_humidity < LOWMOIST+50){
    digitalWrite(22,LOW);
    digitalWrite(23,HIGH);
  }
  else{
      digitalwrite(22,HIGH);
      digitalWrite(23,LOW); 
  }
}

control::water_control(){
    while(soil_humidity < LOWMOIST){
        lcd.setCursor(0,0);
        lcd.print("watering...       ");
        lcd.setCursor(0,1);
        lcd.print("             ");  
        soil_humidity = soil_sensor.touchRead(0);
        digitalWrite(52,HIGH);
        Serial.print(digitalRead(52));
}
    digitalWrite(52,LOW);
}

control::button_press(){
    button_reading = digitalRead(button);
    delay(150);
    return button_reading; 
}


void setup(){
    Serial.begin(9600);
    pinMode(button, INPUT);
    lcd.begin(16, 2);
    dht.begin();
    pinMode(52,OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    soil_sensor.begin(0x36);
}

void show_air(){
    auto_garden.water_control(); 
    auto_garden.LED_control();
 h = dht.readHumidity();
  t = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print('C');
}

void show_ligth(){
    auto_garden.water_control(); 
    auto_garden.LED_control();
    lcd.clear();
    light = analogRead(analogPin);
    lcd.setCursor(0,0);
    if(light <= 266){
        lcd.print("Low Light");
        lcd.setCursor(0,1);
        lcd.print(light);
    }
    else if(light <= 650){
        lcd.print("Medium Light");
        lcd.setCursor(0,1);
        lcd.print(light);
    } 
    else{
        lcd.print("High Light");
        lcd.setCursor(0,1);
        lcd.print(light);  
}

void check_water(){
    auto_garden.water_control(); 
    auto_garden.LED_control();
    soil_humidity = soil_sensor.touchRead(0);
    if(soil_humidity < LOWMOIST+50){
        digitalWrite(22,LOW);
        digitalWrite(23,HIGH);
    }
    else{
        digitalWrite(22,HIGH);
        digitalWrite(23,LOW);
    }
    while(soil_humidity < LOWMOIST){
         lcd.setCursor(0,0);
        lcd.print("watering...       ");
        lcd.setCursor(0,1);
        lcd.print("             ");  
        soil_humidity = soil_sensor.touchRead(0);
        digitalWrite(52,HIGH);
        Serial.print(digitalRead(52));
}

void soil_info(){
    auto_garden.water_control(); 
    auto_garden.LED_control();
    lcd.clear();
    lcd.setCursor(0,0);
    tempC = soil_sensor.getTemp();
    soil_humidity = soil_sensor.touchRead(0);
    lcd.print("Temp: ");
    lcd.print(tempC);
    lcd.setCursor(0,1);
    lcd.print("C: ");
    lcd.print(soil_humidity);
    delay(50);
}


void loop() {
  lcd.clear();
  do{
    show_air();
    check_water();
  }while();
  lcd.clear();
  do{
    show_light();
    check_water();
    delay(20);
  }while(!auto_garden.button_press());
  delay(150);
  do{
    soil_info();
    check_water();
  }while(!auto_garden.button_press());
  delay(150);
}
