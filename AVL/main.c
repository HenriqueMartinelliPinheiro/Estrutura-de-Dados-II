#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo {
  struct sNodo *right;
  struct sNodo *left;
  struct sLivro *livro;
  int height;
} Nodo;

typedef struct sLivro {
  int codigo;
} Livro;

Nodo *criarNodo(int);
Nodo *inserir(Nodo *, int);
void percorrerPosOrdem(Nodo *);
void percorrerPreOrdem(Nodo *);
void percorrerInOrder(Nodo *);
Nodo *verificarRemover(Nodo *, int);
void verificarErro(int);
Livro *criarLivro(int);
Nodo *limpar(Nodo *);
Nodo *verficarFilhos(Nodo *);
Nodo *remover1Filho(Nodo *, Nodo *);
Nodo *verificarFilhos(Nodo *);
Nodo *remover2Filhos(Nodo *, Nodo *);
Nodo* removerTudo(Nodo*);
int maior(int,int);
Nodo * minValueNode( Nodo*);
int getBalance(Nodo *n);
Nodo *leftRotate(Nodo *);
Nodo *rightRotate(Nodo  *);
int height(Nodo *n);
Nodo* verificarRotacao(Nodo*, int);

int main() {
  Nodo *root = NULL;
  root = inserir(root, 5);
  inserir(root, 12);
  inserir(root, 2);
  inserir(root, 7);
  inserir(root, 3);
  inserir(root, 1);
  inserir(root, 3);
  inserir(root, 10);
  inserir(root, 8);
  inserir(root, 9);
  inserir(root, 4);
  inserir(root, 4);
  inserir(root, 6);
  inserir(root, 11);

  percorrerInOrder(root);
  printf("\n\n");
  // root = verificarRemover(root, 12);
  // root = verificarRemover(root, 7);
  // root = verificarRemover(root, 11);
  // root = verificarRemover(root, 2);
  // root = verificarRemover(root, 5);

  percorrerPreOrdem(root);
  // root =  removerTudo(root);
  // percorrerPreOrdem(root);
  return 0;
}

int maior(int a, int b)
{
    return (a > b)? a : b;
}

int height(Nodo *n){
    if (n == NULL)
    return 0;
    return n->height;
}

