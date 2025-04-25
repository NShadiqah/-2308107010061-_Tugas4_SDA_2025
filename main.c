#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include "sorting_algorithms.h"

#pragma comment(lib, "psapi.lib") // Untuk MSVC, abaikan jika pakai MinGW

#define MAX_WORD_LEN 100
#define MAX_ALGO 6

typedef struct {
    char name[20];
    double time_ms;
    SIZE_T memory_kb;
} BenchmarkResult;

int sizes[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
int total_sizes = sizeof(sizes) / sizeof(sizes[0]);

SIZE_T get_memory_usage_kb() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.PeakWorkingSetSize / 1024;
    }
    return 0;
}

void read_numbers(const char *filename, int **arr, int *n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("File tidak dapat dibuka"); exit(1); }
    int capacity = 1024, size = 0;
    int *data = malloc(capacity * sizeof(int));
    while (fscanf(fp, "%d", &data[size]) == 1) {
        size++;
        if (size >= capacity) {
            capacity *= 2;
            data = realloc(data, capacity * sizeof(int));
        }
    }
    fclose(fp);
    *arr = data; *n = size;
}

void read_words(const char *filename, char ***arr, int *n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("File tidak dapat dibuka"); exit(1); }
    int capacity = 1024, size = 0;
    char **data = malloc(capacity * sizeof(char*));
    char buffer[MAX_WORD_LEN+1];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (size >= capacity) {
            capacity *= 2;
            data = realloc(data, capacity * sizeof(char*));
        }
        data[size] = malloc(strlen(buffer) + 1);
        strcpy(data[size], buffer);
        size++;
    }
    fclose(fp);
    *arr = data; *n = size;
}

void benchmark_angka(int *data, int total_n) {
    int *tmp = malloc(total_n * sizeof(int));

    struct {
        char name[20];
        void (*func)(int *, int);
    } algos[] = {
        {"Bubble Sort", bubble_sort},
        {"Selection Sort", selection_sort},
        {"Insertion Sort", insertion_sort},
        {"Merge Sort", NULL},
        {"Quick Sort", NULL},
        {"Shell Sort", shell_sort}
    };

    for (int s = 0; s < total_sizes; s++) {
        int n = sizes[s];
        if (n > total_n) break;

        printf("\n=== Benchmark Data Angka (%d data) ===\n", n);
        printf("%-20s | %-15s | %-15s\n", "Algoritma", "Waktu (ms)", "Memori (KB)");
        printf("------------------------------------------------------------\n");

        for (int i = 0; i < MAX_ALGO; i++) {
            memcpy(tmp, data, n * sizeof(int));
            SIZE_T mem_before = get_memory_usage_kb();
            clock_t start = clock();

            if (algos[i].func) {
                algos[i].func(tmp, n);
            } else if (strcmp(algos[i].name, "Merge Sort") == 0) {
                merge_sort(tmp, 0, n - 1);
            } else if (strcmp(algos[i].name, "Quick Sort") == 0) {
                quick_sort(tmp, 0, n - 1);
            }

            clock_t end = clock();
            SIZE_T mem_after = get_memory_usage_kb();
            double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000;

            printf("%-20s | %-15.2f | %-15llu\n", algos[i].name, elapsed, (unsigned long long)(mem_after - mem_before));
        }
    }

    free(tmp);
}

void benchmark_kata(char **data, int total_n) {
    char **tmp = malloc(total_n * sizeof(char*));

    struct {
        char name[20];
        void (*func)(char **, int);
    } algos[] = {
        {"Bubble Sort", bubble_sort_words},
        {"Selection Sort", selection_sort_words},
        {"Insertion Sort", insertion_sort_words},
        {"Merge Sort", NULL},
        {"Quick Sort", NULL},
        {"Shell Sort", shell_sort_words}
    };

    for (int s = 0; s < total_sizes; s++) {
        int n = sizes[s];
        if (n > total_n) break;

        printf("\n=== Benchmark Data Kata (%d data) ===\n", n);
        printf("%-20s | %-15s | %-15s\n", "Algoritma", "Waktu (ms)", "Memori (KB)");
        printf("------------------------------------------------------------\n");

        for (int i = 0; i < MAX_ALGO; i++) {
            memcpy(tmp, data, n * sizeof(char*));
            SIZE_T mem_before = get_memory_usage_kb();
            clock_t start = clock();

            if (algos[i].func) {
                algos[i].func(tmp, n);
            } else if (strcmp(algos[i].name, "Merge Sort") == 0) {
                merge_sort_words(tmp, 0, n - 1);
            } else if (strcmp(algos[i].name, "Quick Sort") == 0) {
                quick_sort_words(tmp, 0, n - 1);
            }

            clock_t end = clock();
            SIZE_T mem_after = get_memory_usage_kb();
            double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000;

            printf("%-20s | %-15.2f | %-15llu\n", algos[i].name, elapsed, (unsigned long long)(mem_after - mem_before));
        }
    }

    free(tmp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <angka|kata> <filename>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "angka") == 0) {
        int *nums, n;
        read_numbers(argv[2], &nums, &n);
        benchmark_angka(nums, n);
        free(nums);
    } else if (strcmp(argv[1], "kata") == 0) {
        char **words; int n;
        read_words(argv[2], &words, &n);
        benchmark_kata(words, n);
        for (int i = 0; i < n; i++) free(words[i]);
        free(words);
    } else {
        printf("Mode tidak dikenali. Gunakan 'angka' atau 'kata'.\n");
    }

    return 0;
}
