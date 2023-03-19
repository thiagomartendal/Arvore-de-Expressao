#include "arvore_expressao.h"

ArvoreExpressao::ArvoreExpressao(std::string expressao) {
  this->expressao = expressao;
  arvore = new Arvore{};
  ArvoreExpressao::procurarParentesis();
  ArvoreExpressao::formarNosParentesis();
  // ArvoreExpressao::formarArvore();
  // while (arvore->dir != nullptr) {
  //   std::cout << arvore->simbolo << " " << arvore->esq->simbolo << std::endl;
  //   arvore = arvore->dir;
  // }
}

ArvoreExpressao::~ArvoreExpressao() {
  delete arvore;
}

void ArvoreExpressao::procurarParentesis() {
  std::vector<int> pos1;
  for (int i = 0; i < expressao.length(); i++) {
    if (expressao[i] == '(') {
      pos1.push_back(i);
    }
  }
  std::vector<int> pos2;
  for (int i = 0; i < expressao.length(); i++) {
    if (expressao[i] == ')') {
      pos2.push_back(i);
    }
  }
  while ((pos1.size() > 0) && (pos2.size() > 0)) {
    int p1 = 0;
    int i1 = 0;
    for (int i = 0; i < pos1.size(); i++) {
      if (pos1[i] >= p1) {
        p1 = pos1[i];
        i1 = i;
      }
    }
    int p2 = 0;
    int i2 = 0;
    for (int i = 0; i < pos2.size(); i++) {
      if (pos2[i] > p1) {
        p2 = pos2[i];
        i2 = i;
        break;
      }
    }
    posicoes.push_back({p1, p2});
    pos1.erase(pos1.begin()+i1);
    pos2.erase(pos2.begin()+i2);
  }
}

void ArvoreExpressao::formarNosParentesis() {
  std::vector<std::string> subExpressoes;
  for (PosicaoParentesis p: posicoes) {
    std::string tmp = "";
    for (int i = p.p1+1; i < p.p2; i++) {
      tmp += expressao[i];
    }
    subExpressoes.push_back(tmp);
  }
  for (std::string exp: subExpressoes) {
    Arvore *arv = new Arvore{};
    Arvore *tmp = arv;
    for (int i = exp.size()-1; i >= 0; i--) {
      if (exp[i-1] == '*') {
        tmp->simbolo = '*';
        tmp->esq = new Arvore{};
        tmp->esq->simbolo = exp[i-2];
        i = i-2;
      } else {
        tmp->simbolo = '.';
        tmp->esq = new Arvore{};
        tmp->esq->simbolo = exp[i];
      }
      tmp->dir = new Arvore{};
      tmp = tmp->dir;
    }
    while (arv->dir != nullptr) {
      std::cout << arv->simbolo << " " << arv->esq->simbolo << std::endl;
      arv = arv->dir;
    }
    delete arv;
  }
}

void ArvoreExpressao::formarArvore() {
  Arvore *tmp = arvore;
  for (int i = expressao.size()-1; i >= 0; i--) {
    if (expressao[i-1] == '*') {
      tmp->simbolo = '*';
      tmp->esq = new Arvore{};
      tmp->esq->simbolo = expressao[i-2];
      i = i-2;
    } else {
      tmp->simbolo = '.';
      tmp->esq = new Arvore{};
      tmp->esq->simbolo = expressao[i];
    }
    tmp->dir = new Arvore{};
    tmp = tmp->dir;
  }
}
