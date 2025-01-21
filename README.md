# Gerador e Leitor de Código de Barras EAN-8

Este projeto consiste em um arquivo `generate.c` gerador de códigos de barra EAN-8 em arquivo `.pbm` que pode ser configurado com diferentes parâmetros de espaçamento, largura, altura do código de barras e nome do arquivo. Ele também valida o código EAN-8 fornecido, garantindo que o código esteja correto antes de gerá-lo.

Em paralelo, o arquivo `extract.c` funciona como leitor de código de barras EAN-8, recebendo como parâmetro um arquivo `.pbm` e analisando seu código de barras para extrair em seguida seu código EAN-8.

## Requisitos

- Compilador C (`gcc`, Clang, etc.)
- Sistema operacional baseado em Unix (Linux, macOS) ou Windows
- Ferramenta de automação `make`
- Bibliotecas padrão C (`stdio.h`, `stdlib.h` etc.)

## Compilação

1. Clone o repositório em sua máquina ou baixe os arquivos do código.
2. Compile o programa com o arquivo Makefile usando o comando:

```
make
```
 Opcional: Após execução poderá apagar todos os arquivos usados na compilação utilizando o comando:

```
make clean
```

OBS: Os arquivos gerenciadores do jogo são baseados em código binário em Linux, caso o sistema operacional não consiga executar (Windows por exemplo), poderá usar WSL.

## Execução
Para rodar o programa de geração de código de barras use o seguinte formato:

```
./generate <identificador> [espacamento_lateral(Opcional)] [quantidade_pixels_area(Opcional)] [altura_barras(Opcional)] [nome_imagem.pbm(opcional)]
```

**Parâmetros:**
- `<identificador>`: O identificador de 8 dígitos (EAN-8) que será utilizado para gerar o código de barras.
- `[espacamento_lateral]`: O valor do espaçamento lateral (opcional, padrão é 4).
- `[quantidade_pixels_area]`: O valor de pixels para cada área da barra de códigos (opcional, padrão é 3).
- `[altura_barras]`: A altura do código de barras em pixels (opcional, padrão é 50).
- `[nome_imagem.pbm]`: O nome do arquivo onde o código de barras será salvo. Deve ter a extensão `.pbm` (Opcional, padrão ée `codigo_de_barras.pbm`).

Exemplo:

```
./generate 23456785 2 4 20 teste.pbm
```

### Validações
1. **Identificador**: O programa verifica se o identificador fornecido possui exatamente 8 dígitos numéricos e se o oitavo dígito verificador condiz com a verificação dos sete dígitos anteriores.
2. **Extensão do arquivo**: O arquivo de saída deve ter extensão `.pbm`, caso contrário, o programa exibirá uma mensagem de erro.
3. **Verificação de arquivo existente**: Se o arquivo de saída já existir, o programa perguntará se deseja sobrescrevê-lo.

### Exemplo de saída

O arquivo `.pbm` gerado será uma imagem binária de cabeçalho P1 e segunda linha informando a largura e altura da imagem em pixels (pode ser visualizada com ferramentas que suportam o formato `.pbm`).

Para rodar o programa de leitura de código de barras use o seguinte formato:

```
./extract <nome_imagem.pbm>
```

**Parâmetro:**
- `<nome_imagem.pbm>`: O nome do arquivo onde o código de barras está salvo. Deve haver extensão `.pbm`.

Exemplo:

```
./extract codigo_de_barras.pbm
```
### Validações
1. **Existência de arquivo**: Caso o arquivo não existir, o programa exibirá uma mensagem de erro.
2. **Extensão de arquivo**: Caso o arquivo existir mas não possuir a extensão exigida, o programa exibirá uma mensagem de erro.
3. **Cabeçalho**: Caso o arquivo seja um `.pbm` mas não possuir formato de código de barras ou não houver cabeçalho, o programa exibirá uma mensagem de erro.
4. **Dígito verificador**: Caso o código de barras seja lido mas o dígito verificador for inválido, o programa exibirá uma mensagem de erro.

### Exemplo de saída

```
O identificador do código de barras é: 23456785.
```

### Estrutura de arquivos

- `resources`: Pasta que contêm o arquivo de cabeçalho `definitions.h` e arquivos de funções `.c`.

   - `analisarcodigo.c`: Arquivo de implementação de funções auxiliares que analisam e manipulam a linha de código de barras.
  
   - `analisepbm.c`: Arquivo de implementação de funções auxiliares que analisam o arquivo `.pbm`.

   - `definitions.h`: Arquivo de cabeçalho contendo assinaturas das funções, includes comuns de bibliotecas, definições de constantes globais e o Struct da tabela L/R-code.

   - `manipularpbm.c`: Arquivo de implementação de funções auxiliares que manipulam o arquivo `.pbm`.

   - `tabelalr.c`: Arquivo de implementação da variável global `codes` de tipo `DigitCode`, Struct declarado em `definitions.h`, definindo a tabela L/R-code.

   - `verificador.c`: Arquivo de implementação de funções auxiliares que analisam e calculam o dígito verificador EAN-8.

- `.gitignore`: Arquivo declarando arquivos "lixo" que não irão aparecem no repositório.

- `extract.c`: Arquivo em que há a função `main` da funcionalidade de leitura de arquivo `.pbm`.

- `generate.c`: Arquivo em que há a função `main` da funcionalidade de geração de arquivo `.pbm`.

- `Makefile`: Arquivo de automação de compilação e delete de arquivos compilados.
