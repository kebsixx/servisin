#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Konstanta program */
#define MAX 100
#define STATUS_MENUNGGU "MENUNGGU"
#define STATUS_DIPROSES "DIPROSES"
#define STATUS_SELESAI "SELESAI"
#define STATUS_DIAMBIL "DIAMBIL"

/* Struktur data servis */
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

/* Variabel global */
Servis dataServis[MAX];
int jumlahData = 0;
int nextId = 1;

/* Prototype menu utama */
void tampilkanMenu(void);
void inputServis(void);
void tampilkanAntrianPrioritas(void);
void ambilServisBerikutnya(void);
void selesaikanServis(void);
void serahTerimaServis(void);
void cariDataServis(void);
void sortingData(void);
void tampilkanSemuaData(void);

/* Prototype logika servis */
int tentukanPrioritas(int jenisKerusakan);
int cariIndexById(int id);
int cariIndexServisBerikutnya(void);
int adaDataDenganStatus(const char *status);

/* Prototype pencarian dan sorting */
int stringSamaIgnoreCase(const char *a, const char *b);
int containsIgnoreCase(const char *teks, const char *kataKunci);
void copyArray(Servis tujuan[], Servis sumber[], int size);
void swapServis(Servis *a, Servis *b);
void bubbleSortByPrioritas(Servis arr[], int size);
void bubbleSortByEstimasiBiaya(Servis arr[], int size);
void bubbleSortByBiayaAkhir(Servis arr[], int size);

/* Prototype input dan output */
void tampilkanJenisKerusakan(void);
const char *namaKerusakan(int jenisKerusakan);
void tampilkanSatuServis(Servis servis);
void tampilkanDaftarDenganFilterStatus(const char *status);
void tampilkanDataDariArray(Servis arr[], int size);
void clearInputBuffer(void);
void bacaString(const char *prompt, char *tujuan, int ukuran);
int bacaIntDalamRentang(const char *prompt, int min, int max);
float bacaFloatMinimum(const char *prompt, float min);
void pauseEnter(void);

/* =========================
   Program Utama
   ========================= */
int main(void) {
    int pilihan;

    do {
        tampilkanMenu();
        pilihan = bacaIntDalamRentang("Pilih menu: ", 0, 8);

        switch (pilihan) {
            case 1:
                inputServis();
                break;
            case 2:
                tampilkanAntrianPrioritas();
                break;
            case 3:
                ambilServisBerikutnya();
                break;
            case 4:
                selesaikanServis();
                break;
            case 5:
                serahTerimaServis();
                break;
            case 6:
                cariDataServis();
                break;
            case 7:
                sortingData();
                break;
            case 8:
                tampilkanSemuaData();
                break;
            case 0:
                printf("\nProgram selesai. Terima kasih.\n");
                break;
        }
    } while (pilihan != 0);

    return 0;
}

/* =========================
   Function Menu
   ========================= */
void tampilkanMenu(void) {
    printf("\n=====================================\n");
    printf(" SISTEM ANTRIAN SERVIS LAPTOP\n");
    printf("=====================================\n");
    printf("1. Tambah Data Servis\n");
    printf("2. Lihat Antrian Prioritas\n");
    printf("3. Ambil Servis Berikutnya\n");
    printf("4. Selesaikan Servis\n");
    printf("5. Serah Terima Servis\n");
    printf("6. Cari Data Servis\n");
    printf("7. Sorting Data\n");
    printf("8. Tampilkan Semua Data\n");
    printf("0. Keluar\n");
    printf("=====================================\n");
}

void inputServis(void) {
    Servis servisBaru;

    if (jumlahData >= MAX) {
        printf("\nData servis sudah penuh. Tidak bisa menambah data baru.\n");
        pauseEnter();
        return;
    }

    printf("\n--- Tambah Data Servis ---\n");
    servisBaru.idServis = nextId++;
    bacaString("Nama Customer        : ", servisBaru.namaCustomer, sizeof(servisBaru.namaCustomer));
    bacaString("No HP                : ", servisBaru.noHP, sizeof(servisBaru.noHP));
    bacaString("Merk Laptop          : ", servisBaru.merk, sizeof(servisBaru.merk));
    bacaString("Tipe Laptop          : ", servisBaru.tipe, sizeof(servisBaru.tipe));
    bacaString("Keluhan              : ", servisBaru.keluhan, sizeof(servisBaru.keluhan));

    tampilkanJenisKerusakan();
    servisBaru.jenisKerusakan = bacaIntDalamRentang("Pilih jenis kerusakan [1-8]: ", 1, 8);
    servisBaru.prioritas = tentukanPrioritas(servisBaru.jenisKerusakan);
    servisBaru.estimasiBiaya = bacaFloatMinimum("Estimasi Biaya        : ", 0.0f);
    servisBaru.biayaAkhir = 0.0f;
    strcpy(servisBaru.status, STATUS_MENUNGGU);

    dataServis[jumlahData] = servisBaru;
    jumlahData++;

    printf("\nData servis berhasil ditambahkan.\n");
    printf("ID Servis  : %d\n", servisBaru.idServis);
    printf("Prioritas  : %d\n", servisBaru.prioritas);
    printf("Status     : %s\n", servisBaru.status);
    pauseEnter();
}

