#include <stdio.h>
#include <stdlib.h>

typedef struct sLivro {
  struct sLivro *right;
  struct sLivro *left;
  int codigo;
} Livro;

Livro *criarLivro(int);
Livro *inserir(Livro *, int);
void percorrer(Livro *);
int verificarRemover(Livro*, int);
Livro* verificarFilhosRemover(Livro *);
void limpar(Livro *);
void verificarErro(int);

int main() {
  Livro *root = NULL;
  root = inserir(root, 5);
  // inserir(root, 12);
  // inserir(root, 2);
  // inserir(root, 7);
  // inserir(root, 3);
  // inserir(root, 1);
  // inserir(root, 10);
  // inserir(root, 8);
  // inserir(root, 9);
  // inserir(root, 4);
  // inserir(root, 6);
  // inserir(root, 11);

  percorrer(root);

  verificarErro(verificarRemover(root, 5));
  // verificarErro(verificarRemover(root, 5));

  percorrer(root);
  return 0;
}

Livro *criarLivro(int codigo) {
  Livro *livro = (Livro *)malloc(sizeof(Livro));
  livro->codigo = codigo;
  livro->left = NULL;
  livro->right = NULL;

  return livro;
}

Livro *inserir(Livro *livro, int codigo) {
  if (livro == NULL) {
    return criarLivro(codigo);
  } else {
    if (livro->codigo > codigo) {
      livro->left = inserir(livro->left, codigo);
    } else if(livro-> codigo < codigo) {
      livro->right = inserir(livro->right, codigo);
    }
  }
  return livro;
}

void percorrer(Livro* l){
  if(l!=NULL){
    if(l->left!=NULL){
      percorrer(l->left);
      }
    if(l->right!=NULL){
      percorrer(l->right);
    }
    printf("%i \n", l->codigo);
  }
}

void limpar(Livro * l){
  free(l);
}

int verificarRemover(Livro* l, int codigo){
  if(l==NULL){
      return -1;
  } else if(l->codigo == codigo){ //verifica se o elemento atual é o que deve ser removido
    if(l->right ==NULL && l->left == NULL){ //verifica se tem filhos
      limpar(l);
    } else {
      l = verificarFilhosRemover(l);
    }
  } else if(l->codigo > codigo){
    verificarRemover(l->left,codigo);
  } else if(l->codigo< codigo){
    verificarRemover(l->right,codigo);
  } 
  
  return 0;
}

Livro* verificarFilhosRemover(Livro * l){
  Livro * aux;
   if(l->right != NULL && l->left==NULL){//verifica se tem filho apenas no right
     aux = l->right;
     free(l);
     return aux;
    
    } else if(l->left != NULL && l->right == NULL){//verifica se tem filho apenas no left
      aux = l->left;
      free(l);
      return aux;
   
    } else if(l->left!=NULL && l->right!=NULL){  //verifica se tem filho nos dois
      aux = l->left;
     printf("öi");
      while(aux->right!=NULL){ //busca na sub-arvore da esquerda até achar o mais a direita
        aux = aux->right;
      }
      l = aux;
      Livro * aux2;
      aux2->right = l->right;
      aux2->left = l->left;
      l->right = verificarRemover(l->right, aux->codigo);
      free(l);

     return aux2;
    }
  return aux;
}

void verificarErro(int erro){
  if(erro ==-1){
    printf("Livro não existe\n");
  }
}