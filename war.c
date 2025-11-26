#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHO 50

typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// FUNÇÃO PARA SIMULAR ATAQUE
void simularAtaque(Territorio *atacante, Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\nO território atacante não tem tropas suficientes para atacar!\n");
        return;
    }
    if (defensor->tropas <= 0) {
        printf("\nO território defensor já está sem tropas!\n");
        return;
    }

    printf("\n===== ATAQUE =====\n");
    printf("Atacante: %sTropas: %d\n", atacante->nome, atacante->tropas);
    printf("Defensor: %sTropas: %d\n", defensor->nome, defensor->tropas);

    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    printf("\nDado do ATAQUE: %d\n", dadoAtaque);
    printf("Dado da DEFESA: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        defensor->tropas--;
        printf("\nO ataque venceu! O defensor perdeu 1 tropa.\n");
    } else {
        atacante->tropas--;
        printf("\nA defesa venceu! O atacante perdeu 1 tropa.\n");
    }

    printf("\n===== Resultado =====\n");
    printf("Atacante: %d\n", atacante->tropas);
    printf("Defensor: %d\n", defensor->tropas);
    printf("=====================\n\n");
}


//  FUNÇÃO PARA O CASE 1 (CADASTRAR TERRITÓRIOS)
void cadastrarTerritorios(Territorio *territorios) {

    printf("==========================\n");
    printf("\nVamos cadastrar os 5 territórios iniciais \n");

    for (int i = 0; i < 5; i++) {
        printf("--- Cadastrando território %d ---\n", i + 1);

        printf(" Nome do território: ");
        fgets(territorios[i].nome, TAMANHO, stdin);

        printf(" Defina a cor do seu exército: ");
        fgets(territorios[i].cor, TAMANHO, stdin);

        printf(" Qual o número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar();
        
        printf("\n");
    }

    printf("Cadastro concluído!\n");
}


//  FUNÇÃO PARA O CASE 2 (MOSTRAR MAPA)
void mostrarMapa(Territorio *territorios) {

    printf("\n========== MAPA DO JOGO ==========\n\n");

    for (int i = 0; i < 5; i++) {

        printf("┌───────────────────────────────┐\n");
        printf("│ Território %d\n", i + 1);
        printf("│ Nome : %s", territorios[i].nome);
        printf("│ Cor  : %s", territorios[i].cor);
        printf("│ Tropas: %d\n", territorios[i].tropas);
        printf("└───────────────────────────────┘\n\n");
    }
}


//  FUNÇÃO PARA O CASE 3 (ATACAR)
void atacar(Territorio *territorios) {

    int a, d;

    printf("\n===== ATAQUE =====\n");
    printf("Escolha o território atacante (1-5): ");
    scanf("%d", &a);
    printf("Escolha o território defensor (1-5): ");
    scanf("%d", &d);

    a--;
    d--;

    if (a < 0 || a >= 5 || d < 0 || d >= 5) {
        printf("Territórios inválidos!\n");
        return;
    }

    if (a == d) {
        printf("Um território não pode atacar ele mesmo!\n");
        return;
    }

    simularAtaque(&territorios[a], &territorios[d]);
}


int main() {

    srand(time(NULL));

    int variavel;

    // Alocando dinamicamente 5 territórios
    Territorio *territorios = (Territorio *) calloc(5, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    
    // LOOP PRINCIPAL DO MENU
    while (1) {

        printf("==========================\n");
        printf("1. Cadastrar novo território\n");
        printf("2. Mostrar mapa\n");
        printf("3. Atacar\n");
        printf("4. Fechar o jogo!\n");
        printf("Escolha uma opção: ");
        scanf("%d", &variavel);
        getchar();

        switch (variavel) {

        case 1:
            cadastrarTerritorios(territorios);
            break;

        case 2:
            mostrarMapa(territorios);
            break;

        case 3:
            atacar(territorios);
            break;

        case 4:
            printf("Encerrando o jogo...\n");
            free(territorios);
            return 0;

        default:
            printf("Opção inválida!\n");
            break;
        }

    } 
    free(territorios);  
    return 0;
}
