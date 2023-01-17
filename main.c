// Pedro Dutra Drummond

//Quebra cabeça de números
//INCLUDES
#include "funcoes.h"

int main(){
    //DECLARAÇÕES
    int **board;
    const int tam = 3;
    int opcaoMenu, cmdValido, voltarmenu, jogadas, contJA = 0, inst;
    long num;
    char escolha[56], tecla;
    srand(time(NULL));
    //LOOP PRINCIPAL
    do{
        voltarmenu = 0;
        inst = 0;

        //Loop do menu principal  
        system("clear");
        menu();
        do{
            opcaoMenu = -1;
            printf("Digite a opção desejada: ");
            scanf("%d", &opcaoMenu);
            switch (opcaoMenu)
            {
            case 1:
                //NOVO JOGO
                jogadas = 0;
                contJA = 1;
                board = criaMatriz(tam);
                tabuleiroNovo(board);
                shuffle(board);
                system("clear");
                printf("Tabuleiro ordenado!\n");
                imprimeTabuleiro(board);
                break;
            case 2:
                //Continuar jogo atual
                if (contJA == 0) //Condicional para verificar se já existe um jogo em andamento
                {
                    printf(RED("Não há nenhum jogo em andamento!\n"));
                    printf("Começando novo jogo...\n"); //iniciando novo jogo
                    jogadas = 0;
                    contJA = 1; //setando flag de jogo em andamento
                    //iniciando novo jogo
                    board = criaMatriz(tam);
                    tabuleiroNovo(board);
                    shuffle(board);
                    system("clear");
                    printf("Tabuleiro ordenado!\n");
                    imprimeTabuleiro(board);
                }
                else
                {
                    //carregando jogo atual
                    system("clear");
                    board = criaMatriz(tam);
                    carregarJogo(board, &jogadas, tam);
                    printf("Tabuleiro ordenado!\n");
                    imprimeTabuleiro(board);
                    getchar();
                }
                break;

            case 3:
                //Continuar jogo salvo
                contJA = 1; //variável para indicar que já existe um jogo em andamento
                board = criaMatriz(tam);
                carregarJogoSalvo(board, &jogadas, tam);
                imprimeTabuleiro(board);
                break;
            case 4:
                //Instruções
                getchar();
                system("clear");
                instrucoes();
                voltarmenu = 0;
                opcaoMenu = -1;
                inst = 1;
                printf("Pressione enter para voltar ao menu principal.");
                scanf("%c", &tecla);
                system("clear");
                menu();
                break;
            case 0:
                //sair
                return 0;             
            default:
                if (inst == 1){ //Condicional para verificar se o usuário já fez a instrução
                    break;
                }
                else{
                    printf(RED("Opção inválida!\n"));
                    voltarmenu = 1;
                }
                break;
            }
        }while(opcaoMenu != 4 && opcaoMenu != 3 && opcaoMenu != 2 && opcaoMenu != 1);
        
        // game loop 
        while(checkWin(board) == 0){
            // Digitando o número ou a escolha
            do{
                printf("Digite um comando ou o número da peça que deseja mover: ");
                fgets(escolha, 50, stdin);
                num = atol(escolha); //transforma a string em long

                //Se for um numero, então vamos verificar se é válido, se não for, vamos pedir novamente, se for válido, então vamos fazer o movimento
                if(num >= 1 && num <= 8)
                {
                    cmdValido =  move(board, num);
                    if (cmdValido == 1)
                    {
                        jogadas++;
                        system("clear");
                        break;
                    }  
                }
                // OPÇÃO PARA VOLTAR (SALVA EM UM ARQUIVO BINARIO E LIBERA A MEMORIA DA MATRIZ)
                else if(strcmp(escolha, "voltar\n") == 0)
                {
                    // Voltar p/ o menu
                    cmdValido = 1;
                    voltarmenu = 1; // flag para voltar p/ o menu caso seja 0
                    gravaTemp(board, jogadas, tam); //grava o jogo em um arquivo binario
                    liberamatriz(board);
                    system("clear");
                    break;
                }
                // OPÇÃO PARA SAIR (LIBERA A MATRIZ E FECHA O PROGRAMA)              
                else if(strcmp(escolha, "sair\n") == 0)
                {
                    printf(RED("\nSaindo...\n\n"));
                    liberamatriz(board);
                    return 0;
                }
                else if (validaSalvar(escolha) == 1)
                {
                    // Salvar jogo
                    char *nomeArquivo = salvaArq(board, &jogadas, tam, escolha);
                    system("clear");
                    printf("O arquivo");
                    printf(GREEN(" '%s' "), nomeArquivo);
                    printf("foi salvo.");
                    break;
                }
                else
                {
                    // Comando inválido
                    printf(RED("Comando inválido\n"));
                }
            }while(cmdValido == 0);
            if (voltarmenu == 1)
                break;
            else
            {
                printf("\n"); //pula linha estitico
                imprimeTabuleiro(board);
                printf("Jogadas feitas até agora: ");
                printf(RED("%d\n"), jogadas);
                //verificar se ganhou, se for igual a 1 sai do loop.
                if (checkWin(board) == 1){
                    printf(BOLD(GREEN("Parabéns, você ganhou!\n")));
                }            
            }
        }
    }while(voltarmenu == 1);

    return 0;
}

