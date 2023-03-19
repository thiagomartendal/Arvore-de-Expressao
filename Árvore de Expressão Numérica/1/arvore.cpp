#include "arvore.h"

Arvore::Arvore(std::string expressao) {
  this->expressao = expressao;
  std::string copia = expressao;
  arv = Arvore::formarArvore(copia);
  Arvore::exibir(arv);
  std::cout << std::endl;
}

Arvore::~Arvore() {
  delete arv;
}

void Arvore::exibir(No *no) {
  std::cout << no->valor << " ";
  if (no->esq != nullptr) {
    Arvore::exibir(no->esq);
  }
  if (no->dir != nullptr) {
    Arvore::exibir(no->dir);
  }
}

std::vector<PosicaoParentesis> Arvore::procurarParentesis(std::string exp) {
  std::vector<PosicaoParentesis> posicoes;
  std::vector<int> pos1;
  for (int i = 0; i < exp.length(); i++) {
    if (exp[i] == '(') {
      pos1.push_back(i);
    }
  }
  std::vector<int> pos2;
  for (int i = 0; i < exp.length(); i++) {
    if (exp[i] == ')') {
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
  return posicoes;
}

int Arvore::procurarUltimoOperador(std::string exp) {
  int ultimo = -1;
  bool numeroNegativo = false;
  for (int i = 0; i < exp.length(); i++) {
    if (exp[i] == '-') {
      if (i == 0) {
        numeroNegativo = true;
        break;
      } else {
        if ((exp[i-1] == '+') || (exp[i-1] == '*') || exp[i-1] == '/') {
          numeroNegativo = true;
          break;
        }
      }
    }
  }
  bool parentesis = false;
  int contParentesis = 0;
  for (int i = 0; i < exp.length(); i++) {
    if ((exp[i] == '+') || ((exp[i] == '-') && (!numeroNegativo))) {
      if (contParentesis == 0) {
        parentesis = false;
        break;
      }
    } else if (exp[i] == '(') {
      contParentesis++;
      parentesis = true;
    } else if (exp[i] == ')') {
      contParentesis--;
    }
  }
  if (((exp.find('+') != std::string::npos) && (!parentesis)) || ((exp.find('-') != std::string::npos) && (!numeroNegativo) && (!parentesis))) {
    int parentesis = 0;
    int parentesisAbertos = 0;
    for (int i = 0; i < exp.length(); i++) {
      if (exp[i] == '(') {
        parentesis++;
      } else if (exp[i] == ')') {
        parentesis--;
      } else if ((exp[i] == '+') && (parentesis == 0)) {
        ultimo = i;
      } else if ((exp[i] == '-') && (parentesis == 0)) {
        if ((exp[i-1] == '+')) {
          ultimo = i-1;
        } else {
          ultimo = i;
        }
      }
    }
  } else {
    if ((exp.find('*') != std::string::npos) || (exp.find('/') != std::string::npos)) {
      for (int i = 0; i < exp.length(); i++) {
        if ((exp[i] == '*') || (exp[i] == '/')) {
          ultimo = i;
        }
      }
    }
  }
  if (ultimo == 0) {
    ultimo = -1;
  }
  return ultimo;
}

No* Arvore::formarArvore(std::string &exp) {
  // std::cout << exp << std::endl;
  std::vector<PosicaoParentesis> posParentesis = Arvore::procurarParentesis(exp);
  for (PosicaoParentesis p: posParentesis) {
    if ((p.p1 == 0) && (p.p2 == (exp.length()-1))) {
      exp.erase(0, 1);
      exp.erase(exp.length()-1, 1);
      break;
    }
  }
  No *no = new No{};
  int ultimo = Arvore::procurarUltimoOperador(exp);
  // std::cout << exp << " " << ultimo << std::endl;
  if (ultimo != -1) {
    char simbolo = exp[ultimo];
    no->valor = std::string(1, simbolo);
    std::string esq = "";
    std::string dir = "";
    for (int i = 0; i < ultimo; i++) {
      esq += exp[i];
    }
    for (int i = ultimo+1; i < exp.length(); i++) {
      dir += exp[i];
    }
    if (esq != "") {
      no->esq = Arvore::formarArvore(esq);
    }
    if (dir != "") {
      no->dir = Arvore::formarArvore(dir);
    }
  } else {
    no->valor = exp;
  }
  return no;
}
