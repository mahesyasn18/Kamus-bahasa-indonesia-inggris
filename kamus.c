/*
file               : kamus.c
author             : Daniar Miftah Ramdhani (221511047)
                     Fadel Mohammad Fadhillah (221511048)
                     Mahesya Setia Nugraha (221511054)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Kamus Translate Bahasa Indonesia - Inggris.                  
*/


#include "kamus.h"

//Avl Management
int max(int leftNode, int rightNode) {
    return (leftNode > rightNode) ? leftNode : rightNode;
}

int get_height(Node node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int get_balance(Node node) {
    if (node == NULL)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

Node create_node(infotype idn, infotype eng) {
    Node new_node = (Node)malloc(sizeof(BTnode));
    strcpy(new_node->idn, idn);
    new_node->height = 1;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->translate = NULL;
    entry_translate_to_linked_list(&(new_node->translate), strtok(eng, ","));
    char *token = strtok(NULL, ",");
    while (token != NULL) {
        entry_translate_to_linked_list(&(new_node->translate), token);
        token = strtok(NULL, ",");
    }
    return new_node;
}

Node right_rotate(Node y) {
	printf("right rotate\n");
    Node temp1 = y->left;
    Node temp2 = temp1->right;
    temp1->right = y;
    
    if (temp2 != NULL) {
        y->left = temp2;
    } else {
        y->left = NULL;
    }
 
    y->height = max(get_height(y->left), get_height(y->right)) + 1;
    temp1->height = max(get_height(temp1->left), get_height(temp1->right)) + 1;
    return temp1;
}

Node left_rotate(Node x) {
	printf("left rotate\n");
    Node temp1 = x->right;
    Node temp2 = temp1->left;
    temp1->left = x;
    
    if (temp2 != NULL) {
        x->right = temp2;
    } else {
        x->right = NULL;
    }
 
    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    temp1->height = max(get_height(temp1->left), get_height(temp1->right)) + 1;
 
    return temp1;
}

Node rotate_management(int balance, infotype idn, Node root){
	if (balance > 1 && (strcmp(idn, root->left->idn) < 0)) {
        return right_rotate(root);
    }
 
    if (balance < -1 && (strcmp(idn, root->right->idn) > 0)) {
        return left_rotate(root);
    }
 
    if (balance > 1 && (strcmp(idn, root->left->idn) > 0)) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }
 
    if (balance < -1 && (strcmp(idn, root->right->idn) < 0)) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }
    
    return root;
}




//crud data management
void entry_data_to_file(infotype idn, infotype eng) {
    FILE *fp;
    fp = fopen("file.dat", "a+");
	
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(fp, "%s %s\n", idn, eng);
    fclose(fp);
}

Node entry_data_to_tree(Node root, infotype idn, infotype eng){
    Node parent = NULL;
    Node current = root;
    if(root==NULL){
    	return create_node(idn, eng);
	}
	
	if (strcmp(idn, root->idn) < 0) {//idn < root->idn)
        root->left = entry_data_to_tree(root->left, idn, eng);
    } else if (strcmp(idn, root->idn) > 0) {//idn > root->idn)
        root->right = entry_data_to_tree(root->right, idn, eng);
    } else {
        return root;
    }
    
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);
    
    return rotate_management(balance, idn, root);
    
    return root;
}

void entry_translate_to_linked_list(address *head, infotype eng) {
    address temp = *head;

    if (temp == NULL) {
        temp = (address) malloc(sizeof(ElmtList));
        strcpy(temp->eng, eng);
        temp->next = NULL;
        *head = temp;
        return;
    }
	
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = (address) malloc(sizeof(ElmtList));
    strcpy(temp->next->eng, eng);
    temp->next->next = NULL;
}

Node load_data_from_file(Node root) {
    FILE *fp;
    fp = fopen("file.dat", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    infotype idn, eng;
    while (fscanf(fp, "%s %s", idn, eng) == 2) {
        root = entry_data_to_tree(root, idn, eng);
    }

    fclose(fp);
    return root;
}


void show_translate(address head) {
    address temp = head;

    while (temp != NULL) {
        printf("%s ", temp->eng);
        temp = temp->next;
    }

    printf("\n");
}



void travesal_inorder(Node root) {
    if (root != NULL) {
        travesal_inorder(root->left);
        printf("%s:  %d ", root->idn, root->height);
        show_translate(root->translate);
        travesal_inorder(root->right);
    }
}




