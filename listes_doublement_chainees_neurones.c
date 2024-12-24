#include "listes_doublement_chainees_neurones.h"

List_neur init_list_neur() {
	List_neur l = (List_neur)malloc(sizeof(List_struct_neur));
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	return l;
}

void delete_tail_neur(List_neur l) {
	if (l->size == 0) {
		printf("List already empty !\n");
	} else if (l->size == 1) {
		l->size = 0;
		delete_list_int(l->tail->value->weights);
		free(l->tail->value->weights);
		free(l->tail->value);
		free(l->tail);
		l->head = NULL;
		l->tail = NULL;
	} else if (l->size >= 2) {
		l->size --;
		Element_neur* new_last = l->tail->previous;
		l->tail->previous->next = NULL;
		delete_list_int(l->tail->value->weights);
		free(l->tail->value->weights);
		free(l->tail->value);
		free(l->tail);
		l->tail = new_last;
	}
}

void insert_tail_neur(List_neur l, Neuron value) {
	// value est un neurone déjà initialisé, alloué et valide
	Element_neur* new_last = (Element_neur*)malloc(sizeof(Element_neur));
	new_last->next = NULL;
	new_last->previous = l->tail;
	new_last->value = value;
	if (l->size == 0) {
		l->head = new_last;
	} else {
		l->tail->next = new_last;
	}
	l->tail = new_last;
	l->size++;
}

void print_list_neur(List_neur l) {
	Element_neur* sequence = l->head;
	printf("[\n\n");
	while (sequence != NULL) {
		// On recode la fonction print_neuron du fichier fonctions_neurones pour
		// ne pas l'inclure et éviter les dépendances circulaires
		printf("Bias : %d\n", sequence->value->bias);
		printf("Weights : ");
		print_list_int(sequence->value->weights);

		sequence = sequence->next;
		printf("\n");
	}
	printf("\n]\n");
}

void insert_head_neur(List_neur l, Neuron value) {
	Element_neur* new_first = (Element_neur*)malloc(sizeof(Element_neur));
	new_first->next = l->head;
	new_first->previous = NULL;
	new_first->value = value;
	if (l->size == 0) {
		l->tail = new_first;
	} else {
		l->head->previous = new_first;
	}
	l->head = new_first;
	l->size++;
}

void delete_head_neur(List_neur l) {
	if (l->size == 0) {
		printf("List already empty !\n");
	} else if (l->size == 1) {
		l->size = 0;
		delete_list_int(l->head->value->weights);
		free(l->head->value->weights);
		free(l->head->value);
		free(l->head);
		l->head = NULL;
		l->tail = NULL;
	} else if (l->size >= 2) {
		l->size--;
		Element_neur* new_first = l->head->next;
		l->head->next->previous = NULL;
		delete_list_int(l->head->value->weights);
		free(l->head->value->weights);
		free(l->head->value);
		free(l->head);
		l->head = new_first;
	}
}

bool is_empty_list_neur(List_neur l) {
	return l->size == 0;
}

void delete_list_neur(List_neur l) {
	// On fait ici le choix de ne pas liberer la structure 
	// d'entete qui contient les pointeurs, au cas où elle serait
	// reutilisée ensuite
	while (!is_empty_list_neur(l)) {
		delete_head_neur(l);
	}
}

int len_list_neur(List_neur l) {
	return l->size;
}

Neuron get_element_at_given_pos_list_neur(List_neur l, int pos) {
	if (pos < 0 || pos >= len_list_neur(l)) {
		printf("index out of range !!!!!!!!\n");
		return NULL;
	}
	Element_neur* current_pos = l->head;
	while (pos != 0) {
		current_pos = current_pos->next;
		pos--;
	}
	return current_pos->value;
}