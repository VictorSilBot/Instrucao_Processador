# CTZ: Instrução nova para o Processador

## Autores: 

Victor Silva Botelho, Matheus D'Afonseca e Silva, João Victor Andrade dos Santos

## Vídeo sobre a Instrução no Youtube: 

[![Função CTZ](https://img.youtube.com/vi/Fpy74562nf4/0.jpg)](https://www.youtube.com/watch?v=Fpy74562nf4)

## Descrição:

A função CTZ (Count Trailing Zeros) é uma instrução que conta o número de bits de valor zero à direita em um número binário. Ela depende de várias etapas para ser executada corretamente em uma máquina baseada em microarquitetura. Aqui está uma visão geral das etapas envolvidas:

1. **Fetch (Busca):**
   - A instrução é buscada da memória. O `Program Counter (PC)` aponta para a próxima instrução a ser executada.
   - **Estado:** `STATE_FETCH`
   - **Ação:** A instrução é carregada no registrador de instrução.

2. **Decode (Decodificação):**
   - A instrução é decodificada para determinar qual operação precisa ser executada. Os operandos e o tipo de operação são identificados.
   - **Ação:** Decodifica a instrução e identifica que é uma operação de CTZ. Define os registradores `rx` e `ry`, e o opcode correspondente.

3. **Execute (Execução):**
   - A operação específica é executada. Para a instrução CTZ, o valor do registrador `ry` é passado para a ULA, que conta o número de bits de valor zero.
   - **Ação:**
     - `selM3 = ry;` // Seleciona o registrador `ry` para a ULA.
     - `OP = opcode;` // Define a operação CTZ na ULA.

4. **Memory Access (Acesso à Memória) [se necessário]:**
   - Nem todas as instruções exigem esta etapa. A instrução CTZ geralmente não precisa acessar a memória, pois é uma operação baseada em registrador.
   - **Ação:** Pode ser ignorada para CTZ.

5. **Write Back (Escrita de Resultado):**
   - O resultado da operação é escrito de volta em um registrador.
   - **Ação:**
     - `LoadReg[rx] = selM2;` // O resultado da ULA (`sULA`) é armazenado em `selM2` e depois carregado no registrador `rx`.
     - `selM2 = sULA;` // Configura `selM2` para o valor resultante da ULA.

6. **Update PC (Atualização do Program Counter):**
   - O `PC` é atualizado para apontar para a próxima instrução.
   - **Estado:** `STATE_FETCH`
   - **Ação:** O estado é configurado para `STATE_FETCH` para buscar a próxima instrução.

A sequência completa dessas etapas garante que a instrução CTZ seja buscada, decodificada, executada e o resultado seja armazenado corretamente. 

Aqui está uma explicação detalhada do que cada linha faz na parte codificada em Linguagem C:

1. **`case CTZ:`**
   - Este é o início do bloco de código que será executado quando a instrução `CTZ` for chamada.

2. **`result = 0;`**
   - Inicializa a variável `result` com 0. Esta variável será usada para contar o número de zeros à direita no número `x`.

3. **`while(x % 2 == 0) {`**
   - Este é o início de um loop `while` que continua enquanto `x` for divisível por 2, ou seja, enquanto o bit menos significativo de `x` for zero. Em termos binários, isso significa que o loop continuará enquanto o último bit de `x` for zero.

4. **`x /= 2;`**
   - Dentro do loop, `x` é dividido por 2. Em termos binários, isso corresponde a deslocar todos os bits de `x` uma posição para a direita. Isso efetivamente remove o bit menos significativo de `x`.

5. **`result++;`**
   - Incrementa a variável `result` em 1 cada vez que `x` é dividido por 2. Isso conta quantas vezes o bit menos significativo de `x` foi zero.

6. **`}`**
   - Fim do loop `while`.

7. **`break;`**
   - Sai do bloco `case` do `switch`, terminando a execução da instrução `CTZ`.

Em resumo, este bloco de código conta o número de zeros consecutivos à direita em um número inteiro `x`. O número de zeros à direita é armazenado na variável `result`. A operação é feita dividindo `x` por 2 repetidamente até que `x` não seja mais divisível por 2, e contando quantas vezes isso é feito.

Este processo é essencialmente equivalente a contar os zeros à direita no número binário de `x`, ou seja, quantos bits de valor zero existem antes do primeiro bit de valor 1 a partir do final do número.
