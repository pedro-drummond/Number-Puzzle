// Pedro Dutra Drummond


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Declaração de struct
typedef struct 
{
    int col, row;
} Zero;

//cores
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)

void moveShuffle(int **board);

int checkWin(int **board)
{
    int win = 1;
    int gabarito[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
    int gabarito2[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] != gabarito[i][j]){
                win = 0;
            }
            if (win == 0)
                break;
        if (win == 0)
            break;
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (board[i][j] != gabarito2[i][j]){
                win = 0;
            }
            if (win == 0)
                break;
        if (win == 0)
            break;
        }
    }
    return win;
}

int **criaMatriz(int dim)
{
    int **matriz;
    matriz = malloc(dim * sizeof(int*));
    for (int i = 0; i < dim; i++)
        matriz[i] = malloc(dim * sizeof(int));
    return matriz;
}

void carregarJogoSalvo(int **board, int *jogadas, int tam){
    int linha, coluna;
    char nomeArquivo[50];
    FILE *arq;

    //Validando se o arquivo existe. se existir continua
    printf("Digite o nome do arquivo: ");
    getchar();
    fgets(nomeArquivo, 49, stdin); //nome do arquivo
    int k = 0;

    //removendo \n do fgets
    while (nomeArquivo[k] != '0'){
        if (nomeArquivo[k] == '\n') nomeArquivo[k] = '\0';
        k++;
    }

    //Abrindo arquivo e extraindo a matriz
    arq = fopen(nomeArquivo, "r");
    if (arq == NULL){
        printf(MAGENTA("Arquivo ") RED("%s") MAGENTA(" não encontrado! Encerrando programa.\n"), nomeArquivo);
        exit(1);
    }

    fscanf(arq, "%d%d", &linha, &coluna);
    for (int i = 0; i < tam; i++)
        for(int j = 0; j < tam; j++)
            fscanf(arq, "%d", &board[i][j]);
    fscanf(arq, "%d", jogadas);
    fclose(arq);
    system("clear");
    printf("Jogo "BLUE("%s") " carregado com sucesso!\n",nomeArquivo);
    printf("Tabuleiro ordenado.");
}
char *salvaArq(int **board, int *jogadas, int tam, char *escolha){
    static char nome[50];
    int  k = 0;
    for (int i = 7; escolha[i] != '\0'; i++){
        if (escolha[i] == '\n') escolha[i] = '\0';
        nome[k] = escolha[i];
        k++;
    }
    FILE *arq = fopen(nome, "w");
    fprintf(arq, "%d %d\n", tam, tam);
    for (int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++)
            fprintf(arq, "%d ", board[i][j]);
        fprintf(arq, "\n");
    }
    fprintf(arq, "%d", *jogadas);
    fclose(arq);
    return nome;
}

void carregarJogo(int **board, int *jogadas, int tam){
    int tamanho;
    FILE *temp = fopen("temp.dat", "rb");
    fread(&tamanho, sizeof(int), 1, temp);
    for (int i = 0; i < tam; i++)
        fread(board[i], sizeof(int), tam, temp);
    fread(&jogadas, sizeof(int), 1, temp);   
    fclose(temp);
}
void gravaTemp(int **board, int jogadas, int tam){
    FILE *temp = fopen("temp.dat", "wb");
    fwrite(&tam, sizeof(int), 1, temp); //escrevendo o numero de linhas e colunas que sao iguais SEMPRE.
    //escrevendo a matriz
    for (int i = 0; i < tam; i++)
        fwrite(board[i], sizeof(int), tam, temp);
    fwrite(&jogadas, sizeof(int), 1, temp);
    fclose(temp);
}
void liberamatriz(int **board){
    for (int i = 0; i < 3; i++)
        free(board[i]);
    free(board);    
}
int validaSalvar(char *escolha)
{
    char save[6];// = "salvar";
	for(int i = 0; i < 6; i++)
		save[i] = escolha[i];
	save[6] = '\0';
    if(strcmp(save, "salvar") == 0){
        return 1;
    }
	return 0;
}


