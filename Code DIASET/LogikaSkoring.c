#include <stdio.h>
#include <string.h>
#include "Input.c"

typedef enum {
    normal,
    rendah,
    sedang,
    tinggi,
    skor_tidak_valid
} risiko;

void hitung_berat_badan(float berat_badan_akhir, float berat_badan_awal, int *skorBB) {
    float selisih = berat_badan_akhir - berat_badan_awal;
    float persen = (selisih / berat_badan_awal) * 100;

    if (persen < 2) {
        *skorBB = 0;
    } else if (persen < 5) {
        *skorBB = 1;
    } else if (persen <= 10) {
        *skorBB = 2;
    } else {
        *skorBB = 3;
    }
}

void hitung_HbA1c(float persen_HbA1C, int *skorHb) {
    if (persen_HbA1C < 5.7) {
        *skorHb = 0;
    } else if (persen_HbA1C <= 6.4) {
        *skorHb = 1;
    } else if (persen_HbA1C <= 7.5) {
        *skorHb = 2;
    } else if (persen_HbA1C <= 9) {
        *skorHb = 3;
    } else {
        *skorHb = 4;
    }
}

void hitung_glukosa(int nilai_glukosa, int *skorGlukosa) {
    if (nilai_glukosa < 100) {
        *skorGlukosa = 0;
    } else if (nilai_glukosa < 125) {
        *skorGlukosa = 1;
    } else {
        *skorGlukosa = 2;
    }
}

void hitung_umur(int umur, int *skorUmur) {
    if (umur < 35) {
        *skorUmur = 0;
    } else if (umur <= 44) {
        *skorUmur = 1;
    } else if (umur <= 54) {
        *skorUmur = 2;
    } else if (umur <= 64) {
        *skorUmur = 3;
    } else {
        *skorUmur = 4;
    }
}

int hitung_gejala(gejala *g) {
    int skor = 0;

    if (g->polidipsia == 3 ) skor += 2;
    else skor += g->polidipsia;

    if (g->poliuria == 3) skor += 2;
    else skor += g->poliuria;

    if (g->diplopia == 0 || g->diplopia == 1) skor += 0;
    else if (g->diplopia == 2) skor += 1;
    else if (g->diplopia == 3) skor += 2;

    if (g->asthenia <= 1) skor += 0;
    else skor += 1;

    if (g->ulkusKulit == 3) skor += 2;
    else skor += g->ulkusKulit;

    if (g->paretesia == 3) skor += 2;
    else skor += g->paretesia;

    if (g->nausea == 0 || g->nausea == 1) skor += 0;
    else if (g->nausea == 2) skor += 1;
    else if (g->nausea == 3) skor += 2;

    return skor;
}


risiko total_skoring (int skorBB, int skorGlukosa, int skorHb, int skorUmur, int total_sum_gejala) {
    int skorLab = skorGlukosa + skorHb ;
    float total_skor = ( (float)total_sum_gejala / 13 * 30 ) + ((float)skorBB / 3 * 15) + ((float)skorUmur / 4 * 10) + ((float)skorLab / 6 * 45); 
    
    risiko hasil;

    if (total_skor <= 25) {
        hasil = normal;
    } else if (total_skor <= 50) {
        hasil = rendah;
    } else if (total_skor <= 75) {
        hasil = sedang;
    } else if (total_skor <= 100) {
        hasil = tinggi;
    } else {
        printf("Skor tidak valid!");
        return 0;
    }
    
    return hasil;
}

risiko total_skoring_pasien(pasien *p) {
    int skorBB, skorHb, skorGlukosa, skorUmur, totalGejala;

    hitung_berat_badan(p->berat_badan_akhir, p->berat_badan_awal, &skorBB);
    hitung_HbA1c(p->HbA1C_pasien, &skorHb);
    hitung_glukosa(p->glukosa_pasien, &skorGlukosa);
    hitung_umur(p->umur, &skorUmur);
    totalGejala = hitung_gejala(&p->gejala_pasien);

    return total_skoring(skorBB, skorGlukosa, skorHb, skorUmur, totalGejala);
}