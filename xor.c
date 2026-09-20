#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

void xorEncryptDecrypt(char *message, char *key) {
    int keyLength = strlen(key);
    if (keyLength == 0){
	printf("Key cannot be empty");
	return;
    }
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % keyLength];
    }
}

int main() {
    char choice;
    printf("Do you want to encrypt or decrypt? (e/d): ");
    scanf("%c", &choice);

    while (getchar() != '\n');
    if (choice == 'e') {
        char plaintext[1000];
        char filename[50];
        char key[MAX_KEY_LENGTH];

        printf("Enter the string to encrypt: ");
        fgets(plaintext, sizeof(plaintext), stdin);
        plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline

        printf("Enter the filename to save the encrypted data: ");
        scanf("%s", filename);

        printf("Enter the key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        xorEncryptDecrypt(plaintext, key);
        fprintf(file, "%s\n", plaintext);
        fclose(file);
    } else if (choice == 'd') {
        char filename[50];
        char key[MAX_KEY_LENGTH];

        printf("Enter the filename to read the encrypted data: ");
        scanf("%s", filename);

        printf("Enter the key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        char buffer[1000];
        fgets(buffer, sizeof(buffer), file);
	buffer[strcspn(buffer, "\n")] = '\0';
        fclose(file);

        xorEncryptDecrypt(buffer, key);
        printf("Decrypted text: %s\n", buffer);
    } else {
        printf("Invalid choice. Please enter 'e' for encrypt or 'd' for decrypt.\n");
        return 1;
    }

    return 0;
}
