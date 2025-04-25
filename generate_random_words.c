#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_WORD_LEN 100

/*
 * Fungsi: random_word
 * -------------------
 * Mengisi 'word' dengan karakter acak [a–z] sepanjang 'length'.
 */
void random_word(char *word, int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length; i++) {
        int key = rand() % (int)(sizeof(charset) - 1);
        word[i] = charset[key];
    }
    word[length] = '\0';
}

/*
 * Fungsi: generate_random_words
 * -----------------------------
 * Menghasilkan file berisi kata acak (satu kata per baris).
 *
 * filename: nama file output (misal "data_kata.txt")
 * count:    jumlah kata
 * max_word_length: panjang maksimum tiap kata
 */
void generate_random_words(const char *filename, int count, int max_word_length) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File tidak dapat dibuka");
        return;
    }
    srand(time(NULL));
    char word[MAX_WORD_LEN];
    for (int i = 0; i < count; i++) {
        int length = (rand() % (max_word_length - 3)) + 3; // minimal 3 huruf
        random_word(word, length);
        fprintf(fp, "%s\n", word);
    }
    fclose(fp);
}

int main() {
    generate_random_words("data_kata.txt", 2000000, 20);
    return 0;
}
