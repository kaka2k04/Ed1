#ifndef COFO_H
#define COFO_H

  // aqui eu já defino o struct fora do ifdef
  typedef struct cofo Cofo;
  #ifdef COFO_C
    // aqui eu imagino que poderia tirar o extern, mas vou deixar por via das dúvidas
    Cofo *cofCreate(int maxitens);
    int cofInsert(Cofo *c, void *item);
    void *cofQuery(Cofo *c, void *key, int (*cmp)(void *, void *));
    void *cofRemove(Cofo *c, void *key, int (*cmp)(void *, void *));
    int cofEsvaziar(Cofo *c);
    int cofDestroy(Cofo *c);
    void *cofGetFirst(Cofo *c);
    void *cofGetNext(Cofo *c);

  #else

    extern Cofo *cofCreate(int maxItens);
    extern int cofInsert(Cofo *c, void *item);
    extern void *cofQuery(Cofo *c, void *key, int (*cmp)(void *, void *));
    extern void *cofRemove(Cofo *c, void *key, int (*cmp)(void *, void *));
    extern int cofEsvaziar(Cofo *c);
    extern int cofDestroy(Cofo *c);
    extern void *cofGetFirst(Cofo *c);
    extern void *cofGetNext(Cofo *c);
  #endif
#endif