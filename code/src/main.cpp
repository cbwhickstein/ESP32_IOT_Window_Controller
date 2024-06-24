#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <WiFi.h>
#include <secret.hpp>

bool state = true;

// Create an instance of the web server
AsyncWebServer server(80);

// html string
String website_window_closed = R"(
<!DOCTYPE html>
<html>

<head>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <title>Window Control</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <style>
        body {
            margin: 0;
        }

        .button {
            width: 100vw;
            height: 100vh;
            background-color: rgba(55, 110, 33, 0.623);
            display: flex;
            justify-content: center;
            align-items: center;
            font-size: 10vw;
            margin-left: 0%;
            border: 0%;
        }
        
        .button a {
            color: rgb(29, 4, 4);
            width: 100%;
            height: 100%;
            display: flex;
            justify-content: center;
            align-items: center;
        }

    </style>
</head>

<body>
    <div class="button"><a href="./toggle">Fenster Öffnen</a></div>
</body>

</html>
)";

String website_window_open = R"(
<!DOCTYPE html>
<html>

<head>
    <meta charset='utf-8'>
    <meta http-equiv='X-UA-Compatible' content='IE=edge'>
    <title>Window Control</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
    <style>
        body {
            margin: 0;
        }

        .button {
            width: 100vw;
            height: 100vh;
            background-color: rgba(168, 43, 43, 0.795);
            display: flex;
            justify-content: center;
            align-items: center;
            font-size: 10vw;
            margin-left: 0%;
            border: 0%;
        }
        
        .button a {
            color: rgb(29, 4, 4);
            width: 100%;
            height: 100%;
            display: flex;
            justify-content: center;
            align-items: center;
        }

    </style>
</head>

<body>
    <div class="button"><a href="./toggle">Fenster Schließen</a></div>
</body>

</html>
)";

String toggle_redirect = R"(
<head>
    <meta http-equiv=\"Refresh\" content=\"0; URL=./\" />
</head>
)";

void
setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  // Print Chip info
  // Retrieve and print the ESP32 chip information
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  Serial.println("ESP32 Chip Information:");
  Serial.printf("Model: %s\n",
                chip_info.model == CHIP_ESP32 ? "ESP32" : "Unknown");
  Serial.printf("Cores: %d\n", chip_info.cores);
  Serial.printf("Revision: %d\n", chip_info.revision);
  Serial.printf("Features: %s%s%s\n",
                (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "802.11bgn "
                                                             : "",
                (chip_info.features & CHIP_FEATURE_BLE) ? "BLE " : "",
                (chip_info.features & CHIP_FEATURE_BT) ? "BT" : "");
  Serial.printf("Flash: %dMB %s\n",
                spi_flash_get_chip_size() / (1024 * 1024),
                (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded\n"
                                                              : "external\n");

  // create server
  Serial.print("\nConnecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    if (state)
      request->send(200, "text/html", website_window_closed);
    else
      request->send(200, "text/html", website_window_open);
  });

  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest* request) {
    state = !state;
    request->send(303, "text/html", toggle_redirect);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void
loop()
{
}
