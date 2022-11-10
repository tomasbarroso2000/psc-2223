/*
int compare_data_value ( Dataset *set1, Dataset *set2, unsigned index ) {
	if (index >= set1->length || index >= set2->length
		|| NULL == set1->data[index] || NULL == set2->data[index])
		return -1;
	return set1->data[index]->value == set2->data[index]->value;
}
*/

	.text
	.global	compare_data_value
compare_data_value:

	ret

	.section .note.GNU-stack