void tabuleiroNovo(int **tabuleiro)
{
    //Criando novo tabuleiro com valores padrão
    int tabuleiroNovo = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            tabuleiro[i][j] = tabuleiroNovo;
            tabuleiroNovo++;
            if (tabuleiro[i][j] == 9) tabuleiro[i][j] = 0;
        }

}
void swap(int **board, int escolha, int zrow, int zcol)
{   
    //Swap de valores
    int aux;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == escolha)
            {
                aux = board[i][j];
                board[i][j] = board[zrow][zcol];
                board[zrow][zcol] = aux;
            }
}
void imprimeTabuleiro(int **tabuleiro)
{
    printf("\n");
    printf(BG_GREEN (TAB_TL TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TJ TAB_HOR TAB_HOR TAB_HOR TAB_TR "\n"));
    for (int i = 0; i < 3; i++) 
    {
        printf( BG_GREEN(TAB_VER));
        for (int j = 0; j < 3; j++)
            if (tabuleiro[i][j] == 0)
                printf(BG_GREEN("   "TAB_VER));

            else
                printf(BG_GREEN(BOLD(" %d ")) BG_GREEN(TAB_VER), tabuleiro[i][j]);
        if(i != 2)
            printf(BG_GREEN("\n"TAB_ML TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MJ TAB_HOR TAB_HOR TAB_HOR TAB_MR"\n"));
    }
    printf(BG_GREEN("\n"));
    printf(BG_GREEN(TAB_BL TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BJ TAB_HOR TAB_HOR TAB_HOR TAB_BR "\n"));   
}
void shuffle(int **board)
{
    int dificuldade, shuffleDificuldade;
    //Escolha de dificuldade
    do{
        printf("Digite o nível de dificuldade: ");
        printf(GREEN("(1) Facil, "));
        printf(BLUE("(2) Medio, "));
        printf(RED("(3) Dificil: "));
        scanf("%d", &dificuldade);
        if(dificuldade != 1 && dificuldade != 2 && dificuldade != 3)
        {
            printf("\nOpção inválida\n");
        }
    }while(dificuldade != 1 && dificuldade != 2 && dificuldade != 3);
    //Atribuindo numero de movimento
    switch (dificuldade)
    {
    case 1:
        shuffleDificuldade = 20;
        break;
    case 2:
        shuffleDificuldade = 40;
        break;
    case 3:
        shuffleDificuldade = 80;
        break;
    }
    //Reordenando tabuleiro
    for (int i = 0; i < shuffleDificuldade; i++){
        moveShuffle(board);
    }
    getchar();

}
void instrucoes(){
        printf("\n" BG_BLACK("  ") BG_WHITE("  ") BG_BLACK("  ") BG_WHITE("  ") "   INSTRUÇÕES   " BG_WHITE("  ") BG_BLACK("  ") BG_WHITE("  ") BG_BLACK("  ")"\n\n");
        printf("Digite um número de " GREEN("1") " a " GREEN("8") " para jogar.\n");
        printf("Digite a palavra" GREEN(" voltar ") "para voltar ao menu.\n");
        printf("Digite a palavra" GREEN(" sair ") "para sair do jogo.\n");
        printf("Digite a palavra" GREEN(" salvar ") BLUE("nome_do_arquivo.txt") " para salvar o jogo.\n");
        printf("Os comando deve ser digitados em letras " BOLD("minusculas\n\n"));
        printf("-----------------------------------------\n");
}
void menu()
{
    printf("\n" BG_BLACK("  ") BG_WHITE("  ") BG_BLACK("  ") BG_WHITE("  ") BOLD(" QUEBRA CABEÇAS "));
    printf( BG_WHITE("  ") BG_BLACK("  ") BG_WHITE("  ") BG_BLACK("  ")"\n");
    printf( BG_WHITE("  ") BG_BLACK("  ") BG_WHITE("  ")  BG_BLACK("  ") "      MENU      ");
    printf(  BG_BLACK("  ") BG_WHITE("  ")  BG_BLACK("  ") BG_WHITE("  ") "\n\n");
    printf(BOLD(BLUE("0 ")));
    printf("Sair\n");
    printf(BOLD(BLUE("1")));
    printf(" Começar um novo jogo\n");
    printf(BOLD(BLUE("2 ")));
    printf("Continuar jogo atual\n");
    printf(BOLD(BLUE("3 ")));
    printf("Continuar um jogo salvo\n");
    printf(BOLD(BLUE("4 ")));
    printf("Instruções\n");
    printf("\n------------------------------------\n");
}

Zero findZero(int **board)
{
    int zeroFound = 0;
    Zero z;
    for (z.row = 0; z.row < 3; z.row++)
    {
        for (z.col = 0; z.col < 3; z.col++)
            if (board[z.row][z.col] == 0)
            {
                zeroFound = 1;
                break;
            }
        if (zeroFound) break;
    }
    return z;    
}

void moveShuffle(int **board)
{
    int num, nrow, ncol, valid;
    
    //Achando a posição do 0
    Zero z;
    z = findZero(board);
    //Embaralhando
    do{
        valid = 0;
        num = rand() % 8 + 1;
        //verificando se o movimento é possível e se possível trocar se não mensagem de erro
        for (nrow = 0; nrow < 3; nrow++)
        {
            for (ncol = 0; ncol < 3; ncol++)
                if (board[nrow][ncol] == num)
                {
                    if (nrow == z.row)
                    {
                        if (ncol == z.col + 1 || ncol == z.col - 1)
                        {
                            swap(board, num, z.row, z.col);
                            return;
                        }
                        else
                        {
                            valid++;
                        }
                        
                    }
                    else if (ncol == z.col)
                    {
                        if (nrow == z.row + 1 || nrow == z.row - 1)
                        {
                            swap(board, num, z.row, z.col);
                            return;
                        }
                        else
                        {
                            valid++;
                        }
                    }
                    else
                    {
                        valid++;
                    }
                }
        }
    }while(valid);
}
int move(int **board, long num)
{
    int nrow, ncol;
    Zero z;
    z = findZero(board);

    //verificando se o movimento é possível e se possível trocar se não mensagem de erro
    for (nrow = 0; nrow < 3; nrow++)
    {
        for (ncol = 0; ncol < 3; ncol++)
            if (board[nrow][ncol] == num)
            {
                if (nrow == z.row)
                {
                    if (ncol == z.col + 1 || ncol == z.col - 1)
                    {
                        swap(board, num, z.row, z.col);
                        return 1;
                    }
                    else
                    {
                        printf(MAGENTA("\nNão é possível mover a peça "));
                        printf(RED("%ld\n"), num);
                        break;
                    }
                    
                }
                else if (ncol == z.col)
                {
                    if (nrow == z.row + 1 || nrow == z.row - 1)
                    {
                        swap(board, num, z.row, z.col);
                        return 1;
                    }
                    else
                    {
                        printf(MAGENTA("\nNão é possível mover a peça "));
                        printf(RED("%ld\n"), num);
                        break;
                    }
                }
                else
                {
                        printf(MAGENTA("\nNão é possível mover a peça "));
                        printf(RED("%ld\n"), num);
                    break;
                }
            }
    }
    return 0;
}
