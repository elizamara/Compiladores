#include <stdio.h>
#include <stdlib.h> 

// Declara os tokens
/** Autora: Puala Silva **/

enum TokenType {
    ID,
    NUM,
    SYMBOL,
    SEPARATOR
};

// Função para gravar token no arquivo de saída
void grava_token(enum TokenType token, const char *lexema, FILE *outputFile) {
    fprintf(outputFile, "Token: %d, Lexema: %s\n", token, lexema);
}

// Função para ler próximo caractere do arquivo de entrada
char prox_char(FILE *inputFile) {
    char c = fgetc(inputFile);
    if (c == EOF) {
        return '\0';
    }

    return c;
}

void analex(FILE *inputFile, FILE *outputFile) {
    
    char c = prox_char(inputFile);
    char lexeme[100];
    int i = 0;
    
    while (c != '\0') {
        
        if (isalpha(c)) {
            lexeme[i++] = c;
            c = prox_char(inputFile);
            while (isalnum(c)) {
                lexeme[i++] = c;
                c = prox_char(inputFile);
            }
            ungetc(c, inputFile);
            lexeme[i] = '\0';
            grava_token(ID, lexeme, outputFile);
            i = 0;
        } 
        else if (isdigit(c)) {
            lexeme[i++] = c;
            c = prox_char(inputFile);
            while (isdigit(c)) {
                lexeme[i++] = c;
                c = prox_char(inputFile);
            }
            ungetc(c, inputFile);
            lexeme[i] = '\0';
            grava_token(NUM, lexeme, outputFile);
            i = 0;
        } 
        else if (ispunct(c)) {
            lexeme[i++] = c;
            c = prox_char(inputFile);
            while (ispunct(c)) {
                lexeme[i++] = c;
                c = prox_char(inputFile);
            }
            ungetc(c, inputFile);
            lexeme[i] = '\0';
            grava_token(SYMBOL, lexeme, outputFile);
            i = 0;
        } 
        else if (isspace(c)) {
        c = prox_char(inputFile);
        } 
        
        else {
        printf("Invalid character: %c\n", c);
        c = prox_char(inputFile);
        }
    }
}




int main(){

    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");
    
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    if (outputFile == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }
    
    analex(inputFile, outputFile);
    
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}