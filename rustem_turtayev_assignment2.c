#include <stdio.h>
#include <string.h>


void readKey (char **keyArray) {                               // The function to read the key file using the pointer array created in main function

    char temp_keyArray[254];
    FILE *key;
    key = fopen("key.254", "r");

    for (int i = 0; i < 254; ++i) {
        temp_keyArray[i] = fgetc(key);
    }

    *keyArray = temp_keyArray;                                 // Pointing the pointer to array that we've created and filled here
    fclose(key);
}


void encrypt (FILE *in, FILE *out, char keyArray[], char password[]) {

    int length = strlen(password);
    int i = 0;                                                  // Iteration for password string
    while (1) {
        char inchar = fgetc(in);

        if (inchar == EOF || inchar == '\0') break;             // To get rid of the last useless characters in string arrays

        char index = (inchar + password[i]) % 254;              // Calculating the index for keyfile array

        char write_char = keyArray[(unsigned char) index];      // Accessing the character from keyfile array by index that we calculated before

        putc(write_char, out);

        fflush(in);
        fflush(out);                                            // This we need in order to read and write values properly

        i++;
        if (i == length) i = 0;
    }
}


void decrypt (FILE *in, FILE *out, char keyArray[], char password[]) {

    int length = strlen(password);
    int i = 0;
    while (!feof(in)) {
        char inchar = fgetc(in);
        char index = 0;

        if (inchar == EOF || inchar == '\0') break;             // To get rid of the last useless characters in string arrays

        for (int j = 0; j < 254; j++) {                         // Finding out the character in keyfile array in order to get the index
            if (keyArray[j] == inchar) {
                index = j;
                break;
            }
        }

        index -= password[i];
        index %= 254;                                           // Operations for converting the index into character of original file

        fputc(index, out);

        fflush(in);
        fflush(out);                                            // This we need in order to write input values properly

        i++;
        if (i == length) i = 0;                                 // This piece we need for iteration of password string
    }
}


void modPrint (char *printString) {                             // This function makes the life easier, because with it I do not care about the 'new line' chars in printf statements

    printf("%s\n", printString);

}


int main() {

    modPrint("WELCOME to the encryption service.");

    modPrint("ENTER your password");
    char password[256];
    scanf("%s", password);

    char array[254];                                             // Creating the array for keyfile
    char *keyArray;                                              // Creating the pointer array for reading the key file in other functions
    readKey(&keyArray);                                          // Pointing to array thats being filled out in function readKey

    for (int i = 0; i < 254; i++) {
        array[i] = keyArray[i];                                  // Writing to local array in order to use in other functions as an array not pointer
    }

    while (1) {

        modPrint("MENU: <e>ncode, <d>ecode, or <q>uit");
        char command[256];
        scanf("%s", command);

        if (command[0] == 'e') {

            modPrint("ENTER a file to encrypt");
            char in[256];
            scanf("%s", in);

            FILE *fin;
            fin = fopen(in, "r");

            if (fin == NULL) {
                printf("CANNOT open %s\n", in);
                continue;
            }

            modPrint("ENTER a filename for the encrypted file.");
            char out[256];
            scanf("%s", out);

            FILE *fout;
            fout = fopen(out, "w");

            if (fout == NULL) {
                printf("CANNOT open %s\n", out);
                continue;
            }

            encrypt(fin, fout, array, password);

            fclose(fin);
            fclose(fout);

        } else if (command[0] == 'd') {

            modPrint("ENTER a file to decrypt");
            char in[256];
            scanf("%s", in);

            FILE *fin;
            fin = fopen(in, "r");

            if (fin == NULL) {
                printf("CANNOT open %s\n", in);
                continue;
            }

            modPrint("ENTER a filename for the decrypted file.");
            char out[256];
            scanf("%s", out);

            FILE *fout;
            fout = fopen(out, "w");

            if (fout == NULL) {
                printf("CANNOT open %s\n", out);
                continue;
            }

            decrypt(fin, fout, array, password);

            fclose(fin);
            fclose(fout);

        } else if (command[0] == 'q') {

            modPrint("BYE!");
            break;

        } else {

            printf("UNRECOGNIZED %c\n", command[0]);

        }
    }

}
