#include <stdio.h>
#include <string.h>
#include "LogikaSkoring.c" 

#define MAKS_PASIEN 100
pasien daftar_pasien[MAKS_PASIEN];
int jumlah_pasien = 0;

int file_ada(const char* nama_file) {
    FILE *f = fopen(nama_file, "r");
    if (f) {
        fclose(f);
        return 1; 
    }
    return 0; 
}

void simpan_pasien_terakhir_ke_file() {
    int fileSudahAda = file_ada("data_pasien.txt");
    FILE *f = fopen("data_pasien.txt", "a");
    if (!f) {
        printf("Gagal membuka file.\n");
        return;
    }
    if (!fileSudahAda) {
        fprintf(f, "ID|Nama|Gender|Umur|BB_Awal|BB_Akhir|HbA1C|Glukosa|Gejala\n");
    }
    pasien *p = &daftar_pasien[jumlah_pasien - 1];
    fprintf(f, "%s|%s|%s|%d|%.2f|%.2f|%.2f|%d|%d,%d,%d,%d,%d,%d,%d\n",
            p->id, p->nama, p->gender, p->umur,
            p->berat_badan_awal, p->berat_badan_akhir,
            p->HbA1C_pasien, p->glukosa_pasien,
            p->gejala_pasien.polidipsia, p->gejala_pasien.poliuria,
            p->gejala_pasien.diplopia, p->gejala_pasien.asthenia,
            p->gejala_pasien.ulkusKulit, p->gejala_pasien.paretesia,
            p->gejala_pasien.nausea);
    fclose(f);
}

void simpan_semua_ke_file() {
    FILE *f = fopen("data_pasien.txt", "w");
    if (!f) {
        printf("Gagal membuka file.\n");
        return;
    }
    fprintf(f, "ID|Nama|Gender|Umur|BB_Awal|BB_Akhir|HbA1C|Glukosa|Gejala\n");
    for (int i = 0; i < jumlah_pasien; i++) {
        pasien *p = &daftar_pasien[i];
        fprintf(f, "%s|%s|%s|%d|%.2f|%.2f|%.2f|%d|%d,%d,%d,%d,%d,%d,%d\n",
                p->id, p->nama, p->gender, p->umur,
                p->berat_badan_awal, p->berat_badan_akhir,
                p->HbA1C_pasien, p->glukosa_pasien,
                p->gejala_pasien.polidipsia, p->gejala_pasien.poliuria,
                p->gejala_pasien.diplopia, p->gejala_pasien.asthenia,
                p->gejala_pasien.ulkusKulit, p->gejala_pasien.paretesia,
                p->gejala_pasien.nausea);
    }
    fclose(f);
}

void muat_dari_file() {
    FILE *f = fopen("data_pasien.txt", "r");
    if (!f) return;

    jumlah_pasien = 0;
    char header[256];
    fgets(header, sizeof(header), f);
    while (!feof(f) && jumlah_pasien < MAKS_PASIEN) {
        pasien *p = &daftar_pasien[jumlah_pasien];
        int g[7];

        if (fscanf(f, "%[^|]|%[^|]|%[^|]|%d|%f|%f|%f|%d|%d,%d,%d,%d,%d,%d,%d\n",
            p->id, p->nama, p->gender, &p->umur,
            &p->berat_badan_awal, &p->berat_badan_akhir,
            &p->HbA1C_pasien, &p->glukosa_pasien,
            &g[0], &g[1], &g[2], &g[3], &g[4], &g[5], &g[6]) == 15) {

            p->gejala_pasien.polidipsia = g[0];
            p->gejala_pasien.poliuria = g[1];
            p->gejala_pasien.diplopia = g[2];
            p->gejala_pasien.asthenia = g[3];
            p->gejala_pasien.ulkusKulit = g[4];
            p->gejala_pasien.paretesia = g[5];
            p->gejala_pasien.nausea = g[6];

            jumlah_pasien++;
        }
    }
    fclose(f);
}

int cari_index_id(const char* id) {
    for (int i = 0; i < jumlah_pasien; i++) {
        if (strcmp(daftar_pasien[i].id, id) == 0)
            return i;
    }
    return -1;
}

void tampilkan_risiko(risiko r) {
    const char* str[] = { "Normal", "Rendah", "Sedang", "Tinggi", "Skor tidak valid!" };
    printf("%s", str[r]);
}

void tampilkan_tabel_pasien() {
    printf("\n%-10s | %-20s | %-10s | %-6s | %-10s\n", 
           "ID", "Nama", "Gender", "Umur", "Risiko");
    printf("---------------------------------------------------------------\n");
    
    for (int i = 0; i < jumlah_pasien; i++) {
        printf("%-10s | %-20s | %-10s | %-6d | ", 
               daftar_pasien[i].id,
               daftar_pasien[i].nama,
               daftar_pasien[i].gender,
               daftar_pasien[i].umur);
        tampilkan_risiko(total_skoring_pasien(&daftar_pasien[i]));
        printf("\n");
    }
}