void tampilkanAntrianPrioritas(void) {
    int prioritas;
    int i;

    printf("\n--- Antrian Prioritas ---\n");

    if (!adaDataDenganStatus(STATUS_MENUNGGU)) {
        printf("Belum ada data pada antrian.\n");
        pauseEnter();
        return;
    }

    for (prioritas = 1; prioritas <= 3; prioritas++) {
        int ditemukanPadaPrioritas = 0;

        printf("\nPrioritas %d\n", prioritas);
        printf("------------------------------\n");

        for (i = 0; i < jumlahData; i++) {
            if (stringSamaIgnoreCase(dataServis[i].status, STATUS_MENUNGGU) &&
                dataServis[i].prioritas == prioritas) {
                tampilkanSatuServis(dataServis[i]);
                ditemukanPadaPrioritas = 1;
            }
        }

        if (!ditemukanPadaPrioritas) {
            printf("Tidak ada data pada prioritas ini.\n");
        }
    }

    pauseEnter();
}

void ambilServisBerikutnya(void) {
    int index = cariIndexServisBerikutnya();

    printf("\n--- Ambil Servis Berikutnya ---\n");

    if (index == -1) {
        printf("Tidak ada servis dengan status MENUNGGU.\n");
        pauseEnter();
        return;
    }

    strcpy(dataServis[index].status, STATUS_DIPROSES);

    printf("Servis berikutnya berhasil diambil.\n");
    tampilkanSatuServis(dataServis[index]);
    pauseEnter();
}

void selesaikanServis(void) {
    int id;
    int index;

    printf("\n--- Selesaikan Servis ---\n");

    if (!adaDataDenganStatus(STATUS_DIPROSES)) {
        printf("Tidak ada servis yang sedang diproses.\n");
        pauseEnter();
        return;
    }

    tampilkanDaftarDenganFilterStatus(STATUS_DIPROSES);
    id = bacaIntDalamRentang("Masukkan ID servis yang selesai: ", 1, 1000000);
    index = cariIndexById(id);

    if (index == -1) {
        printf("ID servis tidak ditemukan.\n");
        pauseEnter();
        return;
    }

    if (!stringSamaIgnoreCase(dataServis[index].status, STATUS_DIPROSES)) {
        printf("Servis dengan ID tersebut tidak berstatus DIPROSES.\n");
        pauseEnter();
        return;
    }

    dataServis[index].biayaAkhir = bacaFloatMinimum("Masukkan biaya akhir: ", 0.0f);
    strcpy(dataServis[index].status, STATUS_SELESAI);

    printf("Servis berhasil diubah menjadi SELESAI.\n");
    tampilkanSatuServis(dataServis[index]);
    pauseEnter();
}

void serahTerimaServis(void) {
    int id;
    int index;

    printf("\n--- Serah Terima Servis ---\n");

    if (!adaDataDenganStatus(STATUS_SELESAI)) {
        printf("Tidak ada servis yang siap diambil customer.\n");
        pauseEnter();
        return;
    }

    tampilkanDaftarDenganFilterStatus(STATUS_SELESAI);
    id = bacaIntDalamRentang("Masukkan ID servis yang diambil: ", 1, 1000000);
    index = cariIndexById(id);

    if (index == -1) {
        printf("ID servis tidak ditemukan.\n");
        pauseEnter();
        return;
    }

    if (!stringSamaIgnoreCase(dataServis[index].status, STATUS_SELESAI)) {
        printf("Servis dengan ID tersebut tidak berstatus SELESAI.\n");
        pauseEnter();
        return;
    }

    strcpy(dataServis[index].status, STATUS_DIAMBIL);

    printf("Serah terima berhasil dilakukan.\n");
    tampilkanSatuServis(dataServis[index]);
    pauseEnter();
}

