#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

// Declara os tokens
/** Autora: Paula Silva **/

enum TokenType {
    ID,
    NUM,
    SYMBOL,
    ERRO,
    STRING
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

// Função para verificar se o caractere é um símbolo válido
int is_valid_symbol(char c) {
    char valid_symbols[] = "=+-*/(){};";
    for(int i = 0; i < sizeof(valid_symbols); i++){
        if(valid_symbols[i] == c)
            return 1;
    }
    return 0;
}

void analex(FILE *inputFile, FILE *outputFile) {
    
    char c = prox_char(inputFile);
    char lexeme[100];
    int i = 0;
    int string_open = 0;

    while (c != '\0') {
        
        if (isalpha(c) || isdigit(c)) {
            lexeme[i++] = c;
            c = prox_char(inputFile);
        while (isalnum(c) || c == '.') {
            lexeme[i++] = c;
            c = prox_char(inputFile);
        }
        ungetc(c, inputFile);
        lexeme[i] = '\0';
        if (isalpha(lexeme[0])) {
            grava_token(ID, lexeme, outputFile);
        } else {
            grava_token(NUM, lexeme, outputFile);
        }
            i = 0;
        }
        else if (c == '\"') {
            c = prox_char(inputFile);
            while (c != '\"' && c != EOF) {
                lexeme[i++] = c;
                c = prox_char(inputFile);
            }
            if (c == '\"') {
                    lexeme[i] = '\0';
                    grava_token(STRING, lexeme, outputFile);
            } else {
            grava_token(ERRO, "unterminated string", outputFile);
            }
            i = 0;
        } 
        else if (is_valid_symbol(c)) {
            if(i && (isalpha(lexeme[i-1]) || isdigit(lexeme[i-1]) || lexeme[i-1] == '.')) {
                char error[100];
                sprintf(error, "Invalid symbol: %c", c);
                grava_token(ERRO, error, outputFile);
            }
            lexeme[i++] = c;
            lexeme[i] = '\0';
            grava_token(SYMBOL, lexeme, outputFile);
            i = 0;
        } 
        else if (isspace(c)) {
            c = prox_char(inputFile);
        } 
        else {
            char error[100];
            sprintf(error, "Invalid character: %c", c);
            grava_token(ERRO, error, outputFile);
        }
        
        c = prox_char(inputFile);
    }
    fclose(inputFile);
    fclose(outputFile);
    
}




int main(){

    FILE *inputFile, *outputFile;
    
    inputFile= fopen("input.txt", "r");
    outputFile= fopen("output.txt", "w");

    if (inputFile == NULL ||outputFile == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }
    
    analex(inputFile, outputFile);
    
    // fclose(inputFile);
    // fclose(outputFile);
    return 0;
}