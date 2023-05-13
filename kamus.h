/*
file               : kamus.h
author             : Daniar Miftah Ramdhani (221511047)
                     Fadel Mohammad Fadhillah (221511048)
                     Mahesya Setia Nugraha (221511054)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Kamus Translate Bahasa Indonesia - Inggris.                  
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define True 1
#define False 0
#define boolean unsigned char

typedef char infotype[40];
typedef struct BTNode *Node;

typedef struct tElmtList *address;
typedef struct tElmtList {
	 infotype eng;
	 address  next;
} ElmtList;
typedef struct BTNode{
	infotype idn;
	Node left,right;
	address translate;
	int height;
} BTnode;



void entry_data_to_file(infotype idn, infotype eng);
Node load_data_from_file(Node root, bool isAvl);


Node create_node(infotype idn, infotype eng);
Node entry_data_to_tree(Node root, infotype idn, infotype eng, bool isAvl);
Node Search(Node root, infotype idn);
void entry_translate_to_linked_list(address *head, infotype eng);


int max_height(int leftNode, int rightNode);
int get_height(Node node);
int get_balance(Node node);
Node left_rotate(Node node);
Node right_rotate(Node node);
Node rotate_management(int balance, infotype idn, Node root);


void show_translate(address head);
void travesal_inorder(Node root);


void Delete(Node *root, Node target);
void edit_kata_inggris(Node *root, Node tempId);
void edit_kata_indonesia(Node *root, Node tempId);
int delete_kata_inggris(address *head, infotype en);
void gotoxy(int x, int y);
void getCurrentCursorPosition(int *row, int *col);

void translate_search(Node root, infotype idn);

void print_tree(Node root, int level, int max_height);
void change_to_lower(infotype word);