void cariDataServis(void) {
    int pilihan;
    int id;
    int i;
    int ditemukan = 0;
    char kataKunci[100];
    char status[50];

    printf("\n--- Cari Data Servis ---\n");

    if (jumlahData == 0) {
        printf("Belum ada data servis.\n");
        pauseEnter();
        return;
    }

    printf("1. Cari berdasarkan ID Servis\n");
    printf("2. Cari berdasarkan Nama Customer\n");
    printf("3. Cari berdasarkan Status\n");
    pilihan = bacaIntDalamRentang("Pilih metode pencarian: ", 1, 3);

    switch (pilihan) {
        case 1:
            id = bacaIntDalamRentang("Masukkan ID servis: ", 1, 1000000);
            i = cariIndexById(id);
            if (i != -1) {
                tampilkanSatuServis(dataServis[i]);
                ditemukan = 1;
            }
            break;
        case 2:
            bacaString("Masukkan nama customer: ", kataKunci, sizeof(kataKunci));
            for (i = 0; i < jumlahData; i++) {
                if (containsIgnoreCase(dataServis[i].namaCustomer, kataKunci)) {
                    tampilkanSatuServis(dataServis[i]);
                    ditemukan = 1;
                }
            }
            break;
        case 3:
            printf("Pilihan status:\n");
            printf("1. MENUNGGU\n");
            printf("2. DIPROSES\n");
            printf("3. SELESAI\n");
            printf("4. DIAMBIL\n");
            i = bacaIntDalamRentang("Pilih status: ", 1, 4);

            if (i == 1) {
                strcpy(status, STATUS_MENUNGGU);
            } else if (i == 2) {
                strcpy(status, STATUS_DIPROSES);
            } else if (i == 3) {
                strcpy(status, STATUS_SELESAI);
            } else {
                strcpy(status, STATUS_DIAMBIL);
            }

            for (i = 0; i < jumlahData; i++) {
                if (stringSamaIgnoreCase(dataServis[i].status, status)) {
                    tampilkanSatuServis(dataServis[i]);
                    ditemukan = 1;
                }
            }
            break;
    }

    if (!ditemukan) {
        printf("Data servis tidak ditemukan.\n");
    }

    pauseEnter();
}

void sortingData(void) {
    int pilihan;
    Servis salinan[MAX];

    printf("\n--- Sorting Data ---\n");

    if (jumlahData == 0) {
        printf("Belum ada data untuk diurutkan.\n");
        pauseEnter();
        return;
    }

    printf("1. Sorting berdasarkan Prioritas\n");
    printf("2. Sorting berdasarkan Estimasi Biaya\n");
    printf("3. Sorting berdasarkan Biaya Akhir\n");
    pilihan = bacaIntDalamRentang("Pilih sorting: ", 1, 3);

    copyArray(salinan, dataServis, jumlahData);

    if (pilihan == 1) {
        bubbleSortByPrioritas(salinan, jumlahData);
        printf("\nHasil sorting berdasarkan prioritas:\n");
    } else if (pilihan == 2) {
        bubbleSortByEstimasiBiaya(salinan, jumlahData);
        printf("\nHasil sorting berdasarkan estimasi biaya:\n");
    } else {
        bubbleSortByBiayaAkhir(salinan, jumlahData);
        printf("\nHasil sorting berdasarkan biaya akhir:\n");
    }

    tampilkanDataDariArray(salinan, jumlahData);
    pauseEnter();
}

void tampilkanSemuaData(void) {
    printf("\n--- Semua Data Servis ---\n");

    if (jumlahData == 0) {
        printf("Belum ada data servis.\n");
        pauseEnter();
        return;
    }

    tampilkanDataDariArray(dataServis, jumlahData);
    pauseEnter();
}

/* =========================
   Function Logika Servis
   ========================= */
int tentukanPrioritas(int jenisKerusakan) {
    if (jenisKerusakan == 1 || jenisKerusakan == 8) {
        return 1;
    }

    if (jenisKerusakan == 2 || jenisKerusakan == 3 || jenisKerusakan == 4) {
        return 2;
    }

    return 3;
}

int cariIndexById(int id) {
    int i;

    for (i = 0; i < jumlahData; i++) {
        if (dataServis[i].idServis == id) {
            return i;
        }
    }

    return -1;
}

int cariIndexServisBerikutnya(void) {
    int i;
    int indexTerpilih = -1;

    for (i = 0; i < jumlahData; i++) {
        if (!stringSamaIgnoreCase(dataServis[i].status, STATUS_MENUNGGU)) {
            continue;
        }

        if (indexTerpilih == -1 ||
            dataServis[i].prioritas < dataServis[indexTerpilih].prioritas) {
            indexTerpilih = i;
        }
    }

    return indexTerpilih;
}

int adaDataDenganStatus(const char *status) {
    int i;

    for (i = 0; i < jumlahData; i++) {
        if (stringSamaIgnoreCase(dataServis[i].status, status)) {
            return 1;
        }
    }

    return 0;
}

/* =========================
   Function Pencarian dan Sorting
   ========================= */
int stringSamaIgnoreCase(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }

    return *a == '\0' && *b == '\0';
}

