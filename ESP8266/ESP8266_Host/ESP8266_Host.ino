// http://<IP>/get?ssid=value
// http://<IP>/get?psk=value
// http://<IP>/get?gway=value
// http://<IP>/get?sip=value

#define LED1 16
#define LED2 5
#define LED3 4
#define LED4 0
#define LED5 2

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ESP8266HTTPClient.h>

const char* APSSID   = "ESP8266 ACCESS POINT";
const char* APPSK   = "123456789";
const char* SSIDInput = "ssid";
const char* PSKInput = "psk";
const char* GatewayInput = "gateway";
const char* StaticIPInput = "sip";
char NetworkSSID[32], Password[32], Gateway[16], StaticIP[16];
String SSIDHolder = "", PSKHolder = "", GatewayHolder = "", StaticIPHolder = "", NetworkHolder[45] = "";
int nn = 0, IPVector[4] = {0, 0, 0, 0}, GatewayVector[4] = {0, 0, 0, 0};
bool LED1State = false, LED2State = false, LED3State = false, LED4State = false, LED5State = false, LED6State = false, LED7State = false, LED8State = false, LED9State = false, LED10State = false;

WiFiClient client;
AsyncWebServer server(80);

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);  

    
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");

  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  scanNetwork(); 

  loadCredentials();

  Serial.println();

  for (int i = 0; i < nn; i++) {
    if (NetworkHolder[i] == NetworkSSID) {
      WiFi.mode(WIFI_STA);
      WiFi.begin(NetworkSSID, Password);
      i = 0;
      while ((WiFi.status() != WL_CONNECTED) && (i <= 20)) {
        delay(500);
        Serial.print("*");
        i++;
      }
      i = nn + 1;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Connected();
  }
  else {
    AccessPoint();
  }
}

void serverRequested(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
  });
}

void AsyncServerConnected() { 
  serverRequested();
     
  server.on("/1", HTTP_GET, [](AsyncWebServerRequest * request) {
  LED1State =! LED1State;
  digitalWrite(LED1,LED1State);
  request->send(200, "text/plain", "changed state");
  if(LED1State){
    Serial.println();
    Serial.println("Led 1 ligado");
    Serial.println();
  }
  else{
    Serial.println();
    Serial.println("Led 1 desligado");
    Serial.println();
  }
  });

  server.on("/2", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED2State =! LED2State;
  digitalWrite(LED2,LED2State);
  request->send(200, "text/plain", "changed state");
  if(LED2State){
    Serial.println();
    Serial.println("Led 2 ligado");
    Serial.println();
  }
  else{
    Serial.println();
    Serial.println("Led 2 desligado");
    Serial.println();
  }
  });

  server.on("/3", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED3State =! LED3State;
    digitalWrite(LED3,LED3State);
    request->send(200, "text/plain", "changed state");
    if(LED2State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });

  server.on("/4", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED4State =! LED4State;
    digitalWrite(LED4,LED4State);
    request->send(200, "text/plain", "changed state");
    if(LED4State){
      Serial.println();
      Serial.println("Led 4 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 4 desligado");
    Serial.println();
  }
  });

  server.on("/5", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED5State =! LED5State;
    digitalWrite(LED5,LED5State);
    request->send(200, "text/plain", "changed state");
    if(LED5State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });

  server.on("/6", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED6State =! LED6State;
    digitalWrite(LED5,LED6State);
    request->send(200, "text/plain", "changed state");
    if(LED5State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });

  server.on("/7", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED7State =! LED7State;
    digitalWrite(LED5,LED7State);
    request->send(200, "text/plain", "changed state");
    if(LED5State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });

  server.on("/8", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED8State =! LED8State;
    digitalWrite(LED5,LED8State);
    request->send(200, "text/plain", "changed state");
    if(LED5State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });

  server.on("/9", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED9State =! LED9State;
    digitalWrite(LED5,LED9State);
    request->send(200, "text/plain", "changed state");
    if(LED5State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });

  server.on("/10", HTTP_GET, [](AsyncWebServerRequest * request) {
    LED10State =! LED10State;
    digitalWrite(LED5,LED10State);
    request->send(200, "text/plain", "changed state");
    if(LED5State){
      Serial.println();
      Serial.println("Led 3 ligado");
      Serial.println();
    }
  else{
    Serial.println();
    Serial.println("Led 3 desligado");
    Serial.println();
  }
  });
}

void AsyncServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {    
    Serial.println("requested index.html");
    
    AsyncResponseStream *response = request->beginResponseStream("text/html");
    
    response->addHeader("Server","ESP Async Web Server");
    response->print(F("<!DOCTYPE HTML><html><head> <title>ESP 8266's Network Settings Hub</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style type=\"text/css\"> .button { background-color: #4CAF50; border: none; color: white; padding: 16px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; -webkit-transition-duration: 0.4s; transition-duration: 0.4s; cursor: pointer;}.buttonB { background-color: white; color: black; border: 2px solid #008CBA;}.buttonB:hover { background-color: #008CBA; color: white;}.custom-select { position: relative; font-family: Arial;}.custom-select select { display: none;}.select-selected { background-color: DodgerBlue;}.select-selected:after { position: absolute; content: \"\"; top: 14px; right: 10px; width: 0; height: 0; border: 6px solid transparent; border-color: #fff transparent transparent transparent;}.select-selected.select-arrow-active:after { border-color: transparent transparent #fff transparent; top: 7px;}.select-items div,.select-selected { color: #ffffff; padding: 8px 16px; border: 1px solid transparent; border-color: transparent transparent rgba(0, 0, 0, 0.1) transparent; cursor: pointer; user-select: none;}.select-items { position: absolute; background-color: DodgerBlue; top: 100%; left: 0; right: 0; z-index: 99;}.select-hide { display: none;}.select-items div:hover, .same-as-selected { background-color: rgba(0, 0, 0, 0.1);}.inputs{height: 30px;width: 100%;}.divs{margin: auto;width: 80%;padding: 5px;} </style></head><body> <h2 style=\"text-align: center;\">NodeMCU ESP8266's Network Settings</h2><div class=\"custom-select divs\"> <span>SSID: </span> <select style=\"\" id=\"ssidselect\"> <option value=\"0\">Select a network:</option>"));

    for (int NA = 0; NA < nn; NA++) {
      String NWork;
      NWork = "<option value=\"";
      NWork += NA+1;
      NWork += "\">";
      NWork += NetworkHolder[NA];
      NWork += "</option>";
      response->print(NWork);
    }
    
    response->print(F("</select> </div> <div class=\"divs\"> <span>PSK:</span> <input class=\"inputs\" type=\"password\" id=\"pass\" name=\"password\" minlength=\"8\" required> </div> <div class=\"divs\"> <span>Gateway:</span> <br> <input class=\"inputs\" type=\"text\" id=\"gway\" name=\"gateway\" minlength=\"6\" required> </div> <div class=\"divs\"> <span>Desired IPv4:</span> <br> <input class=\"inputs\" type=\"text\" id=\"sip\" name=\"staticIP\" minlength=\"6\" required> </div> <div style=\"text-align: center; margin: 5px;\"> <button onclick=\"callURL()\" class=\"button buttonB\">Save and commit changes</button> </div></body>"));
    response->print(F("<script> function callURL() { ssidTranslate(); var stip = document.getElementById(\"sip\").value; var gatway = document.getElementById(\"gway\").value; var psk = document.getElementById(\"pass\").value; if (psk.length >= 8) { if ((ssidv == null) || (stip == null) || (stip == 0) || (gatway == null) || (gatway == 0) || (psk == null) || (psk == 0)) { alert(\"Empty fields detected\"); } else { doRequest(\"http://192.168.4.1/get?ssid=\" + ssidv); delay(200); doRequest(\"http://192.168.4.1/get?psk=\" + psk); delay(200); doRequest(\"http://192.168.4.1/get?gateway=\" + gatway); delay(200); doRequest(\"http://192.168.4.1/get?sip=\" + stip); delay(200); doRequest(\"http://192.168.4.1/save\"); delay(200); doRequest(\"http://192.168.4.1/restart\"); var conf = confirm(\"Credentials saved and ESP8266 has been restarted!\"); if (conf) { window.close(); } else { window.close(); } } } else { alert(\"Password length is less than 8 characters long!\"); } } var x, i, j, selElmnt, a, b, c;x = document.getElementsByClassName(\"custom-select\");for (i = 0; i < x.length; i++) { selElmnt = x[i].getElementsByTagName(\"select\")[0]; a = document.createElement(\"DIV\"); a.setAttribute(\"class\", \"select-selected\"); a.innerHTML = selElmnt.options[selElmnt.selectedIndex].innerHTML; x[i].appendChild(a); b = document.createElement(\"DIV\"); b.setAttribute(\"class\", \"select-items select-hide\"); for (j = 1; j < selElmnt.length; j++) { c = document.createElement(\"DIV\"); c.innerHTML = selElmnt.options[j].innerHTML; c.addEventListener(\"click\", function(e) { var y, i, k, s, h; s = this.parentNode.parentNode.getElementsByTagName(\"select\")[0]; h = this.parentNode.previousSibling; for (i = 0; i < s.length; i++) { if (s.options[i].innerHTML == this.innerHTML) { s.selectedIndex = i; h.innerHTML = this.innerHTML; y = this.parentNode.getElementsByClassName(\"same-as-selected\"); for (k = 0; k < y.length; k++) { y[k].removeAttribute(\"class\"); } this.setAttribute(\"class\", \"same-as-selected\"); break; } } h.click(); }); b.appendChild(c); } x[i].appendChild(b); a.addEventListener(\"click\", function(e) { e.stopPropagation(); closeAllSelect(this); this.nextSibling.classList.toggle(\"select-hide\"); this.classList.toggle(\"select-arrow-active\"); });}function closeAllSelect(elmnt) { var x, y, i, arrNo = []; x = document.getElementsByClassName(\"select-items\"); y = document.getElementsByClassName(\"select-selected\"); for (i = 0; i < y.length; i++) { if (elmnt == y[i]) { arrNo.push(i) } else { y[i].classList.remove(\"select-arrow-active\"); } } for (i = 0; i < x.length; i++) { if (arrNo.indexOf(i)) { x[i].classList.add(\"select-hide\"); } }} function ssidTranslate() { var x = document.getElementById(\"ssidselect\"); if ((x.selectedIndex == -1) || (x.options[x.selectedIndex].text == \"Select a network:\")) { alert(\"Null SSID selected\"); ssidv = null; } ssidv = x.options[x.selectedIndex].text; } function doRequest(url) { const Http = new XMLHttpRequest(); Http.open(\"GET\", url); Http.send(); } function delay(ms) { var cur_d = new Date(); var cur_ticks = cur_d.getTime(); var ms_passed = 0; while (ms_passed < ms) { var d = new Date(); var ticks = d.getTime(); ms_passed = ticks - cur_ticks; } } document.addEventListener(\"click\", closeAllSelect);</script></html>"));
    request->send(response);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    String inputParam;

    if (request->hasParam(SSIDInput)) {
      inputMessage = request->getParam(SSIDInput)->value();
      inputParam = SSIDInput;
      SSIDHolder = inputMessage;
    }

    else if (request->hasParam(PSKInput)) {
      inputMessage = request->getParam(PSKInput)->value();
      inputParam = PSKInput;
      PSKHolder = inputMessage;
    }

    else if (request->hasParam(GatewayInput)) {
      inputMessage = request->getParam(GatewayInput)->value();
      inputParam = GatewayInput;
      GatewayHolder = inputMessage;
    }

    else if (request->hasParam(StaticIPInput)) {
      inputMessage = request->getParam(StaticIPInput)->value();
      inputParam = StaticIPInput;
      StaticIPHolder = inputMessage;
    }

    else {
      inputMessage = "";
      inputParam = "";
    }
    Serial.println("");
    Serial.println(inputMessage);
    Serial.print("SSIDHolder: "); Serial.println(SSIDHolder);
    Serial.print("PSKHolder: "); Serial.println(PSKHolder);
    Serial.print("GatewayHolder: "); Serial.println(GatewayHolder);
    Serial.print("StaticIPHolder: "); Serial.println(StaticIPHolder);
    Serial.println("");
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field ("
                  + inputParam + ") with value: " + inputMessage +
                  "<br><a href=\"/\">Return to Home Page</a>");
  });
  
  server.on("/save", HTTP_GET, [](AsyncWebServerRequest * request) {
    saveCredentials();
    loadCredentials();
    request->send(200, "text/plain", "Saved Credentials!");
  });

  server.on("/restart", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Restarting ESP8266...");
    server.end();
    delay(333);
    ESP.restart();
  });
}

