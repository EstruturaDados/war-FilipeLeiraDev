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

/*
 * Programa: WAR ESTRUTURADO - MISSÃO ESTRATÉGICA (DESAFIO FINAL)
 * Autor: [SEU NOME AQUI]
 * Descrição: Jogo com 2 jogadores, territórios dinâmicos, missões secretas,
 *            ataque com dados e verificação de vitória.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirMapa(Territorio* mapa, int n);
void exibirMissao(char* missao);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2);
int escolherTerritorio(Territorio* mapa, int n, char* corJogador, char* tipo);
int validarAtaque(Territorio* atacante, Territorio* defensor);

// Vetor de missões pré-definidas (5 opções)
char* missoes[] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar pelo menos 5 territorios",
    "Destruir o territorio mais forte do inimigo",
    "Conquistar todos os territorios da America do Sul"
};
int totalMissoes = 5;

int main() {
    int n;
    Territorio* mapa = NULL;
    char* missaoJogador1 = NULL;
    char* missaoJogador2 = NULL;

    // Inicializa aleatoriedade
    srand(time(NULL));

    printf("=== WAR ESTRUTURADO - MODO ESTRATEGICO ===\n\n");

    // Entrada: número de territórios
    printf("Quantos territorios no mapa? (min 3): ");
    scanf("%d", &n);
    if (n < 3) {
        printf("Numero invalido!\n");
        return 1;
    }

    // Alocação dinâmica do mapa
    mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (!mapa) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    // Alocação das missões
    missaoJogador1 = (char*) malloc(100 * sizeof(char));
    missaoJogador2 = (char*) malloc(100 * sizeof(char));
    if (!missaoJogador1 || !missaoJogador2) {
        printf("Erro ao alocar missao!\n");
        liberarMemoria(mapa, missaoJogador1, missaoJogador2);
        return 1;
    }

    // Cadastro
    cadastrarTerritorios(mapa, n);

    // Sorteio das missões
    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Exibir missões apenas uma vez
    printf("\n=== INICIO DO JOGO ===\n");
    printf("Jogador 1 - Sua missao: ");
    exibirMissao(missaoJogador1);
    printf("Jogador 2 - Sua missao: ");
    exibirMissao(missaoJogador2);
    printf("\nPressione ENTER para comecar...\n");
    getchar(); getchar(); // Limpa buffer

    // Loop principal do jogo
    char turno = '1'; // Alterna entre jogador 1 e 2
    while (1) {
        system("clear || cls"); // Limpa tela (Linux ou Windows)
        printf("=== TURNO DO JOGADOR %c ===\n", turno);
        exibirMapa(mapa, n);

        // Escolher atacante e defensor
        int idx_atacante = escolherTerritorio(mapa, n, (turno == '1' ? "Verde" : "Azul"), "ATACANTE");
        if (idx_atacante == -1) continue;

        int idx_defensor = escolherTerritorio(mapa, n, (turno == '1' ? "Azul" : "Verde"), "DEFENSOR");
        if (idx_defensor == -1) continue;

        // Validar ataque
        if (!validarAtaque(&mapa[idx_atacante], &mapa[idx_defensor])) {
            printf("Ataque invalido!\n");
            printf("Pressione ENTER para continuar...");
            getchar(); getchar();
            continue;
        }

        // Executar ataque
        printf("\n--- SIMULANDO BATALHA ---\n");
        atacar(&mapa[idx_atacante], &mapa[idx_defensor]);

        // Verificar vitória
        int venceu1 = verificarMissao(missaoJogador1, mapa, n);
        int venceu2 = verificarMissao(missaoJogador2, mapa, n);

        printf("\n=== ESTADO ATUAL ===\n");
        exibirMapa(mapa, n);

        if (venceu1) {
            printf("\nPARABENS! JOGADOR 1 CUMPRIU A MISSAO!\n");
            printf("Missao: %s\n", missaoJogador1);
            break;
        }
        if (venceu2) {
            printf("\nPARABENS! JOGADOR 2 CUMPRIU A MISSAO!\n");
            printf("Missao: %s\n", missaoJogador2);
            break;
        }

        // Alterna turno
        turno = (turno == '1') ? '2' : '1';
        printf("\nPressione ENTER para o proximo turno...");
        getchar(); getchar();
    }

    // Libera tudo
    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    printf("\nJogo finalizado. Memoria liberada.\n");
    return 0;
}

// Função: Cadastro com cores fixas (J1=Verde, J2=Azul)
void cadastrarTerritorios(Territorio* mapa, int n) {
    printf("\n=== CADASTRO DOS TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Territorio %d ---\n", i + 1);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        // Alterna cores
        strcpy(mapa[i].cor, (i % 2 == 0) ? "Verde" : "Azul");

        do {
            printf("Tropas (min 1): ");
            scanf("%d", &mapa[i].tropas);
        } while (mapa[i].tropas < 1);
    }
}

// Função: Exibe o mapa
void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== MAPA ATUAL ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d. [%s] %s - %d tropas\n", i + 1, mapa[i].cor, mapa[i].nome, mapa[i].tropas);
    }
}

// Função: Exibe missão (passagem por valor)
void exibirMissao(char* missao) {
    printf("%s\n", missao);
}

// Função: Sorteia e copia missão (passagem por referência)
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    strcpy(destino, missoes[idx]);
}

// Função: Verifica se missão foi cumprida
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    if (strstr(missao, "3 territorios seguidos")) {
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0 && strcmp(mapa[i].cor, mapa[i+2].cor) == 0)
                return 1;
        }
    }
    if (strstr(missao, "todas as tropas da cor vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
    if (strstr(missao, "pelo menos 5 territorios")) {
        int count = 0;
        char cor = (strstr(missao, "Jogador 1")) ? 'V' : 'A'; // simplificado
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].cor[0] == (strstr(missao, "Verde") ? 'V' : 'A'))
                count++;
        }
        return count >= 5;
    }
    if (strstr(missao, "territorio mais forte")) {
        int max_tropas = 0, idx_max = -1;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > max_tropas) {
                max_tropas = mapa[i].tropas;
                idx_max = i;
            }
        }
        return (idx_max != -1 && strcmp(mapa[idx_max].cor, "Verde") != 0);
    }
    return 0;
}

// Função: Escolher território com validação
int escolherTerritorio(Territorio* mapa, int n, char* corJogador, char* tipo) {
    int idx;
    printf("Escolha territorio %s da cor [%s] (1 a %d): ", tipo, corJogador, n);
    scanf("%d", &idx);
    idx--;
    if (idx < 0 || idx >= n) {
        printf("Indice invalido!\n");
        return -1;
    }
    if (strcmp(mapa[idx].cor, corJogador) != 0) {
        printf("Esse territorio nao e seu!\n");
        return -1;
    }
    if (strcmp(tipo, "ATACANTE") == 0 && mapa[idx].tropas < 2) {
        printf("Precisa de pelo menos 2 tropas para atacar!\n");
        return -1;
    }
    return idx;
}

// Função: Simula ataque com dados
void atacar(Territorio* atacante, Territorio* defensor) {
    int d1 = (rand() % 6) + 1;
    int d2 = (rand() % 6) + 1;

    printf("%s ataca %s!\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", d1, d2);

    if (d1 > d2) {
        printf(">>> VITORIA! <<<\n");
        int tropas_enviadas = atacante->tropas / 2;
        if (tropas_enviadas < 1) tropas_enviadas = 1;

        defensor->tropas = tropas_enviadas;
        atacante->tropas -= tropas_enviadas;
        strcpy(defensor->cor, atacante->cor);
    } else {
        printf(">>> DERROTA! <<<\n");
        atacante->tropas--;
    }
}

// Função: Valida ataque (cores diferentes)
int validarAtaque(Territorio* atacante, Territorio* defensor) {
    return strcmp(atacante->cor, defensor->cor) != 0;
}

// Função: Libera toda memória alocada
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}