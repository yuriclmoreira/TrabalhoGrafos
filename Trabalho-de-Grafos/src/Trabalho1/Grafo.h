#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "Vertices.h"
#include "Agm.h"
#include <list>
#include <vector>

class Dijkstra;
class Floyd;

class Grafo{
    //atributos
    private:
    int ordem; //ordem do grafo
    bool direcionado; //direcionado ou nao
    bool pesoArestas; //peso nas arestas
    bool pesoVertice; //peso nos vertices


    public:
    
    Grafo(int ordem, bool direcionado = false, bool pesoArestas= false, bool pesoVertices = false);
    ~Grafo();

    void insereVertice(int id); // Insere vertice no grafo 
    void insereAresta(int id,int id_alvo,bool direcionado = false ,float pesoArestas = 0); // Insere aresta no grafo
    void removeNode(int id); // Remove vertice do grafo
    bool existeVertice(int id); // Procura vertice no grafo
    Arestas* existeAresta(int id ,int id_alvo); //retorna aresta se existir
    Vertices* procurarNo(int id); //retorna vertice se existir
    
    std::list<Arestas*> arestasGrafo; // lista com arestas do grafo       
    std::list<Vertices*> nosGrafo; //lista com nos do grafo            
    
    int getOrdem(); //retorna ordem do grafo
    bool conexo(); // verifica se grafo eh conexo
    void arrumaVisitado(); // seta todos vertices.visitado como false 
    
    Agm* arestaMaisBarata(Vertices* v,Agm* agm);  
    list<int> fechoDireto(int ID);//funçao para achar o fecho transitivo direto
    list<int> fechoDiretoAux(int ID, list<int> ListaFechoDireto); //auxiliar para recursividade do fecho
    list<int> fechoIndireto(int ID);//achar o fecho transitivo indireto
    list<int> fechoIndiretoAux(int ID, list<int> listaFechoIndireto);//achar o fecho transitivo indireto
    list<int> caminhoMinimoDijkstra(int ID1, int ID2);//caminho minimo entre v1 e v2 passados por parametro usando Dijkstra
    void caminhoMinimoFloyd(int ID1, int ID2); // custo minimo entre v1 e v2 passados por parametro usando floyd
    Agm* arvoreGeradoraMinimaPrim(int v);//cria uma arvore geradora minima usando prim
    Agm* caminhoEmProfundidade(int id);//caminha em profundidade pelo grafo
    int caminhoEmProfundidadeAux(Agm* solucao, int id, int ultimo);//aux do caminha em profundidade pelo grafo
    void ordenacaoTopologica();//faz a ordenaçao topologica do grafo
    void quickSort(vector<Vertices*> *copia, int inicio, int fim); // ordenacao pelo metodo de quicksort
    int partQuick(vector<Vertices*> *copia, int inicio, int fim); // aux do quicksort
    Agm* arvoreGeradoraMinimaKruskal();//cria uma arvore geradora minima usando kruskal
    void unir(int v1,int v2, int *ciclo); // Usado para verificar ciclos
    int pai(int v, int *ciclo); // Usado para verificar ciclos
};

#endif //GRAFO_H_INCLUDED