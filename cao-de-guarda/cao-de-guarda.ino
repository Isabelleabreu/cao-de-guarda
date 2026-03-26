#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

//Credenciais da rede industrial
const char* ssid = "Galaxy A35 5G A200";
const char* password = "isinhaaa";


//URL de teste (JSONPlaceholder é um serviço comum para testes de API)
const char* serverName = "https://jsonplaceholder.typicode.com/todos/1";

int ledVerde = 18;
int ledVermelho = 19;

void setup() {
  Serial.begin(115200);

  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Conectando ao Wi-fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado com sucesso!");
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, HIGH);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    //Criamos o objeto cliente seguro
    WiFiClientSecure *client = new WiFiClientSecure;

  if (client) {
    //Em um cenário real, você usaria client->setCACert(rootCACertificate);
    //Para este exemplo simples, vamos ignorar a validação do certificado:
    client->setInsecure();

    HTTPClient https;

    Serial.print("[HTTPS] Iniciando requisição...\n");
  

  if (https.begin(*client, serverName)) {

    //Realiza o GET
    int httpCode = https.GET();

    //httpCode será positivo se o servidor responder
    if (httpCode > 0) {
      Serial.printf("[HTTPS] Código de resposta: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = https.getString();
        Serial.println("Conteúdo recebido");
        Serial.println(payload);
      }
    } else {
      Serial.printf("[HTTPS] Falha na requisição, erro: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
          } else {
            Serial.printf("[HTTPS] Não foi possível conectar ao servidor\n");
            digitalWrite(ledVerde, LOW);
            digitalWrite(ledVermelho, HIGH);
          }
          delete client;
        }
      }

      // Aguarda 10 segundos para a próxima leitura (evita sobrecarga no servidor)
      delay(10000);
}