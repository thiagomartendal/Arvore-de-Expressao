#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>
#include <vector>

typedef struct No {
  std::string valor;
  No *dir{nullptr};
  No *esq{nullptr};
} No;

typedef struct PosicaoParentesis {
  int p1;
  int p2;
} PosicaoParentesis;

class Arvore {
private:
  std::string expressao;
  No *arv{nullptr};
  void exibir(No *no);
  std::vector<PosicaoParentesis> procurarParentesis(std::string exp);
  int procurarUltimoOperador(std::string exp);
  No* formarArvore(std::string &exp);

public:
  Arvore(std::string expressao);
  ~Arvore();
};

#endif