void muat_id_terakhir_dari_file() {
    FILE *f = fopen("data_pasien.txt", "r");
    if (!f) return;

    char baris[256];
    int max_id = 0;

    fgets(baris, sizeof(baris), f);

    while (fgets(baris, sizeof(baris), f)) {
        int id_num;
        if (sscanf(baris, "PSN%4d", &id_num) == 1) {
            if (id_num > max_id) max_id = id_num;
        }
    }

    fclose(f);
    id_pasien_berikutnya = max_id + 1;
}

int main() {   
    int pilihan;
    char id_cari[10];
    muat_id_terakhir_dari_file();
    muat_dari_file();
    printf("Selamat datang di program DIASET!");

    do {
        printf("\n\nMenu:");
        printf("\n1. Tambah pasien");
        printf("\n2. Tampilkan data pasien");
        printf("\n3. Hapus pasien");
        printf("\n4. Keluar");
        printf("\n>> ");
        scanf("%d", &pilihan);
        getchar();

        if (pilihan == 1) {
            if (jumlah_pasien >= MAKS_PASIEN) {
                printf("Kapasitas penuh. Tidak dapat menambah pasien baru.\n");
                continue;
            }
            char* id_generated = buat_id_pasien();
            strncpy(daftar_pasien[jumlah_pasien].id, id_generated, sizeof(daftar_pasien[jumlah_pasien].id));
            free(id_generated);
            
            inputPasien(&daftar_pasien[jumlah_pasien]);

            printf("Rekap: %s | %s | %s | %d | Risiko: ",
                    daftar_pasien[jumlah_pasien].id,
                    daftar_pasien[jumlah_pasien].nama,
                    daftar_pasien[jumlah_pasien].gender,
                    daftar_pasien[jumlah_pasien].umur);
            tampilkan_risiko(total_skoring_pasien(&daftar_pasien[jumlah_pasien]));
            printf("\n");

            jumlah_pasien++;
            simpan_pasien_terakhir_ke_file();
        }

        else if (pilihan == 2) {
            int sub;
            printf("1. Tampilkan semua\n2. Cari berdasarkan ID\n>> ");
            scanf("%d", &sub);
            getchar();

            if (sub == 1) {
                printf("\n--- TAMPILKAN DATA PASIEN ---\n");
                tampilkan_tabel_pasien();
            } else if  (sub == 2) {
                printf("Masukkan ID: ");
                scanf("%s", id_cari);
                int idx = cari_index_id(id_cari);
                if (idx == -1) {
                    printf("ID tidak ditemukan.\n");
                } else {
                    pasien* p = &daftar_pasien[idx];
                    printf("\nID: %s\nNama: %s\nGender: %s\nUmur: %d\nBB: %.2f -> %.2f\nHbA1C: %.2f\nGlukosa: %d\n",
                           p->id, p->nama, p->gender, p->umur,
                           p->berat_badan_awal, p->berat_badan_akhir,
                           p->HbA1C_pasien, p->glukosa_pasien);
                    printf("Gejala (0-3): \nHaus: %d, BAK: %d, Kabur: %d, Lelah: %d, Luka: %d, Kesemutan: %d, Mual: %d\n",
                           p->gejala_pasien.polidipsia, p->gejala_pasien.poliuria, p->gejala_pasien.diplopia,
                           p->gejala_pasien.asthenia, p->gejala_pasien.ulkusKulit,
                           p->gejala_pasien.paretesia, p->gejala_pasien.nausea);

                    printf("Risiko: ");
                    tampilkan_risiko(total_skoring_pasien(p));
                    printf("\n");

                    char edit;
                    printf("Edit data? (y/n): ");
                    getchar();
                    scanf("%c", &edit);
                    getchar();
                    if (edit == 'y' || edit == 'Y') {
                        printf("Silakan input ulang data gejala dan lab:\n");
                        inputPasien(p);
                        simpan_semua_ke_file();
                    }
                } 
            } 
        }

        else if (pilihan == 3) {
            printf("Masukkan ID untuk dihapus: ");
            scanf("%s", id_cari);
            int idx = cari_index_id(id_cari);
            if (idx == -1) {
                printf("ID tidak ditemukan.\n");
            } else {
                for (int i = idx; i < jumlah_pasien - 1; i++)
                    daftar_pasien[i] = daftar_pasien[i + 1];
                jumlah_pasien--;
                printf("Data pasien berhasil dihapus.\n");
                simpan_semua_ke_file(); 
            }
        }

    } while (pilihan != 4);
    
    printf("Program berakhir!\n");
    printf("Terima kasih sudah menggunakan program DIASET.\n");
    return 0;
}