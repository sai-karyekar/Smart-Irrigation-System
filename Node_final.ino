
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


const char* ssid = "Shrutika's Realme";
const char* password = "Shrutikaavhad";

int motorPin = 13; // GPIO13---D7 of NodeMCU
WiFiServer server(80);
WiFiClient client;

String thingSpeakAddress= "http://api.thingspeak.com/update?";
String writeAPIKey;
String tsfield1Name;
String request_string;

HTTPClient http;

void setup()
{
   Serial.begin(115200);
   delay(10);

  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  
   WiFi.disconnect();
   WiFi.begin(ssid, password);
   while ((!(WiFi.status() == WL_CONNECTED)))
    {
    delay(300);
    }

   while (WiFi.status() != WL_CONNECTED) 
   {
    delay(500);
    Serial.print(".");
   }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}

void loop()
{
    if (client.connect("api.thingspeak.com",80))
    {
      request_string = thingSpeakAddress;
      request_string += "key=";
      request_string += "F0VAOGVW1X79UBFF";
      request_string += "&";
      request_string += "field1";
      request_string += "=";
      request_string += analogRead(A0);
      http.begin(request_string);
      http.GET();
      http.end();
      delay(3000);
    }

     // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)
    {
      return;
    }
 
    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available())
    {
      delay(1);
    }
 
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
   
    // Match the request
   
    int value = LOW;
    if (request.indexOf("/PUMP=ON") != -1)  
    {
      digitalWrite(motorPin, HIGH);
      value = HIGH;
    }
    if (request.indexOf("/PUMP=OFF") != -1) 
    {
      digitalWrite(motorPin, LOW);
      value = LOW;
    }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Pump is now: ");
 
  if(value == HIGH) 
  {
    client.print("On");
  } else
  {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/PUMP=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/PUMP=OFF\"\"><button>Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
