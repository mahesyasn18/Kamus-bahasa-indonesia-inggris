/*
file               : kamus.c
author             : Daniar Miftah Ramdhani (221511047)
                     Fadel Mohammad Fadhillah (221511048)
                     Mahesya Setia Nugraha (221511054)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Kamus Translate Bahasa Indonesia - Inggris.                  
*/


#include "kamus.h"

void entryDatatoFile(infotype idn, infotype eng) {
    FILE *fp;
    fp = fopen("file.dat", "a+");
	
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(fp, "%s %s\n", idn, eng);
    fclose(fp);
}



