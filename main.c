#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 100000  // Adjust this size based on the actual dictionary size
#define WORD_LENGTH 50

char current_combination[8] = {};  // To handle combinations up to 7 letters
char letterArr[7] = {};
char *dictionary[DICTIONARY_SIZE] = {0};  // Array to store dictionary words
char mandatory_letter;

// Function to load the dictionary from a file
void load_dictionary(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open dictionary file");
        exit(EXIT_FAILURE);
    }

    char buffer[WORD_LENGTH];
    int index = 0;
    while (fgets(buffer, WORD_LENGTH, file) && index < DICTIONARY_SIZE) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove the newline character
        dictionary[index] = strdup(buffer);
        if (!dictionary[index]) {
            perror("Failed to duplicate string");
            exit(EXIT_FAILURE);
        }
        index++;
    }

    fclose(file);
}

// Function to check if a word exists in the dictionary
int is_word_in_dictionary(const char *word) {
    for (int i = 0; i < DICTIONARY_SIZE && dictionary[i]; i++) {
        if (strcmp(dictionary[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

// Recursive function to generate combinations
void generate_combinations(char *letters, char *current_combination, int depth, int max_depth, int letter_count, char mandatory_letter) {
    if (depth == max_depth) {
        current_combination[max_depth] = '\0';  // Null-terminate the current combination
        if (strchr(current_combination, mandatory_letter) != NULL && is_word_in_dictionary(current_combination)) {
            printf("%s\n", current_combination);
        }
        return;
    }

    for (int i = 0; i < letter_count; i++) {
        current_combination[depth] = letters[i];
        generate_combinations(letters, current_combination, depth + 1, max_depth, letter_count, mandatory_letter);
    }
}

int main() {
    load_dictionary("dictionary.txt");  // Load the dictionary from a file

    printf("Enter the mandatory letter: ");
    scanf(" %c", &mandatory_letter);
    letterArr[0] = mandatory_letter;
    for (int i = 1; i < 7; i++) {
        printf("Enter letter num %d: ", i + 1);
        scanf(" %c", &letterArr[i]);
    }

    printf("\nYour array: \n");
    for (int i = 0; i < 7; i++) {
        printf("%c ", letterArr[i]);
    }
    printf("\n");

    // Generate combinations for lengths 4, 5, 6, and 7
    for (int i = 4; i <= 7; i++) {
        printf("\n------------ %d letter words ------------\n", i);

        int combination_length = i;  // Desired combination length
        int letter_count = sizeof(letterArr) / sizeof(letterArr[0]);
        generate_combinations(letterArr, current_combination, 0, combination_length, letter_count, mandatory_letter);
    }

    // Free dictionary memory
    for (int i = 0; i < DICTIONARY_SIZE && dictionary[i]; i++) {
        free(dictionary[i]);
    }

    return 0;
}