void AccessPoint() {
  Serial.println();
  Serial.print("Não foi possivel conectar a "); Serial.println(NetworkSSID);
  WiFi.mode(WIFI_OFF);
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(APSSID, APPSK);
  Serial.println("Ponto de acesso criado!");

  server.begin();

  AsyncServer();
}

void Connected() {  
  IPconversion(StaticIP, Gateway);
  IPAddress ip( IPVector[0], IPVector[1], IPVector[2], IPVector[3] );
  IPAddress gateway( GatewayVector[0], GatewayVector[1], GatewayVector[2], GatewayVector[3] );
  IPAddress subnet(255, 255, 255, 0);

  WiFi.config(ip, gateway, subnet);
  Serial.println("");
  Serial.print("WiFi connection Successful to: "); Serial.println(NetworkSSID);
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());
  server.begin();
  AsyncServerConnected();
}

void IPconversion(String IPHolder, String GatewayHolder) {
  int GatewayIndex = 0, IPIndex = 0;

  for (int i = 0; i < IPHolder.length(); i++ )
  {
    char c = IPHolder[i];
    if ( c == '.' )
    {
      IPIndex++;
      continue;
    }
    IPVector[IPIndex] *= 10;
    IPVector[IPIndex] += c - '0';
  }

  for (int i = 0; i < GatewayHolder.length(); i++ )
  {
    char c = GatewayHolder[i];
    if ( c == '.' )
    {
      GatewayIndex++;
      continue;
    }
    GatewayVector[GatewayIndex] *= 10;
    GatewayVector[GatewayIndex] += c - '0';
  }
}

