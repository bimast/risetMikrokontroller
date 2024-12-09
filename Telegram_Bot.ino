#include <WiFi.h>
#include <HTTPClient.h>

// Konfigurasi WiFi
const char* ssid = "TestWiFi";       // Ganti dengan nama WiFi Anda
const char* password = "12345678"; // Ganti dengan password WiFi Anda

// Konfigurasi Bot Telegram
const String BOT_TOKEN = "8002809397:AAH6X1LP-fWkcx4r_FbdheqYFR0gNeNdg-s";    // Ganti dengan Bot Token Anda
const String CHAT_ID = "947396333";        // Ganti dengan Chat ID Anda

// Fungsi untuk mengirim pesan
void sendMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage?chat_id=" + CHAT_ID + "&text=" + message;

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("Pesan terkirim: ");
      Serial.println(message);
    } else {
      Serial.print("Gagal mengirim pesan, kode error: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi tidak tersambung.");
  }
}

void setup() {
  Serial.begin(115200);

  // Hubungkan ke WiFi
  Serial.print("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nTersambung ke WiFi!");

  // Kirim pesan pertama
  sendMessage("Halo! Bot Telegram berbasis ESP32 telah aktif!");
}

void loop() {
  // Contoh: Kirim pesan setiap 30 detik
  sendMessage("Ini adalah pesan otomatis dari ESP32.");
  delay(30000); // 30 detik
}
