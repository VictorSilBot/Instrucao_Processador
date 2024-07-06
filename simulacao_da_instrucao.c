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
int pc = 0; // Contador de programa, que indica a posi��o atual na mem�ria.
int state = STATE_FETCH; // Vari�vel que guarda o estado atual da simula��o
int opcode, LoadReg[8] = {0}, LoadFR; // C�digo de opera��o a ser executado e um vetor que indica quais registradores foram carregados
int memoria[256] = {0}; // vetor representando a mem�ria com 256 posi��es

void simulacao() {
    while (state != STATE_HALTED) {
        switch (state) {
            case STATE_FETCH:
                opcode = memoria[pc]; // Carrega o pr�ximo opcode da mem�ria.
                state = STATE_DECODE; // Muda o estado para STATE_DECODE.
                pc++; // Avan�a o contador de programa pc.
                break;

            case STATE_DECODE:  // Decodifica o opcode carregado.
                switch (opcode) {
                    case CTZ: // Se o opcode for CTZ, muda o estado para STATE_EXECUTE.
                        state = STATE_EXECUTE;
                        break;

                    default: // Caso contr�rio, muda o estado para STATE_HALTED.
                        state = STATE_HALTED;
                        break;
                }
                break;

            case STATE_EXECUTE:
                // Marca LoadReg[ry] como carregado. Muda o estado para STATE_HALTED.
                reg[ry] = 0; // Inicializa o registrador ry com 0.
                if (reg[rx] != 0) { // Se o valor do registrador rx n�o for zero, divide rx por 2 at� que n�o seja mais divis�vel por 2, incrementando ry a cada divis�o.
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

    reg[rx] = 32;  // N�mero para testar CTZ
    reg[ry] = 0;   // Registrador que armazenar� o resultado

    memoria[pc] = CTZ; // carrega a mem�ria com o opcode CTZ na posi��o apontada por pc

    simulacao(); // chama a fun��o simulacao para executar a opera��o.

    // Imprime o resultado final do registrador ry, que cont�m a contagem de zeros � direita do n�mero originalmente em rx.

    printf("Numero a ser testado: 32\n\n");
    printf("32 em binario: 100000\n\n");
    printf("Depois da operacao CTZ:\n\n");
    printf("ry = %d\n", reg[ry]);

    return 0;
}

// Inicializa��o: O programa come�a com rx contendo o n�mero a ser testado (neste exemplo, 32) e ry como 0.
// Carregamento do Opcode: A mem�ria na posi��o do contador de programa pc � carregada com o opcode CTZ.
// Simula��o: A fun��o simulacao executa a opera��o de contagem de zeros � direita e armazena o resultado em ry.
// Impress�o do Resultado: O valor final de ry � impresso, mostrando o n�mero de zeros � direita no valor inicial de rx.
// Segundo Teste: 20, em bin�rio: 10100
// Terceiro Teste: 115, em binario: 1110011
