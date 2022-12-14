#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "get_json.h"

void print_json_object(json_t *element) {
    size_t size;
    const char *property;
    json_t *value;
	int i = 0;
    size = json_object_size(element);

    printf(" {\n");
    json_object_foreach(element, property, value) {
        printf("\t\"%s\" : ", property);
        print_json_type(value);
        if(i == size - 1)
			printf("\n");
		else 
			printf(",\n");
        i++;
    }
    printf(" }\n");
}

void print_json_array(json_t *element) {
    size_t i, size = json_array_size(element);

    printf(" [\n");
    for (i = 0; i < size; i++) {
		printf("\t\t");
        print_json_type(json_array_get(element, i));
        
		if(i == size - 1)
			printf("\n");
		else 
			printf(",\n");
    }
    printf("\t ]");
}

void print_json_string(json_t *element) {
    printf(" \"%s\"", json_string_value(element));
}

void print_json_integer(json_t *element) {
    printf(" %" JSON_INTEGER_FORMAT "", json_integer_value(element));
}

void print_json_real(json_t *element) {
    printf(" %f", json_real_value(element));
}

void print_json_boolean(bool element) {
    if (element == true)
		printf(" true");
	else
		printf(" false");
}

void print_json_null(json_t *element) {
    printf(" NULL");
}

void print_json_type(json_t *element) {
    switch (json_typeof(element)) {
        case JSON_OBJECT:
            print_json_object(element);
            break;
        case JSON_ARRAY:
            print_json_array(element);
            break;
        case JSON_STRING:
            print_json_string(element);
            break;
        case JSON_INTEGER:
            print_json_integer(element);
            break;
        case JSON_REAL:
            print_json_real(element);
            break;
        case JSON_TRUE:
            print_json_boolean(true);
            break;
        case JSON_FALSE:
            print_json_boolean(false);
            break;
        case JSON_NULL:
            print_json_null(element);
            break;
        default:
            fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
    }
}

void print_json(json_t *root) {
	printf("\n######\tJSON Response\t######\n\n");
	print_json_type(root);
	printf("\n\n");
}

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    fprintf(stderr, "not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}

json_t *load_json(const char *text) {
    json_t *root;
    json_error_t error;

    root = json_loads(text, 0, &error);

    if (root != NULL) {
        return root;
    } else {
        fprintf(stderr, "json error on line %d: %s\n", error.line, error.text);
        return (json_t *)0;
    }
}

json_t *http_get_json_data(const char *url) {
	struct MemoryStruct chunk;
 
	chunk.memory = malloc(1);
	chunk.size = 0;
	
	
	curl_global_init(CURL_GLOBAL_DEFAULT);

	CURL *curl = curl_easy_init();
	if (curl != NULL) {
		curl_easy_setopt(curl, CURLOPT_URL, url);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		CURLcode res = curl_easy_perform(curl);

		curl_easy_cleanup(curl);
		
		if (CURLE_OK != res) {
			fprintf(stderr, "curl told us %d\n", res);
		}
	}
	json_t *json = load_json(chunk.memory);
	free(chunk.memory);
	curl_global_cleanup();
	return json;
}


