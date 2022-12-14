#include <curl/curl.h>
#include <jansson.h>
#include <stdbool.h>

struct MemoryStruct {
  char *memory;
  size_t size;
};

void print_json_object(json_t *element);

void print_json_array(json_t *element);

void print_json_string(json_t *element);

void print_json_integer(json_t *element);

void print_json_real(json_t *element);

void print_json_boolean(bool element);

void print_json_null(json_t *element);

void print_json_type(json_t *element);

void print_json(json_t *root);

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp);

json_t *load_json(const char *text);

json_t *http_get_json_data(const char *url);