Nodo *rightRotate(Nodo  *y) {
    Nodo *x = y->left;
    Nodo *aux = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = aux;
 
    // Update heights
    y->height = maior(height(y->left), height(y->right))+1;
    x->height = maior(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}

Nodo *leftRotate(Nodo *x){
    Nodo *y = x->right;
    Nodo *aux = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = aux;
 
    //  Update heights
    x->height = maior(height(x->left), height(x->right))+1;
    y->height = maior(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}

int getBalance(Nodo *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

 Nodo * minValueNode( Nodo* node)
{
     Nodo* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

Nodo *criarNodo(int codigo) { // aloca memória para o nodo
  Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->livro = criarLivro(codigo);
  nodo->left = NULL;
  nodo->right = NULL;
  nodo->height =1;
  return nodo;
}

Livro *criarLivro(int codigo) { // aloca memória para o livro
  Livro *livro = (Livro *)malloc(sizeof(Livro));
  livro->codigo = codigo;
  return livro;
}

Nodo *inserir(Nodo *nodo, int codigo) { // encontra a posição e insere o elemento
  if (nodo == NULL) {
    return criarNodo(codigo);
  } else if(nodo!=NULL){
    if (nodo->livro->codigo > codigo) {
      nodo->left = inserir(nodo->left, codigo);
    } else if (nodo->livro->codigo <= codigo) {
      nodo->right = inserir(nodo->right, codigo);
    }
  } else{
      return nodo;
  }

  nodo->height = 1 + maior(height(nodo->left), height(nodo->right));

  int balance = getBalance(nodo);
  nodo = verificarRotacao(nodo, balance);
  // Left Left Case
   
 
    return nodo;
}

Nodo* verificarRotacao(Nodo* nodo, int balance){
   if (balance > 1 && getBalance(nodo->left) >= 0)
        return rightRotate(nodo);
 
    // Left Right Case
    if (balance > 1 && getBalance(nodo->left) < 0)
    {
        nodo->left =  leftRotate(nodo->left);
        return rightRotate(nodo);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(nodo->right) <= 0)
        return leftRotate(nodo);
 
    // Right Left Case
    if (balance < -1 && getBalance(nodo->right) > 0)
    {
        nodo->right = rightRotate(nodo->right);
        return leftRotate(nodo);
    }
}

void percorrerPreOrdem(Nodo *nodo) {
  if (nodo != NULL) {
    printf("Valor: %i Height: %i \n ", nodo->livro->codigo, nodo->height);
    percorrerPreOrdem(nodo->left);
    percorrerPreOrdem(nodo->right);
  }
}

void percorrerPosOrdem(Nodo *nodo) {
  if (nodo != NULL) {
    percorrerPosOrdem(nodo->left);
    percorrerPosOrdem(nodo->right);
    printf("%i \n ", nodo->livro->codigo);
  }
}

void percorrerInOrder(Nodo *nodo) {
  if (nodo != NULL) {
    percorrerInOrder(nodo->left);
    printf("%i \n ", nodo->livro->codigo);
    percorrerInOrder(nodo->right);
  }
}

Nodo *limpar(Nodo *n) {
  free(n->livro);
  n->livro = NULL;
  free(n);
  n = NULL;
  return n;
}

Nodo *verificarRemover(Nodo *nodo, int codigo) {
  if (nodo == NULL) {
    return NULL;
  } else if (nodo->livro->codigo ==
             codigo) { // verifica se o elemento atual é o que deve ser removido
    nodo = verificarFilhos(nodo);
  } else if (nodo->livro->codigo >
             codigo) { // se não for o elemento a ser removido vai pra esquerda
                       // ou pra direita
    nodo->left = verificarRemover(nodo->left, codigo);
  } else if (nodo->livro->codigo <= codigo) {
    nodo->right = verificarRemover(nodo->right, codigo);
  }
  return nodo;
}

Nodo *verificarFilhos(Nodo *nodo) {
  Nodo *aux;
  if (nodo->right == NULL && nodo->left == NULL) { // verifica se tem filhos
    nodo = limpar(nodo);
    return NULL;
  } else if (nodo->left != NULL && nodo->right != NULL) {
    aux = nodo->left;
    aux = remover2Filhos(nodo, aux);
    return aux;
  } else {
    aux = remover1Filho(nodo, aux);
    return aux;
  }

  return nodo;
}

Nodo *remover2Filhos(Nodo *nodo, Nodo *aux) {
  Nodo *pai = nodo;
  while (aux->right != NULL) { // busca na sub-arvore da esquerda até //
    // achar o mais a direita
    pai = aux;
    aux = aux->right;
  }

  if (pai != nodo) { // encontra o mais a esquerda e o pai dele
    pai->right = aux->left;
    aux->left = nodo->left;
  }

  aux->right = nodo->right;
  nodo = limpar(nodo);
  return aux;
}

Nodo *remover1Filho(Nodo *nodo, Nodo *aux) {
  if (nodo->right != NULL &&
      nodo->left == NULL) { // verifica se tem filho apenas no right
    aux = nodo->right;
    nodo = limpar(nodo);
  } else if (nodo->left != NULL &&
             nodo->right == NULL) { // verifica se tem filho apenas no left
    aux = nodo->left;
    nodo = limpar(nodo);
  }
  return aux;
}

void verificarErro(int erro) {
  if (erro == -1) {
    printf("Livro não existe\n");
  }
}

Nodo* removerTudo(Nodo* root){
  if(root->left !=NULL){
   root->left = removerTudo(root->left);
  }
  if(root->right !=NULL){
   root->right = removerTudo(root->right);
  }
  root = limpar(root);
  return root;
}