#ifndef LISTES_DOUBLEMENT_CHAINEES_ENTIERS_H
#define LISTES_DOUBLEMENT_CHAINEES_ENTIERS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Définition d'un élément de la liste d'entiers
typedef struct Element_int {
	int value;
	struct Element_int* next;
	struct Element_int* previous;
} Element_int;

// Définition de la liste comme une structure avec les info ci dessous
typedef struct {
	Element_int* head;
	Element_int* tail;
	int size;
} List_struct_int;

// Sucre syntaxique pour un pointeur vers la structure qui 
// pointe vers le premier et le dernier élément 
typedef List_struct_int* List_int;

void delete_tail_int(List_int l);
List_int init_list_int();
void insert_tail_int(List_int l, int value);
void print_list_int(List_int l);
void insert_head_int(List_int l, int value);
void delete_head_int(List_int l);
bool is_empty_list_int(List_int l);
void delete_list_int(List_int l);
int len_list_int(List_int l);
int get_element_at_given_pos_list_int(List_int l, int pos);

#endif