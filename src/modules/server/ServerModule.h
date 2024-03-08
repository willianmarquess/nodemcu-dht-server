#include <ESPAsyncTCP.h>
#include "ESPAsyncWebServer.h"
#include "LittleFS.h"

class ServerModule
{
public:
  ServerModule(unsigned int port = 80) : port(port), web_server(port), web_socket("/ws") {}
  ~ServerModule() {}

  void init()
  {
    this->initWebSocket();
    this->initWebServer();
  }

  void notifyAll(String message) {
    this->web_socket.textAll(message);
  }

private:
  unsigned int port;
  AsyncWebServer web_server;
  AsyncWebSocket web_socket;

  void initWebSocket()
  {
    this->web_socket.onEvent([](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                             {
    switch (type) {
      case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
      case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
      case WS_EVT_DATA:
      case WS_EVT_PONG:
      case WS_EVT_ERROR:
        break;
    } });
  }

  void initWebServer()
  {
    this->web_server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    this->web_server.onNotFound([](AsyncWebServerRequest *request)
                                { request->send(404, "text/plain", "Not found"); });

    this->web_server.addHandler(&this->web_socket);
    this->web_server.begin();
  }
};