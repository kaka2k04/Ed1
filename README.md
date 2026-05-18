# TAD Coleção Genérica em C (Cofo)

## 📚 Descrição do Projeto

Este projeto implementa um **TAD Coleção (Cofo)** utilizando um vetor dinâmico de ponteiros genéricos (`void *`), permitindo armazenar qualquer tipo de estrutura em memória.

A coleção foi desenvolvida seguindo os princípios de:

- Genericidade com `void *`
- Gerenciamento manual de memória
- Encapsulamento via TAD
- Manipulação dinâmica de elementos
- Busca e remoção utilizando funções de callback

O sistema utiliza uma estrutura `CD` como exemplo de aplicação prática do Cofo.

---

# 📁 Estrutura dos Arquivos

- `cofo.h` → Protótipos das funções e definição do tipo abstrato
- `cofo.c` → Implementação do TAD Coleção
- `main.c` → Aplicação de teste e interação com o usuário
- `main.exe` → Executável compilado
- `README.md` → Documentação do projeto

---

# ⚙️ Ambiente de Execução

Projeto desenvolvido em:

- Linguagem: C
- Compilador: GCC
- Sistema Operacional: Windows/Linux
- Padrão: C99

---

# 🔨 Comando de Compilação

## Linux / GCC

```bash
gcc Main.c Cofo.c -o main