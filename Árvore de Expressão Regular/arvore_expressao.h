#ifndef ARVORE_EXPRESSAO_H
#define ARVORE_EXPRESSAO_H

#include <iostream>
#include <string>
#include <vector>

typedef struct Arvore {
  char simbolo;
  Arvore *dir{nullptr};
  Arvore *esq{nullptr};
} Arvore;

typedef struct PosicaoParentesis {
  int p1;
  int p2;
} PosicaoParentesis;

class ArvoreExpressao {
private:
  std::string expressao;
  std::vector<PosicaoParentesis> posicoes;
  Arvore *arvore{nullptr};
  void procurarParentesis();
  void formarNosParentesis();
  void formarArvore();

public:
  ArvoreExpressao(std::string expressao);
  ~ArvoreExpressao();
};

#endif
