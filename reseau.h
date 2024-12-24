#ifndef RESEAU_H
#define RESEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_neurones.h" // en "héritant" de ce fichier il hérite aussi des fichers des listes doublement chainées pour les entiers et les neurones

// Définition d'un élément de la liste de listes de neurones, il s'agit enfaite d'une des couches. Comme aucun type couche n'a été défini précédement, on utilisera ce nom
typedef struct Layer {
	List_neur value;
	struct Layer* next;
	struct Layer* previous;
} Layer;

// Définition de la liste de couches comme une structure avec les info ci dessous et de son sucre syntaxique
typedef struct {
	Layer* head;
	Layer* tail;
	int size;
} Layer_list;

typedef Layer_list* Network;

Network init_layer_list();
void delete_tail_net(Network n);
void insert_tail_net(Network n, List_neur value);
void print_network(Network n);
void delete_head_net(Network n);
void insert_head_net(Network n, List_neur value);
bool is_empty_net(Network n);
void delete_network(Network n);
int len_network(Network n);
List_neur get_element_at_given_pos_network(Network n, int pos);

// l'aboutissement de tout le projet !!!
int out_network(Network n, int* input_list, int nb_inputs);

#endif
