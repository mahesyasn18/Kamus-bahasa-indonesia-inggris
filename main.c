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

int main(int argc, char *argv[]){
	int menu = 0, pilih = 0;
	
    infotype indonesia, english;
    Node root = NULL, temp, rootBalance = NULL;
    address tempEn;
    do {
    	if(rootBalance!=NULL){
        	root = rootBalance;
        	rootBalance = NULL;
		}else{
			root = load_data_from_file(root, false);
		}
        printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
        printf("Lakukan Balancing Terlebih dahulu untuk pertama kali load data dan untuk setiap terdapat perubahan data\n");
		printf("1. Tambah Data\n");
        printf("2. Tampilkan Semua Data\n");
        printf("3. Translate Kata\n");
		printf("4. Delete Kata\n");
		printf("5. Edit Kata\n");
		printf("6. Balancing\n");
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
            int max_height = max(get_height(root->left), get_height(root->right))+1;
    		print_tree(root, 1, max_height);
            printf("##############\n");
            printf("Travesal Inorder\n");
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
            printf("1. Delete kata Indonesia\n");
            printf("2. Delete kata Inggris\n");
            printf("Masukkan Pilihan Menu: ");
			scanf("%d", &pilih);
			system("cls");
			printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
			printf("\nData Kamus\n");
            travesal_inorder(root);
            printf("\n==============================\n");
        	printf("Masukkan kata dalam Bahasa Indonesia yang akan dihapus: ");
        	scanf("%s", &indonesia);
        	printf("\n==============================\n");
        	change_to_lower(indonesia);
        	temp = Search(root, indonesia);
        	if(temp == NULL){
				printf("Kata ini tidak terdaftar dalam kamus.\n");
				printf("Silakan masukkan kata yang lain.\n");
				system("pause");
				system("cls");
				break;
			}
			if (pilih == 1){
				//kalo katanya ada, jalanin modul Delete dengan temp sebagai target kata yang di delete
				printf("Data Kamus '%s' Berhasil Dihapus!\n", temp->idn);
				Delete(&root, temp);
			}else{
				system("cls");
				printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
				printf("\n%s ", temp->idn);
				show_translate(temp->translate);
				printf("Masukkan kata terjemahan yang akan di delete: ");
				scanf("%s", &english);
				change_to_lower(english);
				if (delete_kata_inggris(&(temp->translate), english) == 1) {
					printf("\nKata yang dicari tidak ditemukan!\n");
				}else{
					printf("\nKata terjemahan '%s' berhasil dihapus!\n", english);
					Delete(&root, NULL);
				}
			}
			system("pause");
			system("cls");
            break;
		case 5:
			system("cls");
			printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
            printf("1. Edit kata Indonesia\n");
            printf("2. Edit kata Inggris\n");
            printf("Masukkan Pilihan Menu: ");
			scanf("%d", &pilih);
			system("cls");
			printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
			printf("\nData Kamus\n");
            travesal_inorder(root);
            printf("\n==============================\n");
        	printf("Masukkan kata dalam Bahasa Indonesia: ");
        	scanf("%s", &indonesia);
        	printf("\n==============================\n");
        	change_to_lower(indonesia);
        	temp = Search(root, indonesia);
        	if(temp == NULL){
				printf("Kata ini tidak terdaftar dalam kamus.\n");
				printf("Silakan masukkan kata yang lain.\n");
				system("pause");
				system("cls");
				break;
			}
			if (pilih == 1){
				edit_kata_indonesia(&root, temp);
			}else{
				edit_kata_inggris(&root, temp);
			}
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			printf("==============================\n-- Kamus Indonesia - Inggris--\n==============================\n");
			printf("\nData Kamus Sebelum Balancing\n");
			print_tree(root, 1, max_height);
            printf("################\n");
            printf("Travesal Inorder\n");
            travesal_inorder(root);
			printf("\nData Kamus Sesudah Balancing\n");
			rootBalance = load_data_from_file(rootBalance, true);
			print_tree(rootBalance, 1, max_height);
            printf("################\n");
            printf("Travesal Inorder\n");
            travesal_inorder(rootBalance);
			system("pause");
			system("cls");
		case 0:
			break;
        default:
            printf("Invalid input\n");
            break;
    }

	} while (menu != 0);
	printf("\nprogram selesai!");
	return 0;
}

