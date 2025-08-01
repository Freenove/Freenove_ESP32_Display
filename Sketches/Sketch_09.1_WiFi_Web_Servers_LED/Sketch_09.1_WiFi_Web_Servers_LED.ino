/*
* @ File:   Sketch_09.1_WiFi_Web_Servers_LED.ino
* @ Author: [Zhentao Lin]
* @ Date:   [2025-06-14]
*/

#include <WiFi.h>

// WiFi credentials
const char* ssid     = "**************";
const char* password = "**************";

// Web server on port 80
WiFiServer server(80);

// HTTP request buffer
String request;

// LED pin definitions
const int redLedPin = 22;
const int greenLedPin = 16;
const int blueLedPin = 17;

// LED state tracking
String greenLedState = "OFF";
String blueLedState = "OFF";
String redLedState = "OFF";

// Timeout settings
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;  // 2 seconds

void setup() {
  Serial.begin(115200);

  // Initialize LED pins
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  digitalWrite(redLedPin, HIGH);
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(blueLedPin, HIGH);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        request += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP response headers
            // Handle incoming commands first. These are AJAX requests.
            if (request.indexOf("GET /22/ON") >= 0) {
              Serial.println("Red LED ON");
              redLedState = "ON";
              digitalWrite(redLedPin, LOW);
            } else if (request.indexOf("GET /22/OFF") >= 0) {
              Serial.println("Red LED OFF");
              redLedState = "OFF";
              digitalWrite(redLedPin, HIGH);
            } else if (request.indexOf("GET /16/ON") >= 0) {
              Serial.println("Green LED ON");
              greenLedState = "ON";
              digitalWrite(greenLedPin, LOW);
            } else if (request.indexOf("GET /16/OFF") >= 0) {
              Serial.println("Green LED OFF");
              greenLedState = "OFF";
              digitalWrite(greenLedPin, HIGH);
            } else if (request.indexOf("GET /17/ON") >= 0) {
              Serial.println("Blue LED ON");
              blueLedState = "ON";
              digitalWrite(blueLedPin, LOW);
            } else if (request.indexOf("GET /17/OFF") >= 0) {
              Serial.println("Blue LED OFF");
              blueLedState = "OFF";
              digitalWrite(blueLedPin, HIGH);
            } else {
              // Send the Complete HTML page
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();

              // Generate HTML response
              client.println("<!DOCTYPE html><html>");
              client.println("<head><meta charset=\"UTF-8\">");
              client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
              client.println("<title>ESP32 Web Server LED</title>");
              client.println("<style>");
              client.println("html{font-family:'Segoe UI',Roboto,sans-serif;background:#f5f5f5;height:100vh;display:flex;justify-content:center;align-items:center;}");
              client.println("body{margin:0;padding:20px;background:white;border-radius:15px;box-shadow:0 10px 30px rgba(0,0,0,0.1);max-width:800px;width:90vw;}");
              client.println(".container{display:grid;grid-template-columns:repeat(3, 1fr);gap:20px;margin-top:20px;}");
              client.println(".card{border-radius:15px;padding:25px;text-align:center;min-width:180px;transition:all 0.3s;cursor:pointer;border:2px solid;position:relative;overflow:hidden;}");
              client.println(".card:hover{transform:translateY(-5px);box-shadow:0 15px 35px rgba(0,0,0,0.15);}");
              client.println(".card:active{transform:translateY(0) scale(0.98);}");
              client.println("#red-card{background:linear-gradient(145deg,#ffcdd2,#ef9a9a);border-color:#f44336;}");
              client.println("#green-card{background:linear-gradient(145deg,#c8e6c9,#a5d6a7);border-color:#4caf50;}");
              client.println("#blue-card{background:linear-gradient(145deg,#bbdefb,#90caf9);border-color:#2196f3;}");
              client.println(".card.off-state{filter:grayscale(70%) brightness(0.85);}");
              client.println("h1{color:#333;text-align:center;font-size:2.4rem;margin-bottom:10px;border-bottom:2px solid #eee;padding-bottom:15px;}");
              client.println(".status{font-size:1.4rem;font-weight:600;margin:25px 0;color:#333;position:relative;z-index:2;}");
              client.println(".device-info{text-align:center;margin-top:25px;color:#777;font-size:0.9rem;padding-top:15px;border-top:1px solid #eee;}");
              client.println("@media (max-width:768px){.container{grid-template-columns:1fr;} body{padding:15px;} h1{font-size:2rem;}}");
              client.println("</style></head>");
              client.println("<body>");
              client.println("<h1>ESP32 Web Server LED</h1>");
              client.println("<div class=\"container\">");

              // Red LED control
              client.println("<div class=\"card " + String(redLedState == "OFF" ? "off-state" : "") + "\" id=\"red-card\" onclick=\"toggleLED('22', this)\">");
              client.println("<h2>Red LED</h2>");
              client.println("<p class=\"status\" id=\"status-22\">" + redLedState + "</p>");
              client.println("</div>");
              
              // Green LED control
              client.println("<div class=\"card " + String(greenLedState == "OFF" ? "off-state" : "") + "\" id=\"green-card\" onclick=\"toggleLED('16', this)\">");
              client.println("<h2>Green LED</h2>");
              client.println("<p class=\"status\" id=\"status-16\">" + greenLedState + "</p>");
              client.println("</div>");
              
              // Blue LED control
              client.println("<div class=\"card " + String(blueLedState == "OFF" ? "off-state" : "") + "\" id=\"blue-card\" onclick=\"toggleLED('17', this)\">");
              client.println("<h2>Blue LED</h2>");
              client.println("<p class=\"status\" id=\"status-17\">" + blueLedState + "</p>");
              client.println("</div>");

              client.println("</div>");
              client.println("<div class=\"device-info\">Device IP: " + WiFi.localIP().toString() + " | ESP32 Web Server LED</div>");
              client.println("<script>");
              client.println("function toggleLED(pin, element) {");
              client.println("  const statusElement = document.getElementById('status-' + pin);");
              client.println("  const currentState = statusElement.innerText;");
              client.println("  const newState = currentState === 'ON' ? 'OFF' : 'ON';");
              client.println("  fetch('/' + pin + '/' + newState);");
              client.println("  statusElement.innerText = newState;");
              client.println("  if (newState === 'ON') { element.classList.remove('off-state'); } else { element.classList.add('off-state'); }");
              client.println("}");
              client.println("</script>");
              client.println("</body></html>");
            }
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    request = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}