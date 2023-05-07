/*
file               : kamus.c
author             : Daniar Miftah Ramdhani (221511047)
                     Fadel Mohammad Fadhillah (221511048)
                     Mahesya Setia Nugraha (221511054)
program description: Program tugas besar mata kuliah Struktur Data dan Algoritma (praktik).
                     Program Kamus Translate Bahasa Indonesia - Inggris.                  
*/


#include "kamus.h"


//crud data management
void entry_data_to_file(infotype idn, infotype eng) {
    FILE *fp;
    fp = fopen("file.dat", "a+");
    int i;
   	change_to_lower(idn);
    change_to_lower(eng);
	
    if (fp == NULL) {
        printf("Error opening file\n");
    }else{
    	fprintf(fp, "%s %s\n", idn, eng);
    	fclose(fp);
	}
}

Node load_data_from_file(Node root, bool isAvl) {
    FILE *fp;
    infotype idn, eng;
    fp = fopen("file.dat", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        return NULL;
    }

    while (fscanf(fp, "%s %s", idn, eng) == 2) {
        root = entry_data_to_tree(root, idn, eng, isAvl);
    }

    fclose(fp);
    return root;
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

Node entry_data_to_tree(Node root, infotype idn, infotype eng, bool isAvl){
    if(root == NULL) {
        return create_node(idn, eng);
    }
    
    if (strcmp(idn, root->idn) < 0) {//idn < root->idn)
        root->left = entry_data_to_tree(root->left, idn, eng, isAvl);
    } else if (strcmp(idn, root->idn) > 0) {//idn > root->idn)
        root->right = entry_data_to_tree(root->right, idn, eng, isAvl);
    } else {
        return root;
    }
    
    root->height = 1 + max(get_height(root->left), get_height(root->right));
    int balance = get_balance(root);
    if(isAvl){
    	return rotate_management(balance, idn, root);
	}
	else{
		return root;
	}
}

Node Search(Node root, infotype idn){
	if(root == NULL){
		return NULL;
	}
	if(strcmp(idn, root->idn) < 0){
		return Search(root->left, idn);
	}else if(strcmp(idn, root->idn) > 0){
		return Search(root->right, idn);
	}else{
		return root;
	}

}


void entry_translate_to_linked_list(address *head, infotype eng) {
    address temp = *head;

    if (temp == NULL) {
        temp = (address) malloc(sizeof(ElmtList));
        strcpy(temp->eng, eng);
        temp->next = NULL;
        *head = temp;
        
    }else{
    	while (temp->next != NULL) {
        	temp = temp->next;
    	}
		 temp->next = (address) malloc(sizeof(ElmtList));
	    strcpy(temp->next->eng, eng);
	    temp->next->next = NULL;  
	}
	
    
}




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


Node right_rotate(Node y) {
//	printf("right rotate\n");
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
//	printf("left rotate\n");
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

void show_translate(address head) {
    address temp = head;
    int count = 0;

    // Menghitung jumlah node pada linked list
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    temp = head;
    while (temp != NULL) {
        printf("%s", temp->eng);

        // Jika terjemahan saat ini bukan merupakan terjemahan terakhir, tampilkan tanda koma
        if (count > 1) {
            printf(", ");
            count--;
        }

        temp = temp->next;
    }

    printf("\n");
}



void travesal_inorder(Node root) {
	
    if (root != NULL) {
    
        travesal_inorder(root->left);
        printf("%s %d ", root->idn, root->height);
        show_translate(root->translate);
        travesal_inorder(root->right);
    }
}

void print_tree(Node root, int level, int max_height) {
    int i;
    if (root == NULL) {
        return;
    }

    print_tree(root -> right, level + 1, max_height);

    for (i = 0; i < level - 1; i++) {
        printf("|       ");
    }

    if (level > 0) {
        printf("|-------");
    }

    if (root -> height == max_height) {
        printf("+");
        printf("--- %s  \n", root -> idn);
    } else {
        printf("-");
        printf("--- %s \n", root -> idn);
    }

    // Print the left subtree
    print_tree(root -> left, level + 1, max_height);
}



int calculate_max_height(Node root) {
    if (root == NULL) {
        return 0;
    } else {
        int left_height = calculate_max_height(root->left);
        int right_height = calculate_max_height(root->right);
        return 1 + (left_height > right_height ? left_height : right_height);
    }
}




void edit_kata(Node *root, Node tempId){
	address tempEn, temp;
	infotype english;
	int flag = -1;
	printf("\n%s ", tempId->idn);
	show_translate(tempId->translate);
	printf("Masukkan kata terjemahan yang akan di delete: ");
	scanf("%s", &english);
	change_to_lower(english);
	if (strcmp(tempId->translate->eng, english) == 0){
		//jika translate nya ada di head, maka pindahkan head nya ke next
		temp = tempId->translate;
		if (tempId->translate->next != NULL){
			tempId->translate = tempId->translate->next;
		}else{
			tempId->translate = NULL;
		}
		free(temp);
	//jika next translate tidak null, loop untuk mencari kata yang mau di delete
	}else if (tempId->translate->next != NULL){
		//loop dengan harus memegang item sebelum target untuk disambungkan ke next dari target delete
		tempEn = tempId->translate;
		while(tempEn != NULL){
			if (tempEn->next != NULL){
				if(strcmp(tempEn->next->eng, english) == 0){
					temp = tempEn->next;
					if (temp->next != NULL){
						tempEn->next = temp->next;
						temp->next = NULL;
						free(temp);
					}else{
						tempEn->next = NULL;
						free(temp);
					}
					flag = 0;
					break;
				}
			}
			tempEn = tempEn->next;
		}
		if (flag != 0){
			printf("\nKata yang dicari tidak ditemukan!\n");
			return;
		}
	}else{
		printf("\nKata yang dicari tidak ditemukan!\n");
		return;
	}
	printf("Masukkan Kata translate (pisahkan beberapa terjemahan dengan koma): ");
    scanf("%s", &english);
    change_to_lower(english);
    entry_translate_to_linked_list(&(tempId->translate), strtok(english, ","));
    char *token = strtok(NULL, ",");
    while (token != NULL) {
        entry_translate_to_linked_list(&(tempId->translate), token);
        token = strtok(NULL, ",");
    }
    printf("Berhasil Menambahkan Data ke Kamus\n");
	Delete(&*root, NULL);
}

void Delete(Node *root, Node target){
	//target adalah node kata yang akan di delete
	//traverse semua elemen tree, write kedalam file
	//jika elemen sama dengan target maka jangan write kedalam file
	FILE *fp;
	fp = fopen("file.dat", "w");
	if(fp==NULL){
		printf("Error opening file\n");
		return;
	}
	Node temp;
	Node stack[10] = {*root};
	int top=0;
	address tempEng;
	//algoritma traversing preorder binary tree tanpa rekursif (pake stack)
	while (top!=-1){
		temp = stack[top--];
		if (temp != target){
			char strId[25] = "", strEn[100] = ""; //strId untuk menampung idn, strEn untuk seluruh translate
			strcpy(strId,temp->idn); //copy idn dari elemen tree
			tempEng = temp->translate;
			//loop untuk translate
			while (tempEng != NULL){ //cek elemen translate saat ini
				strcat(strEn,tempEng->eng); //di concatenate dengan elemen translate sebelumnya
				strcat(strEn,",");//di concat juga dengan koma ',' agar format sama dengan cara insert
				tempEng = tempEng->next;
			}
			change_to_lower(strId);
			change_to_lower(strEn);
			fprintf(fp, "%s %s\n", strId, strEn); //write ke file
		}
		
		if (temp->left != NULL){
			stack[++top] = temp->left;
		}
		if (temp->right != NULL){
			stack[++top] = temp->right;
		}
	}
	fclose(fp);
	free(*root);
	*root = NULL;
	load_data_from_file(*root, true);
}


void translate_search(Node root, infotype idn){
	Node find;
	change_to_lower(idn);
	if(root == NULL){
		printf("Kamus Kosong. Tidak ada data yang tersedia!\n");
	}else{
		find = Search(root,idn);
		if(find != NULL){
			printf("Terjemahan: ");
			show_translate(find->translate);
		}else{
			printf("Kata tidak ditemukan.\n");
		}
	}
	
}

void change_to_lower(infotype word){
	int i;
	for (i= 0; i<=strlen(word); i++) {
	    word[i] = tolower(word[i]);
    }
}



