#ifndef LISTES_DOUBLEMENT_CHAINEES_NEURONES_H
#define LISTES_DOUBLEMENT_CHAINEES_NEURONES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listes_doublement_chainees_entiers.h"

// Définition du neurone et de son sucre syntaxique
typedef struct {
	List_int weights;
	int bias;
} Neuron_struct;

typedef Neuron_struct* Neuron;

// Définition d'un élément de la liste de neurones
typedef struct Element_neur {
	Neuron value;
	struct Element_neur* next;
	struct Element_neur* previous;
} Element_neur;

// Définition de la liste comme une structure avec les info ci dessous et de son sucre syntaxique
typedef struct {
	Element_neur* head;
	Element_neur* tail;
	int size;
} List_struct_neur;

typedef List_struct_neur* List_neur;

List_neur init_list_neur();
void delete_tail_neur(List_neur l);
void insert_tail_neur(List_neur l, Neuron value);
void print_list_neur(List_neur l);
void delete_head_neur(List_neur l);
void insert_head_neur(List_neur l, Neuron value);
bool is_empty_list_neur(List_neur l);
void delete_list_neur(List_neur l);
int len_list_neur(List_neur l);
Neuron get_element_at_given_pos_list_neur(List_neur l, int pos);

#endif