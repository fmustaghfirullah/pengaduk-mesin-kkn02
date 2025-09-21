# Mesin Pengaduk Pupuk Otomatis ⚙️

Proyek Arduino sederhana untuk mengotomatiskan proses pencampuran pupuk cair. Mesin ini akan aktif berdasarkan kondisi suhu dan kelembapan yang terdeteksi oleh sensor DHT11.

## Deskripsi Proyek

Tujuan utama dari alat ini adalah untuk menjaga adonan pupuk tetap dalam kondisi ideal. Alat akan secara otomatis menyalakan pompa air untuk menambahkan cairan dan kemudian menyalakan dinamo pengaduk jika kondisi lingkungan (suhu dan kelembapan) memenuhi kriteria yang telah ditentukan.

---

## Cara Kerja Alat 🧠

Logika utama alat ini berada di dalam fungsi `loop()`:
1.  **Membaca Sensor**: Setiap beberapa detik, alat akan membaca data **suhu** dan **kelembapan** dari sensor DHT11.
2.  **Pengecekan Kondisi**: Alat akan memeriksa apakah kondisi saat ini sesuai dengan yang telah diatur. Logika utamanya adalah:
    ```
    JIKA (Suhu saat ini > Batas Suhu) DAN (Kelembapan saat ini < Batas Kelembapan)
    ```
    Artinya, proses akan berjalan jika udara terasa "panas" dan "kering" dari batas yang ditentukan.
3.  **Menjalankan Proses**: Jika kondisi terpenuhi, alat akan:
    * Menyalakan **pompa air** selama beberapa detik untuk menambahkan cairan.
    * Mematikan pompa air.
    * Menyalakan **dinamo pengaduk** selama beberapa menit untuk mencampur adonan.
    * Mematikan dinamo pengaduk.
4.  **Mode Tunggu**: Setelah proses selesai, alat akan masuk ke mode "tunggu" selama periode waktu tertentu sebelum mulai mengecek kondisi lagi. Ini untuk mencegah mesin bekerja terus-menerus.
5.  **Kondisi Normal**: Jika suhu dan kelembapan tidak memenuhi kriteria, alat tidak akan melakukan apa-apa dan terus memantau.

---

## Komponen yang Dibutuhkan 🔌

* Mikrokontroler (Arduino Uno, Nano, dll.)
* Sensor Suhu & Kelembapan **DHT11**
* **Relay Module 2 Channel** (untuk pompa dan pengaduk)
* Pompa Air DC
* Dinamo Pengaduk DC
* Kabel Jumper

### Skema Rangkaian

| Komponen            | Pin Arduino | Keterangan                        |
| ------------------- | :---------: | --------------------------------- |
| **Sensor DHT11** | `PIN 2`     | Hubungkan pin `VCC` ke `5V` & `GND` ke `GND` |
| **Relay Pompa Air** |   `PIN 7`   | Hubungkan ke `IN1` pada modul relay     |
| **Relay Pengaduk** |   `PIN 8`   | Hubungkan ke `IN2` pada modul relay     |

*Pastikan modul relay juga terhubung ke `5V` dan `GND` Arduino.*

---

## Instalasi Pustaka (Library)

Proyek ini memerlukan satu pustaka tambahan:
1.  **DHT sensor library** oleh Adafruit.

Anda bisa menginstalnya melalui **Library Manager** di Arduino IDE:
* Buka Arduino IDE.
* Pilih `Sketch` > `Include Library` > `Manage Libraries...`.
* Cari `DHT sensor library` dan klik **Install**.

---

## 🔧 Kustomisasi & Pengembangan (Untuk Teman Anda!)

Bagian ini adalah yang paling penting jika Anda ingin mengubah cara kerja mesin. Semua pengaturan utama ada di bagian atas kode. Anda tidak perlu mengubah logika di dalam `loop()`.

```cpp
// --- PENGATURAN PIN ---
#define PIN_DHT 2               // Pin untuk sensor DHT11
#define PIN_RELAY_POMPA 7       // Pin untuk relay pompa air
#define PIN_RELAY_PENGADUK 8    // Pin untuk relay dinamo pengaduk

// --- PENGATURAN KONDISI ---
const float SUHU_AKTIF = 20.0;        // Mesin akan aktif jika suhu DI ATAS nilai ini (dalam Celcius)
const float KELEMBAPAN_AKTIF = 98.0;  // Mesin akan aktif jika kelembapan DI BAWAH nilai ini (dalam %)

// --- PENGATURAN DURASI (dalam milidetik) ---
// 1000 milidetik = 1 detik
const unsigned long DURASI_POMPA = 5000;        // 5 detik -> Ubah untuk mengatur lamanya pompa menyala
const unsigned long DURASI_PENGADUK = 120000;   // 2 menit -> Ubah untuk mengatur lamanya pengaduk berputar
const unsigned long PERIODE_TUNGGU = 120000;    // 2 menit -> Ubah untuk mengatur waktu jeda setelah proses selesai
