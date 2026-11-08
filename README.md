# SHA-256 em C

TDE simples: calcula o hash SHA-256 de textos. Ao iniciar, o programa executa
dois testes (`abc` e `hello world`) e compara os resultados com hashes
conhecidos. Depois permite digitar outro texto.

A saída tem 32 bytes, mostrados como 64 caracteres hexadecimais. A mesma
sequência de bytes sempre produz o mesmo hash. O Enter que encerra a entrada
não faz parte do texto. SHA-256 puro não deve ser usado para armazenar senhas.

## Arquivos

- `main.c`: entrada de texto, dois testes e apresentação do hash.
- `sha256.c` e `sha256.h`: implementação educacional de Brad Conte, com os
  créditos originais preservados.
- `.vscode/`: recomendações de extensões e configuração para executar no Windows.

## Compilar e executar pelo VS Code no Windows

1. Use a extensão [C/C++ Compile Run](https://marketplace.visualstudio.com/items?itemName=danielpinto8zz6.c-cpp-compile-run),
   já instalada neste ambiente. A extensão [C/C++, da Microsoft](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
   fornece sugestões de código e identificação de erros.
2. Abra esta pasta no VS Code. Caso as configurações tenham acabado de mudar,
   pressione **Ctrl+Shift+P** e execute **Developer: Reload Window**.
3. Abra **`main.c`** e pressione **F6**, ou execute o comando
   **C/C++: Compile & Run** pela paleta de comandos.
4. Os dois testes aparecem no terminal. Digite um texto e pressione Enter.

O GCC portátil do [w64devkit 2.11.0](https://github.com/skeeto/w64devkit/releases/tag/v2.11.0)
foi instalado em `%LOCALAPPDATA%\Programs\w64devkit`, fora do repositório.
As extensões não incluem um compilador C: elas acionam esse GCC. O caminho
do compilador e a inclusão de `sha256.c` na compilação estão configurados
em `.vscode/settings.json`. O executável gerado fica em `output/main.exe`.

Se copiar o projeto para outro computador, instale um compilador C e ajuste
`c-cpp-compile-run.c-compiler` para o caminho do seu `gcc.exe`.
As demais configurações de caminho pressupõem w64devkit na pasta indicada.
Não é necessário script Python.

### Erro: Compiler executable not found

Confirme que o `gcc.exe` existe no caminho configurado em
`c-cpp-compile-run.c-compiler`. Essa extensão precisa de barras invertidas
no caminho do Windows; no arquivo JSON, escreva cada barra como `\\`:

```json
"c-cpp-compile-run.c-compiler": "C:\\Users\\dmarc\\AppData\\Local\\Programs\\w64devkit\\bin\\gcc.exe"
```

Em outro computador, substitua pelo caminho real do compilador. Evite usar
`/` nessa configuração: a verificação de caminhos dessa extensão pode não
reconhecer o executável. Depois de alterar, execute **Developer: Reload
Window**, abra `main.c` e pressione **F6**.

## Alternativa: terminal PowerShell

Abra um **novo terminal integrado** do VS Code: o projeto adiciona o GCC
ao Path desse terminal. Na pasta do projeto:

```powershell
gcc -std=c11 -Wall -Wextra main.c sha256.c -o sha256.exe
.\sha256.exe
```

## Fonte da implementação

[Brad Conte — crypto-algorithms](https://github.com/B-Con/crypto-algorithms/tree/cfbde48414baacf51fc7c74f275190881f037d32).
Os arquivos `sha256.c` e `sha256.h` foram obtidos desse commit. O autor
libera o código em domínio público e o apresenta para fins educacionais,
sem garantias: veja o README do projeto original.

Foram feitos pequenos ajustes locais: uso de `string.h`, palavra de 32 bits
com `uint32_t`, conversões sem sinal antes de deslocamentos, índice `size_t`
na leitura dos dados e correção do nome do algoritmo no comentário do cabeçalho.
A interface e os testes em `main.c` foram desenvolvidos para esta atividade.

Especificação do método: [NIST, FIPS 180-4](https://doi.org/10.6028/NIST.FIPS.180-4).
