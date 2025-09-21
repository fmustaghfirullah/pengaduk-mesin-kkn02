 #include <DHT.h>

#define PIN_DHT 2
#define PIN_RELAY_POMPA 7
#define PIN_RELAY_PENGADUK 8

const float SUHU_AKTIF = 20.0;
const float KELEMBAPAN_AKTIF = 98.0;

const unsigned long DURASI_POMPA = 5000;
const unsigned long DURASI_PENGADUK = 120000;
const unsigned long PERIODE_TUNGGU = 120000;

#define TIPE_DHT DHT11
DHT dht(PIN_DHT, TIPE_DHT);

void setup() {
  Serial.begin(9600);
  Serial.println("Mesin Pengaduk Pupuk Otomatis");

  pinMode(PIN_RELAY_POMPA, OUTPUT);
  pinMode(PIN_RELAY_PENGADUK, OUTPUT);

  digitalWrite(PIN_RELAY_POMPA, HIGH);
  digitalWrite(PIN_RELAY_PENGADUK, HIGH);

  dht.begin();
}

void loop() {
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  Serial.print("Kelembapan: ");
  Serial.print(h);
  Serial.print("%  |  ");
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println(" *C");

  if (t > SUHU_AKTIF && h < KELEMBAPAN_AKTIF) {
    Serial.println("Kondisi terpenuhi! Memulai proses pengadukan...");
    
    Serial.println("Menyalakan pompa air...");
    digitalWrite(PIN_RELAY_POMPA, LOW);
    delay(DURASI_POMPA);
    
    digitalWrite(PIN_RELAY_POMPA, HIGH);
    Serial.println("Pompa air mati.");
    delay(1000);

    Serial.println("Menyalakan dinamo pengaduk...");
    digitalWrite(PIN_RELAY_PENGADUK, LOW);
    delay(DURASI_PENGADUK);

    digitalWrite(PIN_RELAY_PENGADUK, HIGH);
    Serial.println("Dinamo pengaduk mati.");

    Serial.print("Proses selesai. Menunggu ");
    Serial.print(PERIODE_TUNGGU / 60000);
    Serial.println(" menit sebelum pengecekan berikutnya.");
    delay(PERIODE_TUNGGU);
    
  } else {
    Serial.println("Kondisi normal, tidak ada tindakan.");
  }
}