void loadCredentials() {
  EEPROM.begin(512);
  EEPROM.get(0, NetworkSSID);
  EEPROM.get(0 + sizeof(NetworkSSID), Password);
  EEPROM.get(0 + sizeof(NetworkSSID) + sizeof(Password), Gateway);
  EEPROM.get(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway), StaticIP);
  char ok[2 + 1];
  EEPROM.get(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway) + sizeof(StaticIP), ok);
  EEPROM.end();
  if (String(ok) != String("OK")) {
    Serial.println();
    Serial.println("ok ausente");
    Serial.println();
    NetworkSSID[0] = 0;
    Password[0] = 0;
  }else{
  Serial.println();
  Serial.println("ok presente");
  Serial.println();
  }

  Serial.println();
  Serial.println("Recovered credentials:");
  Serial.print("Network SSID: "); Serial.println(NetworkSSID);
  Serial.print("Network PSK: "); Serial.println(Password);
  Serial.print("Gateway: "); Serial.println(Gateway);
  Serial.print("IPv4: "); Serial.println(StaticIP);
}

void saveCredentials() {
  SSIDHolder.toCharArray(NetworkSSID, SSIDHolder.length() + 1);
  PSKHolder.toCharArray(Password, PSKHolder.length() + 1);
  GatewayHolder.toCharArray(Gateway, GatewayHolder.length() + 1);
  StaticIPHolder.toCharArray(StaticIP, StaticIPHolder.length() + 1);

  EEPROM.begin(512);
  EEPROM.put(0, NetworkSSID);
  EEPROM.put(0 + sizeof(NetworkSSID), Password);
  EEPROM.put(0 + sizeof(NetworkSSID) + sizeof(Password), Gateway);
  EEPROM.put(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway), StaticIP);
  char ok[2 + 1] = "OK";
  EEPROM.put(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway) + sizeof(StaticIP), ok);
  EEPROM.commit();
  EEPROM.end();
}

void scanNetwork(){
  nn = WiFi.scanNetworks();
  for (int i = 0; i < nn; i++) {
    NetworkHolder[i] = WiFi.SSID(i);
    Serial.println(NetworkHolder[i]);
    delay(10);
  }       
}
  
void loop() {}
