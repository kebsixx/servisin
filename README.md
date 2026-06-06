# servisin

![Language](https://img.shields.io/badge/Language-C-blue)
![Project](https://img.shields.io/badge/Project-CLI-green)
![Topic](https://img.shields.io/badge/Data%20Structure-Priority%20Queue-orange)

`servisin` adalah project bahasa C berbasis CLI untuk mengelola antrian servis laptop menggunakan konsep `Priority Queue`. Sistem ini digunakan untuk mencatat data servis customer, mengatur urutan pengerjaan berdasarkan prioritas kerusakan, mengubah status servis, melakukan pencarian data, dan menampilkan hasil sorting.

**About repo:** Aplikasi CLI bahasa C untuk mengelola antrian servis laptop menggunakan Priority Queue.

## Fitur

- Tambah data servis laptop
- Lihat antrian servis berdasarkan prioritas
- Ambil servis berikutnya secara otomatis
- Selesaikan servis dengan input biaya akhir
- Serah terima servis ke customer
- Cari data servis berdasarkan ID, nama customer, atau status
- Sorting data berdasarkan prioritas, estimasi biaya, atau biaya akhir
- Tampilkan seluruh data servis

## Konsep yang Digunakan

Project ini dibuat menggunakan materi dasar Struktur Data:

- Struct
- Array
- Function
- Priority Queue
- Searching
- Sorting

## Struktur Data

Data servis disimpan dalam struct berikut:

```c
typedef struct {
    int idServis;
    char namaCustomer[100];
    char noHP[20];
    char merk[50];
    char tipe[50];
    int jenisKerusakan;
    int prioritas;
    char keluhan[200];
    char status[50];
    float estimasiBiaya;
    float biayaAkhir;
} Servis;
```

Seluruh data disimpan dalam array global dengan kapasitas maksimum `100` data.

## Jenis Kerusakan dan Prioritas

Pilihan jenis kerusakan:

1. Mati Total
2. Tidak Bisa Booting / Bootloop
3. Overheat
4. Layar Rusak
5. Keyboard Rusak
6. Baterai Bermasalah
7. Speaker Rusak
8. Port Charger Rusak

Aturan prioritas:

- Prioritas `1`: Mati Total, Port Charger Rusak
- Prioritas `2`: Tidak Bisa Booting / Bootloop, Overheat, Layar Rusak
- Prioritas `3`: Keyboard Rusak, Baterai Bermasalah, Speaker Rusak

Semakin kecil nilai prioritas, semakin dahulu servis diproses.

## Alur Status

Status servis pada program:

- `MENUNGGU`
- `DIPROSES`
- `SELESAI`
- `DIAMBIL`

Urutan perubahan status:

```text
MENUNGGU -> DIPROSES -> SELESAI -> DIAMBIL
```

## Menu Program

```text
=====================================
 SISTEM ANTRIAN SERVIS LAPTOP
=====================================
1. Tambah Data Servis
2. Lihat Antrian Prioritas
3. Ambil Servis Berikutnya
4. Selesaikan Servis
5. Serah Terima Servis
6. Cari Data Servis
7. Sorting Data
8. Tampilkan Semua Data
0. Keluar
=====================================
```

## Contoh Output

Berikut contoh tampilan menu utama program saat dijalankan:

```text
=====================================
 SISTEM ANTRIAN SERVIS LAPTOP
=====================================
1. Tambah Data Servis
2. Lihat Antrian Prioritas
3. Ambil Servis Berikutnya
4. Selesaikan Servis
5. Serah Terima Servis
6. Cari Data Servis
7. Sorting Data
8. Tampilkan Semua Data
0. Keluar
=====================================
Pilih menu:
```

Contoh output saat menambahkan data servis:

```text
--- Tambah Data Servis ---
Nama Customer        : Anwar
No HP                : 08123456789
Merk Laptop          : ASUS
Tipe Laptop          : TUF F15
Keluhan              : Tidak bisa menyala
Pilih jenis kerusakan [1-8]: 1
Estimasi Biaya       : 350000

Data servis berhasil ditambahkan.
ID Servis  : 1
Prioritas  : 1
Status     : MENUNGGU
```

## Cara Menjalankan

Pastikan Anda memiliki compiler C seperti `gcc`.

Contoh kompilasi:

```bash
gcc main.c -o main
```

Jalankan program:

```bash
./main
```

Di Windows Command Prompt:

```bash
main.exe
```

## Algoritma

### Priority Queue

Program menggunakan `Priority Queue` berbasis array. Saat menu `Ambil Servis Berikutnya` dipilih, sistem akan mencari data dengan status `MENUNGGU`, lalu memilih prioritas tertinggi. Jika ada beberapa data dengan prioritas sama, data yang lebih dulu masuk akan diproses lebih dahulu (FIFO).

### Searching

Pencarian dilakukan dengan `linear search` untuk:

- ID Servis
- Nama Customer
- Status

### Sorting

Sorting menggunakan `Bubble Sort` pada salinan array agar urutan antrian asli tidak berubah. Kriteria sorting:

- Prioritas
- Estimasi Biaya
- Biaya Akhir

## Struktur File

```text
.
├── main.c
└── README.md
```

## Author

Project ini dibuat sebagai tugas Struktur Data / Algoritma dan Struktur Data.
