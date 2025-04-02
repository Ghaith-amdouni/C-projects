#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define ALPHABET_LENGTH 26
bool is_valid_key(string key);
void encrypt(string plaintext, string key);
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage :./substitution key\n");
        return 1;
    }
    string key = argv[1];
    if(!is_valid_key(key))
    {
        printf("Invalid key.key must contain 26 unique alphabetical characters .\n");
        return 1;
    }
    // GET the user plaintext
    string plaintext = get_string("plaintext:");
    printf("ciphertext:");
    encrypt(plaintext, key);
    printf("\n");
    return 0;
}
bool is_valid_key(string key)
{
    if (strlen(key) != ALPHABET_LENGTH)
    {
        return false;
    }
    bool letters[ALPHABET_LENGTH] = {false};
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        int index = toupper(key[i]) - 'A';
        if (letters[index])
        {
            return false;
        }
        letters[index] = true;
    }
    return true;
}
void encrypt(string plaintext, string key)
{
    for (int i = 0;i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = plaintext[i] - base;
            printf("%c", isupper(plaintext[i]) ? toupper(key[index]) : tolower(key[index]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
}
