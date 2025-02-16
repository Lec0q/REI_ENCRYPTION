#include <stdio.h>
#include <string.h>
#define PLAINTEXT_SIZE 1000  
#define CYPHERTEXT_SIZE 1000
#define KEY128_SIZE 17      // 16 characters + null (128-bit)
#define KEY192_SIZE 25      // 24 characters + null (192-bit)
#define KEY256_SIZE 33      // 32 characters + null (256-bit)

void toBinary(unsigned int n, int bits);
void user_input(char PlainText[PLAINTEXT_SIZE], char key_128[KEY128_SIZE], char Key_192[KEY192_SIZE], char Key_256[KEY256_SIZE],
                int *plainText_length, int *key_bits_size_option);
void XOR_operation(const char *PlainText, const char *Key, int Plain_length, int Key_length, char *CypherText);
void reverse_XOR_operation(const char *CypherText, const char *Key, int CypherText_length, int Key_length, char *RecoveredPlainText);

void toBinary(unsigned int n, int bits) {
    for (int i = bits - 1; i >= 0; i--)
        printf("%d", (n >> i) & 1);
    printf("\n");
}

void user_input(char PlainText[PLAINTEXT_SIZE], char key_128[KEY128_SIZE], char Key_192[KEY192_SIZE], char Key_256[KEY256_SIZE],
                int *plainText_length, int *key_bits_size_option) {
    printf("Welcome to REI Encryption \n");
    printf("Please choose the encryption key size: \n");
    printf("1. 128 bits (16 characters)\n");
    printf("2. 192 bits (24 characters)\n");
    printf("3. 256 bits (32 characters)\n -> ");
    int choice;
    scanf("%d", &choice);
    getchar();
    *key_bits_size_option = choice;
    if (choice < 1 || choice > 3) {
        fprintf(stderr, "Invalid choice. Please try again.\n");
        *key_bits_size_option = -1;
        return;
    }
    printf("Please enter the plain text: \n");
    fgets(PlainText, PLAINTEXT_SIZE, stdin);
    *plainText_length = strlen(PlainText);
    if (*plainText_length > 0 && PlainText[*plainText_length - 1] == '\n') {
        PlainText[*plainText_length - 1] = '\0';
        (*plainText_length)--;
    }
    if (choice == 1) {
        printf("Please enter the key (16 characters): ");
        fgets(key_128, KEY128_SIZE, stdin);
        int key_len = strlen(key_128);
        if (key_len > 0 && key_128[key_len - 1] == '\n') {
            key_128[key_len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else if (choice == 2) {
        printf("Please enter the key (24 characters): ");
        fgets(Key_192, KEY192_SIZE, stdin);
        int key_len = strlen(Key_192);
        if (key_len > 0 && Key_192[key_len - 1] == '\n') {
            Key_192[key_len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else if (choice == 3) {
        printf("Please enter the key (32 characters): ");
        fgets(Key_256, KEY256_SIZE, stdin);
        int key_len = strlen(Key_256);
        if (key_len > 0 && Key_256[key_len - 1] == '\n') {
            Key_256[key_len - 1] = '\0';
        } else {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } 
}

void XOR_operation(const char *PlainText, const char *Key, int Plain_length, int Key_length, char *CypherText) {
    int j = 0;
    for (int i = 0; i < Plain_length; i++) {
        CypherText[i] = PlainText[i] ^ Key[j];
        j = (j + 1) % Key_length;
    }
    CypherText[Plain_length] = '\0';
}

void reverse_XOR_operation(const char *CypherText, const char *Key, int CypherText_length, int Key_length, char *RecoveredPlainText) {
    int j = 0;
    for (int i = 0; i < CypherText_length; i++) {
        RecoveredPlainText[i] = CypherText[i] ^ Key[j];
        j = (j + 1) % Key_length;
    }
    RecoveredPlainText[CypherText_length] = '\0';
}

int main() {
    int PlainText_length = 0;
    char PlainText[PLAINTEXT_SIZE];
    char CypherText[CYPHERTEXT_SIZE];
    char RecoveredPlainText[PLAINTEXT_SIZE];
    char Key_128[KEY128_SIZE];
    char Key_192[KEY192_SIZE];
    char Key_256[KEY256_SIZE];
    int key_bits_size_option;
    
    user_input(PlainText, Key_128, Key_192, Key_256, &PlainText_length, &key_bits_size_option);
    if (key_bits_size_option == -1) {
        fprintf(stderr, "Encryption setup failed. Please try again.\n");
        return 1;
    }
    
    const char *selected_key;
    int key_length;
    switch (key_bits_size_option) {
        case 1:
            selected_key = Key_128;
            key_length = strlen(Key_128);
            break;
        case 2:
            selected_key = Key_192;
            key_length = strlen(Key_192);
            break;
        case 3:
            selected_key = Key_256;
            key_length = strlen(Key_256);
            break;
        default:
            fprintf(stderr, "Invalid key option\n");
            return 1;
    }
    
    XOR_operation(PlainText, selected_key, PlainText_length, key_length, CypherText);
    printf("\nEncrypted Ciphertext: %s\n", CypherText);
    printf("Hex: ");
    for (int i = 0; i < PlainText_length; i++) {
        printf("%02X ", (unsigned char)CypherText[i]);
    }
    printf("\n");
    
    reverse_XOR_operation(CypherText, selected_key, PlainText_length, key_length, RecoveredPlainText);
    printf("\nDecrypted Plaintext: %s\n", RecoveredPlainText);
    
    return 0;
}
