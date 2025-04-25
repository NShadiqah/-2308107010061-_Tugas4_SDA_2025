-Nama : Nur Shadiqah 

-NPM  : 2308107010061

- Penjelasan Tugas 4 :
 # 📊 Evaluasi Algoritma Sorting: Performa Waktu & Memori

Repositori ini berisi implementasi dan analisis perbandingan enam algoritma sorting klasik berdasarkan waktu eksekusi dan penggunaan memori terhadap dataset acak dalam skala besar (hingga 2 juta data).

---

## ✨ Tujuan

Melakukan benchmark terhadap algoritma sorting berikut:

- Bubble Sort  
- Selection Sort  
- Insertion Sort  
- Merge Sort  
- Quick Sort  
- Shell Sort  

Setiap algoritma diuji menggunakan data **angka acak** dan **kata acak** dengan ukuran mulai dari 10.000 hingga 2.000.000 elemen.

---

## 🛠 Teknologi & Metode

- **Bahasa**: C
- **Compiler**: GCC (MinGW)
- **Pengukuran waktu**: Fungsi `clock()` dari `<time.h>`
- **Pengukuran memori**: `GetProcessMemoryInfo()` dari `psapi.h` (Windows)
- **Dataset**: `data_angka.txt` dan `data_kata.txt` yang digenerate secara acak

---

## ▶️ Cara Menjalankan

```bash
gcc main.c -o benchmark -lpsapi
./benchmark angka data_angka.txt
./benchmark kata data_kata.txt

