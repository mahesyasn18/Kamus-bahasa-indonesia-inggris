/*
file               : main.c
author             : Daniar Miftah Ramdhani (221511047)
                     Fadel Mohammad Fadhillah (221511048)
                     Mahesya Setia Nugraha (221511054)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Kamus Translate Bahasa Indonesia - Inggris.                  
*/



#include <stdio.h>
#include <stdlib.h>
#include "kamus.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int menu = 0;
	
    infotype indonesia, english;
    Node root = NULL, temp;
    address tempEn;
    do {
    	root = load_data_from_file(root);
        printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
        printf("1. Tambah Data\n");
        printf("2. Tampilkan Semua Data\n");
        printf("3. Translate Kata\n");
		printf("4. Delete Kata\n");
		printf("5. Edit Kata\n");
		printf("0. Exit\n");
		printf("Masukkan Pilihan Menu: ");
		scanf("%d", &menu);
		
		switch (menu) {
        case 1:
            do{
            	system("cls");
            	printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
            	printf("Masukkan kata dalam Bahasa Indonesia: ");
            	scanf("%s", &indonesia);
            	temp = Search(root, indonesia);
            	if(temp != NULL){
					printf("Kata ini sudah ada dalam kamus.\n");
					printf("Silakan masukkan kata yang lain.\n");
					system("pause");
				}
			}while(temp!=NULL);
            
            printf("Masukkan Kata translate(pisahkan beberapa terjemahan dengan koma): ");
            scanf("%s", &english);
            entry_data_to_file(indonesia, english);
            printf("\n==============================\n");
            printf("Berhasil Menambahkan Data ke Kamus\n");
            sleep(1);
            system("cls");
            break;
        case 2:
        	system("cls");
        	printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
            printf("Data Kamus\n");
            travesal_inorder(root);
			printf("\n");
			system("pause");
			system("cls");
            break;
        case 3:
        	system("cls");
        	printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
        	printf("Masukkan kata yang ingin dicari: ");
        	scanf("%s", &indonesia);
        	translate_search(root,indonesia);
        	system("pause");
        	system("cls");
        	break;
		case 4:
			//cari dulu kata yang pengen di delete, make modul search
			system("cls");
			printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
			printf("\nData Kamus\n");
            travesal_inorder(root);
            printf("\n==============================\n");
        	printf("Masukkan kata dalam Bahasa Indonesia yang akan dihapus: ");
        	scanf("%s", &indonesia);
        	printf("\n==============================\n");
        	temp = Search(root, indonesia);
        	if(temp == NULL){
				printf("Kata ini tidak terdaftar dalam kamus.\n");
				printf("Silakan masukkan kata yang lain.\n");
				system("pause");
				break;
			}else{
				//kalo katanya ada, jalanin modul Delete dengan temp sebagai target kata yang di delete
				Delete(&root, temp);
				
			}
			system("pause");
			system("cls");
            break;
		case 5:
			system("cls");
			printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
			printf("\nData Kamus\n");
            travesal_inorder(root);
            printf("\n==============================\n");
        	printf("Masukkan kata dalam Bahasa Indonesia: ");
        	scanf("%s", &indonesia);
        	printf("\n==============================\n");
        	temp = Search(root, indonesia);
        	if(temp == NULL){
				printf("Kata ini tidak terdaftar dalam kamus.\n");
				printf("Silakan masukkan kata yang lain.\n");
				system("pause");
				break;
			}else{
				system("cls");
				edit_kata(&root, temp);
				
			}
			system("pause");
			system("cls");
			break;
		case 0:
			printf("\nprogram selesai!");
			break;
        default:
            printf("Invalid input\n");
            break;
    }

	} while (menu != 0);

	return 0;
}

