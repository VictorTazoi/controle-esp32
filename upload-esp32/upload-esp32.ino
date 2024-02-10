/* ============================================================================
 
   Controle de Relés por WiFi com ESP32
   Autor: Eng. Wagner Rambo
   Março de 2021

============================================================================ */

#include <WiFi.h>

#define dispositivo01 4 //Define o nome para o pino

const char *ssid = "Nome WiFi"; //Nome do WiFi
const char *password = "Senha WiFi"; //Senha do WiFi

WiFiServer server(80); //Porta do servidor
void relay_wifi();

// ============================================================================
void setup()
{
  Serial.begin(115200);
  pinMode(dispositivo01, OUTPUT); //Define pino como saída
  Serial.println();
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(741);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


// ============================================================================
void loop() 
{
  while(WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, password);
    Serial.print(".");
    delay(741);
  }
  relay_wifi();
}


// ============================================================================
void relay_wifi()
{
  WiFiClient client = server.available();
  if(client)
  {
    Serial.println("Novo Cliente Definido");
    String currentLine = "";
    while(client.connected())
    {
      if(client.available())
      {
        char c=client.read();
        Serial.write(c);
        if(c=='\n')
        {
          if(currentLine.length()==0)
          {
            break;
          }else currentLine="";
        }else if(c != '\r') currentLine += c;

        // DISPOSITIVOS
        if(currentLine.endsWith("GET /1ON")){
          digitalWrite(dispositivo01, HIGH);
          client.print("HTTP/1.1 302 Found\r\n");
          client.print("Location: http://192.168.0.10/controle/");
        }
        else if(currentLine.endsWith("GET /1OFF")){
          digitalWrite(dispositivo01,  LOW);
          client.print("HTTP/1.1 302 Found\r\n");
          client.print("Location: http://192.168.0.10/controle/");
        }
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
