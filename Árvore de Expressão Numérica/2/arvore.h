#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

typedef struct No {
  std::string valor;
  No *dir{nullptr};
  No *esq{nullptr};
} No;

typedef struct Posicao {
  int p1;
  int p2;
} Posicao;

class Arvore {
private:
  std::string expressao;
  No *arv{nullptr};
  std::vector<Posicao> procurarPosicaoParentesis(std::string exp);
  int procurarUltimoOperador(std::string exp);

public:
  Arvore(std::string expressao);
  ~Arvore();
};

#endif
