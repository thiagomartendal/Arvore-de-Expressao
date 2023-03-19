#include <iostream>
#include "arvore.h"

int main() {
  Arvore arv1 = Arvore("1+2*3/4");
  Arvore arv2 = Arvore("3+((5+9)*2)");
  Arvore arv3 = Arvore("1*2+(3/(4+5)-(6+7))");
  Arvore arv4 = Arvore("(4+5)*(3-2)+(5/3)-1");
  return 0;
}
