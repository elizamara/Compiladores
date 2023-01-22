## Manual do Usuário 

Este código é um analisador léxico, que é uma etapa da compilação que separa a entrada de um programa (geralmente um arquivo de texto) em uma sequência de tokens. Cada token é composto por um tipo e um lexema. Um lexema é a sequência de caracteres que representa o token.

A função analex() é uma função que realiza a análise léxica do arquivo de entrada, identificando os tokens presentes nele e escrevendo-os em um arquivo de saída. Ela faz isso lendo caractere por caractere do arquivo de entrada através da função prox_char() e, baseado no tipo de caractere lido, inicia uma sequência de análise para identificar o token correspondente. Se o caractere lido for uma letra, a função entra em um loop para ler todos os caracteres subsequentes que também sejam letras ou dígitos, armazenando-os em um array lexeme. Quando encontra um caractere que não é uma letra ou dígito, a função coloca esse caractere de volta no arquivo de entrada com ungetc() e adiciona um caractere de fim de string ao array lexeme. Em seguida, a função chama grava_token(), passando o tipo de token ID e o array lexeme como argumentos. A função grava_token() escreve o token e o lexema no arquivo de saída.

Se o caractere lido for um espaço em branco, a função irá ignorar e continuar lendo o próximo caractere, sem armazenar em nenhum buffer ou gerar nenhum token.

Se o caractere lido não for uma letra, dígito, símbolo ou espaço em branco, a função irá gravar uma mensagem de erro "Invalid character: %c\n" e parar o programa.

A função grava_token() tem como objetivo escrever no arquivo de saída informações sobre o token encontrado. Ela recebe três parâmetros: o primeiro é o tipo de token, o segundo é o lexema correspondente ao token e o terceiro é o ponteiro para o arquivo de saída. A função grava_token() é chamada dentro da função analex() sempre que é identificado um token válido.

### Como executar o analisador lexico 

1) Crie um arquivo fonte em C-- para ser analisado pelo programa anaLexic.c 
    
    Exemplo: code.txt

2) Depois execute o seguinte comandos:

        gcc o- analise anaLexic.c

        ./analise code.txt

3) Exemplo de saída. 
        
        Entrada: paula = 24;

        Saída: 

            Token: 0, Lexema: paula
            Token: 2, Lexema:24 ;


## Link para o vídeo: https://youtu.be/cFlsr00fapc
