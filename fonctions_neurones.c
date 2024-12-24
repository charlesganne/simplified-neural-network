#include "fonctions_neurones.h"

// partie 1

Neuron init_neuron(int bias, int nb_weights, int* weights_tab) {
	Neuron returned_neuron = (Neuron)malloc(sizeof(Neuron_struct));
	returned_neuron->bias = bias;
	List_int weights_list = init_list_int();
	returned_neuron->weights = weights_list;

    for (int i = 0; i < nb_weights; i++) {
        insert_tail_int(weights_list, weights_tab[i]);
    }

    return returned_neuron;
}

void print_neuron(Neuron n) {
	printf("Bias : %d\n", n->bias);
	printf("Weights : ");
	print_list_int(n->weights);
}

int size_neuron(Neuron n) {
	return len_list_int(n->weights);
}

int out_neuron(Neuron n, int nb_input, int* inputs_tab) {
	int min_size = (nb_input > size_neuron(n)) ? size_neuron(n) : nb_input;

	int x = 0;

	for (int i = 0; i < min_size; i++) {
		x+=inputs_tab[i]*get_element_at_given_pos_list_int(n->weights, i);
	}
	if (x >= n->bias) {
		return 1;
	} else {
		return 0;
	}
}

void release_neuron(Neuron n) {
	delete_list_int(n->weights);
	free(n->weights);
	free(n);
}

// partie 2
// Une couche sera représentée par une liste doublement chainée de neurones

List_neur init_layer(int nb_neurones, int nb_input, int** weights, int* bias) {
	List_neur layer=init_list_neur();
	for (int i = 0; i < nb_neurones; i++) {
		Neuron new_neur = init_neuron(bias[i], nb_input, weights[i]);
		insert_tail_neur(layer, new_neur);
	}

	return layer;
}

int* out_layer(List_neur layer, int nb_inputs, int* inputs) {
	int* out_tab = (int*)malloc(len_list_neur(layer) * sizeof(int));
	Element_neur* curent_element_neuron = layer->head;
	for (int i = 0; i < len_list_neur(layer); i++) {
		out_tab[i] = out_neuron(curent_element_neuron->value, nb_inputs, inputs);
		curent_element_neuron=curent_element_neuron->next;
	}
	return out_tab;
	// la taille de la liste retournée est la même que celle de la liste designant la couche
}

void display_layer(List_neur l) {
	Element_neur* n = l->head;
	for (int i = 0; i < len_list_neur(l); i++) {
		print_neuron(n->value);
		n = n->next;
	} 
}

void release_layer(List_neur l) {
	while (len_list_neur(l) > 0) {
		delete_head_neur(l);
	}
	free(l);
}