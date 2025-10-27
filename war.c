// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

//    return 0;
//}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
/*
 * Programa: Cadastro de 5 Territórios
 * Disciplina: Programação em C
 * Descrição: Cadastra 5 territórios com nome, cor do exército e número de tropas,
 *            e exibe os dados logo após o preenchimento.
 */
/*
 * Programa: War Estruturado - Ataque entre Territórios
 * Disciplina: Programação em C
 * Descrição: Sistema com alocação dinâmica de territórios, cadastro,
 *            simulação de ataque com dados aleatórios e gerenciamento de memória.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
int validarAtaque(Territorio* atacante, Territorio* defensor);

// Função principal
int main() {
    int n;
    Territorio* mapa = NULL;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("=== WAR ESTRUTURADO - SIMULACAO DE BATALHA ===\n\n");

    // Entrada: número de territórios
    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Numero invalido! Encerrando...\n");
        return 1;
    }

    // Alocação dinâmica com calloc (inicializa com zeros)
    mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, n);

    // Exibição inicial
    printf("\n=== ESTADO INICIAL DOS TERRITORIOS ===\n");
    exibirTerritorios(mapa, n);

    // Loop de ataques (o usuário escolhe quando parar)
    char continuar;
    do {
        int atacante_idx, defensor_idx;

        // Exibe territórios para escolha
        exibirTerritorios(mapa, n);

        // Escolha do atacante
        printf("\nEscolha o territorio ATACANTE (1 a %d): ", n);
        scanf("%d", &atacante_idx);
        atacante_idx--; // Ajuste para índice do vetor

        // Escolha do defensor
        printf("Escolha o territorio DEFENSOR (1 a %d): ", n);
        scanf("%d", &defensor_idx);
        defensor_idx--;

        // Validações
        if (atacante_idx < 0 || atacante_idx >= n || defensor_idx < 0 || defensor_idx >= n) {
            printf("Indice invalido! Tente novamente.\n\n");
            continue;
        }

        if (atacante_idx == defensor_idx) {
            printf("Um territorio nao pode atacar a si mesmo!\n\n");
            continue;
        }

        if (!validarAtaque(&mapa[atacante_idx], &mapa[defensor_idx])) {
            printf("Ataque invalido: territorios da mesma cor!\n\n");
            continue;
        }

        if (mapa[atacante_idx].tropas < 2) {
            printf("Ataque invalido: atacante precisa de pelo menos 2 tropas!\n\n");
            continue;
        }

        // Executa o ataque
        printf("\n--- SIMULANDO ATAQUE ---\n");
        atacar(&mapa[atacante_idx], &mapa[defensor_idx]);

        // Exibe resultado
        printf("\n=== ESTADO APOS O ATAQUE ===\n");
        exibirTerritorios(mapa, n);

        // Pergunta se quer continuar
        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    // Libera memória alocada
    liberarMemoria(mapa);

    printf("\nJogo encerrado. Memoria liberada com sucesso!\n");
    return 0;
}

// Função: Cadastra n territórios via ponteiros
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\n=== CADASTRO DE TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);

        // Limpa buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        do {
            printf("Quantidade de tropas (min 1): ");
            scanf("%d", &mapa[i].tropas);
            if (mapa[i].tropas < 1) printf("Tropas devem ser pelo menos 1!\n");
        } while (mapa[i].tropas < 1);
    }
}

// Função: Exibe todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== LISTA DE TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d. [%s] %s - Tropas: %d\n",
               i + 1, mapa[i].cor, mapa[i].nome, mapa[i].tropas);
    }
}

// Função: Simula ataque com dados (1 a 6)
void atacar(Territorio* atacante, Territorio* defensor) {
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;

    printf("Dado do atacante (%s): %d\n", atacante->nome, dado_atacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dado_defensor);

    if (dado_atacante > dado_defensor) {
        // Atacante vence
        printf(">>> ATAQUE BEM-SUCEDIDO! <<<\n");

        // Defensor perde todas as tropas
        int tropas_conquistadas = defensor->tropas;
        defensor->tropas = atacante->tropas / 2;  // Metade das tropas do atacante vão para o novo território
        if (defensor->tropas < 1) defensor->tropas = 1;

        atacante->tropas -= defensor->tropas;  // Atacante deixa tropas no novo território

        // Muda a cor (dono)
        strcpy(defensor->cor, atacante->cor);

        printf("%s agora pertence a %s com %d tropas!\n",
               defensor->nome, defensor->cor, defensor->tropas);

    } else {
        // Defensor vence ou empata
        printf(">>> ATAQUE REPELIDO! <<<\n");
        atacante->tropas -= 1;  // Perde 1 tropa
        printf("%s perdeu 1 tropa. Restam: %d\n", atacante->nome, atacante->tropas);
    }
}

// Função: Valida se o ataque é permitido (cores diferentes)
int validarAtaque(Territorio* atacante, Territorio* defensor) {
    return strcmp(atacante->cor, defensor->cor) != 0;
}

// Função: Libera memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    mapa = NULL; 
}