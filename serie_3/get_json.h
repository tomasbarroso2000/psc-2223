#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

void print_json_indent(int indent);

const char *json_plural(size_t count);

void print_json_object(json_t *element, int indent);

void print_json_array(json_t *element, int indent);

void print_json_string(json_t *element, int indent);

void print_json_integer(json_t *element, int indent);

void print_json_real(json_t *element, int indent);

void print_json_true(json_t *element, int indent);

void print_json_false(json_t *element, int indent);

void print_json_null(json_t *element, int indent);

/*-----------------------------------*/

void print_json_aux(json_t *element, int indent);
