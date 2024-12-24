#ifndef FONCTIONS_NEURONES_H
#define FONCTIONS_NEURONES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "listes_doublement_chainees_entiers.h"
#include "listes_doublement_chainees_neurones.h"

// partie 1
Neuron init_neuron(int bias, int nb_weights, int* weights_tab);
int out_neuron(Neuron n, int nb_input, int* inputs_tab);

void release_neuron(Neuron n);
void print_neuron(Neuron n);
int size_neuron(Neuron n);

// partie 2
List_neur init_layer(int nb_neurones, int nb_input, int** weights, int* bias); // in progress
int* out_layer(List_neur layer, int nb_inputs, int* inputs);

void display_layer(List_neur l);
void release_layer(List_neur l);

#endif 