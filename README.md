# Student Record System / Öğrenci Kayıt Sistemi
 
A console-based student record management system implemented in C using a singly linked list.  
Tek yönlü bağlı liste (singly linked list) kullanılarak C dilinde yazılmış, konsol tabanlı öğrenci yönetim sistemi.
 
---
 
## Features / Özellikler
 
| # | English | Türkçe |
|---|---------|--------|
| 1 | Add new student (full name supported) | Yeni öğrenci kaydı ekleme (tam isim desteği) |
| 2 | Search by ID or full name | Numara veya tam isme göre arama |
| 3 | List students with average ≥ 60 | Ortalama 60+ öğrencileri listeleme |
| 4 | Update student record | Kayıt güncelleme |
| 5 | Delete student record | Kayıt silme |
| 6 | Calculate class midterm/final average | Sınıf vize/final ortalaması hesaplama |
| 7 | Find top student | En başarılı öğrenciyi bulma |
| 8 | Unique ID validation | Tekrar eden numara engelleme |
| 9 | Grade range validation (0–100) | Not aralığı doğrulama (0–100) |
| 10 | Auto save & load (binary file) | Otomatik kayıt ve yükleme (binary dosya) |
 
---


## Build & Run / Derleme ve Çalıştırma
 
**Linux / macOS**
```bash
gcc student_record_system.cpp -o student_record_system
./student_record_system
```
 
**Windows**
```bash
gcc student_record_system.cpp -o student_record_system.exe
student_record_system.exe
```
---

 ## Data Persistence / Veri Kalıcılığı
 
Records are automatically saved to `students.dat` on exit and loaded on startup.  
Kayıtlar, program kapanırken `students.dat` dosyasına otomatik olarak kaydedilir ve açılışta yüklenir.
 
> **Note / Not:** Do not manually edit `students.dat` — it is a binary file.  
> `students.dat` dosyasını elle düzenlemeyin — binary formattadır.
 
---
 
## Grade Calculation / Not Hesaplama
 
```
Average = Midterm × 0.4 + Final × 0.6
Ortalama = Vize × 0.4 + Final × 0.6
```
 
---
 
## Technical Details / Teknik Detaylar
 
- **Language / Dil:** C (C99)
- **Data Structure / Veri Yapısı:** Singly Linked List
- **File I/O:** Binary (`fread` / `fwrite`)
- **Input Validation:** Grade range 0–100, unique student ID, full name with spaces
 
