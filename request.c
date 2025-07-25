#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 4096

typedef struct {
    char *data;
    size_t size;
} MemoryBuffer;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    MemoryBuffer *mem = (MemoryBuffer *)userdata;

    if (mem->size + total_size >= BUFFER_SIZE - 1) total_size = BUFFER_SIZE - mem->size - 1;

    memcpy(mem->data + mem->size, ptr, total_size);
    mem->size += total_size;
    mem->data[mem->size] = '\0';  // null-terminate

    return total_size;
}

int main() {
    CURL *curl;
    CURLcode res;

    MemoryBuffer mem = {
        .data = calloc(BUFFER_SIZE, 1),
        .size = 0
    };

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
        //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "accept : application/json");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mem);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Failed to init curl\n");
    }

    write(STDOUT_FILENO, mem.data, mem.size);
    free(mem.data);

    return 0;
}
