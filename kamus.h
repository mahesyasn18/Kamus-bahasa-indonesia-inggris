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


//crud data management
void entry_data_to_file(infotype idn, infotype eng);
Node entry_data_to_tree(Node root, infotype idn, infotype eng, bool isAvl);
void entry_translate_to_linked_list(address *head, infotype eng);
Node load_data_from_file(Node root, bool isAvl);
void travesal_inorder(Node root);
void show_translate(address head);




//avl management
int get_height(Node node);
Node create_node(infotype idn, infotype eng);
int max(int leftNode, int rightNode);
int get_balance(Node node);
Node left_rotate(Node x);
Node right_rotate(Node y);
Node rotate_management(int balance, infotype idn, Node root);

Node Search(Node root, infotype idn);
void Delete(Node *root, Node target);
void edit_kata(Node *root, Node tempId);

void translate_search(Node root, infotype idn);

int calculate_max_height(Node root) ;
void print_tree(Node root, int level, int max_height);





