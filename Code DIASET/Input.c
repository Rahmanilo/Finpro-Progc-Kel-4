#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int polidipsia;
    int poliuria;
    int diplopia;
    int asthenia;
    int ulkusKulit;
    int paretesia;
    int nausea;
} gejala;

typedef struct {
    char id[10];
    char nama[100];
    char gender[20];
    int umur;
    gejala gejala_pasien;
    float berat_badan_awal, berat_badan_akhir;
    float HbA1C_pasien;
    int glukosa_pasien;
    int skor;
} pasien;

static int id_pasien_berikutnya = 1;

char* buat_id_pasien() {
    char* id = (char*)malloc(10 * sizeof(char));
    if (id == NULL) {
        fprintf(stderr, "Kesalahan: Memori tidak cukup untuk membuat ID.\n");
        exit(1);
    }

    sprintf(id, "PSN%04d", id_pasien_berikutnya++);
    return id;
}

int input_gejala_valid(const char* pertanyaan) {
    int input;
    do {
        printf("%s", pertanyaan);
        // fflush(stdout); // pastikan prompt langsung muncul
        scanf("%d", &input);
        // while (getchar() != '\n'); // bersihkan newline tersisa
        if (input < 0 || input > 3) {
            printf("Input tidak valid! Masukkan angka antara 0 sampai 3.\n");
        }
    } while (input < 0 || input > 3);
    return input;
}

void inputPasien(pasien *p) {
    // Data Pasien
    printf("\nMasukkan nama anda: ");
    fgets(p->nama, sizeof(p->nama), stdin);
    p->nama[strcspn(p->nama, "\n")] = 0;
    printf("Masukkan umur anda: ");
    scanf("%d", &p->umur);
    getchar();

    printf("Laki-laki/Perempuan: ");
    fgets(p->gender, sizeof(p->gender), stdin);
    p->gender[strcspn(p->gender, "\n")] = 0;

    printf("Masukkan berat badan normal: ");
    scanf("%f", &p->berat_badan_awal);
    printf("Masukkan berat badan sekarang: ");
    scanf("%f", &p->berat_badan_akhir);

    // Gejala
    printf("\nHarap masukkan gejala Anda dalam skala 0-3!\n");
    p->gejala_pasien.polidipsia = input_gejala_valid("Seberapa sering Anda merasa haus?\n>> ");
    p->gejala_pasien.poliuria = input_gejala_valid("Seberapa sering Anda buang air kecil?\n>> ");
    p->gejala_pasien.diplopia = input_gejala_valid("Seberapa sering Anda memiliki pandangan yang berbayang?\n>> ");
    p->gejala_pasien.asthenia = input_gejala_valid("Seberapa sering Anda merasa lelah?\n>> ");
    p->gejala_pasien.ulkusKulit = input_gejala_valid("Seberapa sering Anda merasa luka Anda sulit sembuh?\n>> ");
    p->gejala_pasien.paretesia = input_gejala_valid("Seberapa sering Anda mengalami kesemutan?\n>> ");
    p->gejala_pasien.nausea = input_gejala_valid("Seberapa sering Anda merasa mual?\n>> ");


    // Hasil Lab
    printf("\nHarap masukkan hasil laboratorium Anda!\n");
    printf("Masukkan HbA1C (dalam persen): ");
    scanf("%f", &p->HbA1C_pasien);
    printf("Masukkan glukosa (dalam mg/dL): ");
    scanf("%d", &p->glukosa_pasien);
}