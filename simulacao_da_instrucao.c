#include <stdio.h>
#include <stdbool.h>

#define rx 0
#define ry 1
#define CTZ 38
#define STATE_FETCH 1
#define STATE_DECODE 2
#define STATE_EXECUTE 3
#define STATE_HALTED 5

int reg[8] = {0}; // vetor representando 8 registradores.
int pc = 0; // Contador de programa, que indica a posição atual na memória.
int state = STATE_FETCH; // Variável que guarda o estado atual da simulação
int opcode, LoadReg[8] = {0}, LoadFR; // Código de operação a ser executado e um vetor que indica quais registradores foram carregados
int memoria[256] = {0}; // vetor representando a memória com 256 posições

void simulacao() {
    while (state != STATE_HALTED) {
        switch (state) {
            case STATE_FETCH:
                opcode = memoria[pc]; // Carrega o próximo opcode da memória.
                state = STATE_DECODE; // Muda o estado para STATE_DECODE.
                pc++; // Avança o contador de programa pc.
                break;

            case STATE_DECODE:  // Decodifica o opcode carregado.
                switch (opcode) {
                    case CTZ: // Se o opcode for CTZ, muda o estado para STATE_EXECUTE.
                        state = STATE_EXECUTE;
                        break;

                    default: // Caso contrário, muda o estado para STATE_HALTED.
                        state = STATE_HALTED;
                        break;
                }
                break;

            case STATE_EXECUTE:
                // Marca LoadReg[ry] como carregado. Muda o estado para STATE_HALTED.
                reg[ry] = 0; // Inicializa o registrador ry com 0.
                if (reg[rx] != 0) { // Se o valor do registrador rx não for zero, divide rx por 2 até que não seja mais divisível por 2, incrementando ry a cada divisão.
                    while (reg[rx] % 2 == 0) {
                        reg[rx] /= 2;
                        reg[ry]++;
                    }
                }
                LoadReg[ry] = 1; // Marca LoadReg[ry] como carregado.
                state = STATE_HALTED; // Muda o estado para STATE_HALTED.
                break;
        }
    }
}

int main() {

    // Inicializa os registradores rx e ry

    reg[rx] = 32;  // Número para testar CTZ
    reg[ry] = 0;   // Registrador que armazenará o resultado

    memoria[pc] = CTZ; // carrega a memória com o opcode CTZ na posição apontada por pc

    simulacao(); // chama a função simulacao para executar a operação.

    // Imprime o resultado final do registrador ry, que contém a contagem de zeros à direita do número originalmente em rx.

    printf("Numero a ser testado: 32\n\n");
    printf("32 em binario: 100000\n\n");
    printf("Depois da operacao CTZ:\n\n");
    printf("ry = %d\n", reg[ry]);

    return 0;
}

// Inicialização: O programa começa com rx contendo o número a ser testado (neste exemplo, 32) e ry como 0.
// Carregamento do Opcode: A memória na posição do contador de programa pc é carregada com o opcode CTZ.
// Simulação: A função simulacao executa a operação de contagem de zeros à direita e armazena o resultado em ry.
// Impressão do Resultado: O valor final de ry é impresso, mostrando o número de zeros à direita no valor inicial de rx.
// Segundo Teste: 20, em binário: 10100
// Terceiro Teste: 115, em binario: 1110011
