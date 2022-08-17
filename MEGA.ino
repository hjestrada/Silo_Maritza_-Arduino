#include <SHT1x.h>
#define dataPin  20
#define clockPin 21
String Cadena = "";


SHT1x sht1x(dataPin, clockPin);

void setup()
{
  Serial.begin(9600);
  Serial3.begin(115200);
}
void loop()
{
  float temp_c;
  float humidity;
  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();

  Cadena = "";
  Cadena += humidity;
  Cadena += ";";
  Cadena += temp_c;

  Serial3.print(Cadena);
  if (Serial3.available()) {
    String msg = "";
    while (Serial3.available()) {
      msg += char(Serial3.read());
      delay(50);
    }
    Serial.println(msg);
  }
  delay(1000);
}