int containsIgnoreCase(const char *teks, const char *kataKunci) {
    int i;
    int j;

    if (kataKunci[0] == '\0') {
        return 1;
    }

    for (i = 0; teks[i] != '\0'; i++) {
        j = 0;
        while (teks[i + j] != '\0' &&
               kataKunci[j] != '\0' &&
               tolower((unsigned char)teks[i + j]) == tolower((unsigned char)kataKunci[j])) {
            j++;
        }
        if (kataKunci[j] == '\0') {
            return 1;
        }
    }

    return 0;
}

void copyArray(Servis tujuan[], Servis sumber[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        tujuan[i] = sumber[i];
    }
}

void swapServis(Servis *a, Servis *b) {
    Servis temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSortByPrioritas(Servis arr[], int size) {
    int i;
    int j;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j].prioritas > arr[j + 1].prioritas) {
                swapServis(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubbleSortByEstimasiBiaya(Servis arr[], int size) {
    int i;
    int j;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j].estimasiBiaya > arr[j + 1].estimasiBiaya) {
                swapServis(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void bubbleSortByBiayaAkhir(Servis arr[], int size) {
    int i;
    int j;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j].biayaAkhir > arr[j + 1].biayaAkhir) {
                swapServis(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/* =========================
   Function Input dan Output
   ========================= */
void tampilkanJenisKerusakan(void) {
    printf("\nJenis Kerusakan:\n");
    printf("1. Mati Total\n");
    printf("2. Tidak Bisa Booting / Bootloop\n");
    printf("3. Overheat\n");
    printf("4. Layar Rusak\n");
    printf("5. Keyboard Rusak\n");
    printf("6. Baterai Bermasalah\n");
    printf("7. Speaker Rusak\n");
    printf("8. Port Charger Rusak\n");
}

const char *namaKerusakan(int jenisKerusakan) {
    switch (jenisKerusakan) {
        case 1:
            return "Mati Total";
        case 2:
            return "Tidak Bisa Booting / Bootloop";
        case 3:
            return "Overheat";
        case 4:
            return "Layar Rusak";
        case 5:
            return "Keyboard Rusak";
        case 6:
            return "Baterai Bermasalah";
        case 7:
            return "Speaker Rusak";
        case 8:
            return "Port Charger Rusak";
        default:
            return "Tidak Diketahui";
    }
}

void tampilkanSatuServis(Servis servis) {
    printf("ID Servis       : %d\n", servis.idServis);
    printf("Nama Customer   : %s\n", servis.namaCustomer);
    printf("No HP           : %s\n", servis.noHP);
    printf("Merk            : %s\n", servis.merk);
    printf("Tipe            : %s\n", servis.tipe);
    printf("Kerusakan       : %s\n", namaKerusakan(servis.jenisKerusakan));
    printf("Prioritas       : %d\n", servis.prioritas);
    printf("Keluhan         : %s\n", servis.keluhan);
    printf("Status          : %s\n", servis.status);
    printf("Estimasi Biaya  : Rp %.2f\n", servis.estimasiBiaya);
    printf("Biaya Akhir     : Rp %.2f\n", servis.biayaAkhir);
    printf("-------------------------------------\n");
}

void tampilkanDaftarDenganFilterStatus(const char *status) {
    int i;

    for (i = 0; i < jumlahData; i++) {
        if (stringSamaIgnoreCase(dataServis[i].status, status)) {
            tampilkanSatuServis(dataServis[i]);
        }
    }
}

void tampilkanDataDariArray(Servis arr[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        tampilkanSatuServis(arr[i]);
    }
}

void clearInputBuffer(void) {
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void bacaString(const char *prompt, char *tujuan, int ukuran) {
    size_t panjang;

    do {
        printf("%s", prompt);
        if (fgets(tujuan, ukuran, stdin) != NULL) {
            panjang = strcspn(tujuan, "\n");

            if (tujuan[panjang] == '\n') {
                tujuan[panjang] = '\0';
            } else {
                clearInputBuffer();
            }

            if (strlen(tujuan) > 0) {
                return;
            }
        }

        printf("Input tidak boleh kosong.\n");
    } while (1);
}

int bacaIntDalamRentang(const char *prompt, int min, int max) {
    int nilai;
    int hasilScan;

    do {
        printf("%s", prompt);
        hasilScan = scanf("%d", &nilai);
        clearInputBuffer();

        if (hasilScan == 1 && nilai >= min && nilai <= max) {
            return nilai;
        }

        printf("Input harus berupa angka antara %d dan %d.\n", min, max);
    } while (1);
}

float bacaFloatMinimum(const char *prompt, float min) {
    float nilai;
    int hasilScan;

    do {
        printf("%s", prompt);
        hasilScan = scanf("%f", &nilai);
        clearInputBuffer();

        if (hasilScan == 1 && nilai >= min) {
            return nilai;
        }

        printf("Input harus berupa angka minimal %.2f.\n", min);
    } while (1);
}

void pauseEnter(void) {
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
}
