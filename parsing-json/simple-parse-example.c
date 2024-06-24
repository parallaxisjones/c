// donut.c
#include <stdio.h>
#include <jansson.h>

int main() {
    // Creating a JSON object
    json_t *object = json_object();
    json_object_set_new(object, "name", json_string("Candlehopper"));
    json_object_set_new(object, "level", json_integer(5));
    json_object_set_new(object, "score", json_integer(12345));

    // Serialize JSON object to string
    char *json_str = json_dumps(object, JSON_INDENT(2));
    if (!json_str) {
        fprintf(stderr, "Error serializing JSON object.\n");
        return 1;
    }
    printf("Serialized JSON:\n%s\n", json_str);

    // Free the serialized string
    free(json_str);

    // JSON string to parse
    const char *json_input = "{\"name\": \"Candlehopper\", \"level\": 5, \"score\": 12345}";

    // Parse JSON string
    json_error_t error;
    json_t *parsed_object = json_loads(json_input, 0, &error);
    if (!parsed_object) {
        fprintf(stderr, "Error parsing JSON string: %s\n", error.text);
        return 1;
    }

    // Extract values
    json_t *name = json_object_get(parsed_object, "name");
    json_t *level = json_object_get(parsed_object, "level");
    json_t *score = json_object_get(parsed_object, "score");

    if (json_is_string(name) && json_is_integer(level) && json_is_integer(score)) {
        printf("Parsed JSON:\n");
        printf("name: %s\n", json_string_value(name));
        printf("level: %lld\n", json_integer_value(level));
        printf("score: %lld\n", json_integer_value(score));
    } else {
        fprintf(stderr, "Error extracting values from JSON object.\n");
        json_decref(parsed_object);
        return 1;
    }

    // Decrement reference counts to free memory
    json_decref(object);
    json_decref(parsed_object);

    return 0;
}
