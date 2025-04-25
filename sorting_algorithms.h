#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <string.h>

/* ==================== Sorting untuk integer ==================== */

/*
 * Bubble Sort
 * Prinsip: Bandingkan elemen bersebelahan, tukar kalau urutan salah, ulangi hingga terurut.
 */
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

/*
 * Selection Sort
 * Prinsip: Pilih elemen terkecil di sisa array, tukar ke posisi depan.
 */
void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

/*
 * Insertion Sort
 * Prinsip: Ambil satu per satu elemen, sisipkan di bagian yang sudah terurut.
 */
void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

/*
 * Merge Sort
 * Prinsip: Bagi dua, rekursif urutkan masing-masing, lalu gabung (merge).
 */
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i=0, j=0, k=l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else             arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

/*
 * Quick Sort
 * Prinsip: Pilih pivot, partisi elemen lebih kecil dan lebih besar, lalu rekursif.
 */
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    return i + 1;
}
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

/*
 * Shell Sort
 * Prinsip: Seperti Insertion Sort, tapi mulai dengan gap besar, mengecil hingga 1.
 */
void shell_sort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

/* ==================== Sorting untuk kata (char*) ==================== */

void swap_words(char *arr[], int i, int j) {
    char *tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

/* Bubble Sort untuk kata */
void bubble_sort_words(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j], arr[j+1]) > 0)
                swap_words(arr, j, j+1);
}

/* Selection Sort untuk kata */
void selection_sort_words(char *arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (strcmp(arr[j], arr[min_idx]) < 0)
                min_idx = j;
        swap_words(arr, i, min_idx);
    }
}

/* Insertion Sort untuk kata */
void insertion_sort_words(char *arr[], int n) {
    for (int i = 1; i < n; i++) {
        char *key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

/* Merge Sort untuk kata */
void merge_words(char *arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    char **L = malloc(n1 * sizeof(char*));
    char **R = malloc(n2 * sizeof(char*));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i=0, j=0, k=l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) arr[k++] = L[i++];
        else                         arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}
void merge_sort_words(char *arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_words(arr, l, m);
        merge_sort_words(arr, m+1, r);
        merge_words(arr, l, m, r);
    }
}

/* Quick Sort untuk kata */
int partition_words(char *arr[], int low, int high) {
    char *pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swap_words(arr, i, j);
        }
    }
    swap_words(arr, i+1, high);
    return i + 1;
}
void quick_sort_words(char *arr[], int low, int high) {
    if (low < high) {
        int pi = partition_words(arr, low, high);
        quick_sort_words(arr, low, pi - 1);
        quick_sort_words(arr, pi + 1, high);
    }
}

/* Shell Sort untuk kata */
void shell_sort_words(char *arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            char *temp = arr[i];
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

#endif // SORTING_ALGORITHMS_H
