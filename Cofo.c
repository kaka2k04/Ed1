#include <stdlib.h>
#include "cofo.h"
#define TRUE 1
#define FALSE 0

// cria a struct cofo aqui pra fazer o typedef só no cofo.h
struct cofo {
  int maxItens;
  int numItens;
  void **elm;
  int cur;
};

// função de criar cofo de acordo com o que foi trabalhado em sala
Cofo *cofCreate(int maxItens)
{
  if (maxItens > 0) {
    Cofo *c = (Cofo *)malloc(sizeof(Cofo));
    if (c != NULL) {
      c->elm = (void **)malloc(sizeof(void *) * maxItens);
      if (c->elm != NULL) {
        c->maxItens = maxItens;
        c->numItens = 0;
        c->cur = -1;
        return c;
      }
      free(c);
    }
  }
  return NULL;
}

// se ele estiver vazio dá free em tudo
int cofDestroy(Cofo *c)
{
  if (c != NULL) {
    if (c->numItens <= 0) {
      free(c->elm);
      free(c);
      return TRUE;
    }
  }
  return FALSE;
}

// insere se tiver espaço
int cofInsert(Cofo *c, void *item)
{
  if (c != NULL) {
    if (c->numItens < c->maxItens) {
      c->elm[c->numItens] = item;
      c->numItens++;
      return TRUE;
    }
  }
  return FALSE;
}

// função de consulta diferente da do slide pq tava dando problema na hora de encontrar
void *cofQuery(Cofo *c, void *key, int (*cmp)(void *, void *))
{
  int i;
  if (c != NULL && key != NULL && cmp != NULL) {
    for (i = 0; i < c->numItens; i++) {
      if (cmp(c->elm[i], key) == TRUE) {
        return c->elm[i];
      }
    }
  }
  return NULL;
}

// como a de remove é bem similar a de consulta, teve que ser modificada também
void *cofRemove(Cofo *c, void *key, int (*cmp)(void *, void *))
{
  int i, j;
  void *data; 
  if (c != NULL && key != NULL && cmp != NULL) {
    if (c->numItens > 0) {
      for (i = 0; i < c->numItens; i++) {
        if (cmp(c->elm[i], key) == TRUE) {
          data = c->elm[i];
          for (j = i; j < c->numItens - 1; j++) {
            c->elm[j] = c->elm[j + 1];
          }
          c->numItens--;
          return data;
        }
      }
    }
  }
  return NULL;
}


// esvazia cada elemento do vetor, depois disso zera o numero de itens
int cofEsvaziar(Cofo *c) {
  int i;
  if (c != NULL) {
    if (c->numItens > 0) {
      for (i = 0; i < c->numItens; i++) {
        if (c->elm[i] != NULL) {
          free(c->elm[i]);
        }
      }
      c->numItens = 0;
      return TRUE;
    }
  }
  return FALSE;
}

// padrão de acordo com o material
void *cofGetFirst(Cofo *c)
{
  if (c != NULL) {
    if (c->numItens > 0) {
      c->cur = 0;
      return c->elm[c->cur];
    }
  }
  return NULL;
}

// também no mesmo modelo das aulas e do slide
void *cofGetNext(Cofo *c)
{
  if (c != NULL) {
    if (c->numItens > 0) {
      if (c->cur < c->numItens - 1) {
        c->cur++;
        return c->elm[c->cur];
      }
    }
  }
  return NULL;
}