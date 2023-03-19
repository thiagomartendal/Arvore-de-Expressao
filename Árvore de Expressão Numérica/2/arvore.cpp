#include "arvore.h"

Arvore::Arvore(std::string expressao) {
  this->expressao = expressao;
}

Arvore::~Arvore() {
  delete arv;
}

std::vector<Posicao> Arvore::procurarPosicaoParentesis(std::string exp) {
  std::vector<Posicao> posicoes;
  std::vector<int> posicoesMarcadas;
  std::size_t totalParentesisAbertos = std::count(exp.begin(), exp.end(), '(');
  while (totalParentesisAbertos > 0) {
    int totalParentesis = 0;
    int p1, p2;
    for (int i = 0; i < exp.size(); i++) {
      bool posicaoMarcada = (std::find(posicoesMarcadas.begin(), posicoesMarcadas.end(), i) != posicoesMarcadas.end());
      if (exp[i] == '(') {
        if (!posicaoMarcada) {
          if (totalParentesis == 0) {
            p1 = i;
            posicoesMarcadas.push_back(i);
          }
          totalParentesis++;
        }
      } else if (exp[i] == ')') {
        if (!posicaoMarcada) {
          totalParentesis--;
          if (totalParentesis == 0) {
            p2 = i;
            posicoesMarcadas.push_back(i);
            posicoes.push_back({p1, p2});
          }
        }
      }
    }
    totalParentesisAbertos--;
  }
  return posicoes;
}

int Arvore::procurarUltimoOperador(std::string exp) {
  int ultimo = -1;
  std::vector<Posicao> posicoes = Arvore::procurarPosicaoParentesis(exp);
  for (Posicao p: posicoes) {
    if ((p.p1 == 0) && (p.p2 == exp.length()-1)) {
      exp.erease(0, 1);
      exp.erease(exp.length()-1, 1);
    }
  }
  posicoes = Arvore::procurarPosicaoParentesis(exp);
  for (int i = 0; i < exo; i++) {
    for (Posicao p: posicoes) {
      if ((i > p.p1) && (i < p.p2)) {
        // Inválido
      } else {
        // Válido
      }
    }
  }
}
