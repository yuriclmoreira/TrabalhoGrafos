#include "Grafo.h"
#include "Vertices.h"
#include "Agm.h"
#include "Dijkstra.h"
#include "Floyd.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <stack>



Grafo::Grafo(int ordem, bool direcionado, bool pesoArestas, bool pesoVertices){//construtor do grafo
    this->ordem = ordem;//inicializa a ordem com a ordem passada
    this->direcionado = direcionado;//inicializa o grafo se é direcionado ou nao
    this->pesoArestas = pesoArestas;//inicializa o grafo com peso nas arestas ou nao
    this->pesoVertice = pesoVertices;//inicializa o grafo com peso nos vertices ou nao
    this->cont = 0;
}
Grafo::~Grafo(){}

int Grafo::getOrdem(){
    return this->ordem;
}

void Grafo::insereVertice(string nome){// Insere vertice passando id
    if(!existeNome(nome)){//se nao existir o no no grafo
        Vertices* no = new Vertices(this->cont);//aloca um novo no dinamicamente
        nosGrafo.push_back(no);//cria um novo no
        if(this->cont < this->ordem){
            no = procurarNo(cont);
            no->setNome(nome);
            this->nomesGrafo.push_back(nome);
            this->cont++;
        }
        else{
            cout << "Numero de vertices ultrapassa a ordem do grafo." << endl;
        }
    }
}

void Grafo::testaNomes(){
    for (auto i = this->nosGrafo.begin();i!=this->nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um vertice auxiliar
        cout << "id: " << aux->getId() << " nome:" << aux->getNome() << endl; 
    }
}


void Grafo::insereAresta(string nome, string nome_alvo,bool direcionado, float pesoArestas){// Inseri aresta passando id do vertice de origem, vertice alvo, e o peso
    if(!nosGrafo.empty()){//se o grafo nao for vazio
        Vertices* no1;
        Vertices* no2;
        if(existeNome(nome) && existeNome(nome_alvo)){//caso tenha os 2 
            Arestas* auxAresta;//cria uma aresta auxiliar
            if(direcionado == false){//se ela nao for direcionada
                no1 = procurarNome(nome);//cria um vertice auxiliar para alterarmos os dados dos vertices
                no2 = procurarNome(nome_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                auxAresta = no1->insereAresta(no1->getId(), no2->getId(), pesoArestas);//insere aresta no grafo passando o vertice inicial, final e peso
                no1->adicionarGrauSaida();//adiciona 1 ao grau de saida
                no1->adicionarGrauEntrada();//adiciona grau de entrada, ja que nao é direcionado
                //como nao é um grafo direcionado temos que fazer o mesmo para o vertice 2 tambem para adicionarmos a adjacencia
                //Obs: nao é necessario adicionar uma nova aresta se nao teriamos uma multiaresta
                no2->adicionaAdjacencia(no1->getId());//adiciona adjacencia do vertice1 no vertice2
                no2->adicionarGrauEntrada();//adiciona o grau de entrada
                no2->adicionarGrauSaida();//adiciona o grau de saida
                arestasGrafo.push_back(auxAresta);//poe ela na lista de arestas do grafo
                Arestas *arestasContraria = new Arestas(no2->getId(),no1->getId(),pesoArestas);
                arestasGrafo.push_back(arestasContraria);
                
            }
            else if(direcionado == true){//se for direcionada
                no1 = procurarNome(nome);//cria um vertice auxiliar para alterarmos os dados dos vertices
                no2 = procurarNome(nome_alvo);//cria um auxiliar para o vertice alvo igual ao primeiro
                //adicionando peso nos vertices
                auxAresta = no1->insereAresta(no1->getId(), no2->getId(), pesoArestas);//insere aresta no grafo passando o vertice inicial, final e peso
                no1->adicionarGrauSaida();//adiciona 1 ao grau de saida
                no2->adicionarGrauEntrada();//adiciona o grau de entrada
                arestasGrafo.push_back(auxAresta);//poe ela na lista de arestas do grafo
                no2->adicionaAntecessor(no1->getId());
            }
        }
        else if(!existeNome(nome))
        {
            cout<< "o vertice "<<nome<< " nao foi encontrado";
        }
        else if(!existeNome(nome_alvo))
        {
            cout<< "o vertice "<<nome_alvo<< " nao foi encontrado";
        }
        else if(!existeNome(nome) && !existeNome(nome_alvo))
        {
            cout<< "ambos os vertices tanto "<<nome<<" quanto "<<nome_alvo<< " nao foram encontrados";
        }
    }
}

bool Grafo::existeNome(string nome){//procura se existe aquele vertice
     for (auto i = nomesGrafo.begin();i!=nomesGrafo.end();i++){//percorre os vertices do grafo 
        string aux = *i;//cria um auxiliar para conferencia
        //cout << "nome do id inicial: "<<nome << "nome do vertice alvo" << aux << endl;
        if (nome == aux)//se o id do vertice passado for igual
            return true;//retorna que existe o vertice
    }
    return false;//se nao, retorna falso
}

Vertices* Grafo::procurarNome(string nome){
    for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um vertice auxiliar
        if (aux->getNome() == nome)//se o id do vertice passado for igual
            return aux;//retorna o vertice
    }
    return nullptr;//se nao, retorna null
}

void Grafo::removeNode(int id){ //remove vertice
    if(existeVertice(id)){//se o vertice nao existe no grafo entra no if
        for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
            Vertices* aux = *i;//cria um vertice auxiliar
            if (aux->getId() == id)//se o id do vertice passado for igual
                nosGrafo.erase(i);//apaga o no do grafo na posiçao i
        }
    }
}

Vertices* Grafo::procurarNo(int id){//pesquisa vertice no grafo e retorna ele
    for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um vertice auxiliar
        if (aux->getId() == id)//se o id do vertice passado for igual
            return aux;//retorna o vertice
    }
    return nullptr;//se nao, retorna null
}

bool Grafo::existeVertice(int id){//procura se existe aquele vertice
     for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um auxiliar para conferencia
        if (aux->getId() == id)//se o id do vertice passado for igual
            return true;//retorna que existe o vertice
    }
    return false;//se nao, retorna falso
}

bool Grafo::existeVerticeNome(string nome){//procura se existe aquele vertice
     for (auto i = nosGrafo.begin();i!=nosGrafo.end();i++){//percorre os vertices do grafo 
        Vertices* aux = *i;//cria um auxiliar para conferencia
        if (aux->getNome() == nome)//se o id do vertice passado for igual
            return true;//retorna que existe o vertice
    }
    return false;//se nao, retorna falso
}
Arestas* Grafo::existeAresta(int id ,int id_alvo){ // FUNCAO PARA ACHAR UMA ARESTA DADO DOIS VERTICES
    for (auto i = arestasGrafo.begin(); i != arestasGrafo.end(); i++){
        Arestas* verificador = *i;
        if(verificador->getId() == id && verificador->getId_alvo() == id_alvo){
            return verificador;
        }
    }
    cout << "Nao existe essa aresta no grafo." << endl;
    return NULL;
}

void Grafo::arrumaVisitado(){ // Seta visitados para false
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
}

bool Grafo::conexo(){
    for (auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* auxVertice = *i;
        if(auxVertice->ListAdj.empty() == true)
            return false;
    }
    return true;
}

// FUNCAO PARA ACHAR A MENOR ARESTA DENTRE DOIS NOS 
Agm* Grafo::arestaMaisBarata(Vertices* v,Agm* agm, vector<Vertices*> abertos){
    int menor = INT_MAX/2; 
    abertos.push_back(v);
    Arestas* ponteiro = NULL;
    // Percorrengo toda a lista de adj do vertice v
    for(auto j = abertos.begin(); j != abertos.end(); j++)
    {
        Vertices* aSerPercorrido = *j;
        for(auto i = aSerPercorrido->ListAdj.begin(); i != aSerPercorrido->ListAdj.end(); i++){
            int aux = *i; 
            Vertices* proximo = procurarNo(aux);
            if(proximo->getVisitado() == false){
                Arestas* arestaAux = existeAresta(aSerPercorrido->getId(),aux);
                if(arestaAux != NULL){
                    if(arestaAux->getPeso() < menor){
                        menor = arestaAux->getPeso();
                        ponteiro = arestaAux;
                    }
                }
            }
        }

    }
    if(ponteiro != NULL){
        Vertices* verticeVisitado = procurarNo(ponteiro->getId_alvo());
        //verticeVisitado->setVisitado(true);
        if(!v->getVisitado())
        {
            agm->insereVertice(v);
            v->setVisitado(true);
        }
        agm->insereVertice(verticeVisitado);
        verticeVisitado->setVisitado(true);
        agm->insereAresta(ponteiro);
        arestaMaisBarata(verticeVisitado,agm,abertos);
    }
    return agm;
}
Agm* Grafo::arvoreGeradoraMinimaPrim(string v){
    Vertices* aux = procurarNome(v);
    arrumaVisitado();
    vector<Vertices*> abertos;
    Agm *agm = new Agm();             // Criando o conjunto solucao das arestas com menor peso 
    agm = arestaMaisBarata(aux,agm,abertos);// Procurar dentre todos os vizinhos do vertice inicial qual tem aresta com menor peso 
     
    // Percorrendo a lista de adj ate achar o mais barato
    arrumaVisitado();
    return agm;
}


list<int> Grafo::fechoDireto(int ID){
    list<int> listaSolucao;//cria uma lista de soluçao
    Vertices *aux = procurarNo(ID);
    if(this->direcionado == false){
        cout<< "Esse grafo nao eh direcionado, portanto, nao contem fecho transitivo direto"<< endl;
    }
    else if(aux->getGrauSaida() == 0){
        cout << "Vertice nao possue fecho transitivo direto." << endl;
    }
    else
    {
        listaSolucao = fechoDiretoAux(ID,listaSolucao);//chama a funçao auxiliar para fazer de modo recursivo
        list<int>::iterator it;
        cout << endl << "Os vertices que sao alcansaveis a partir do "<< ID << " sao: " << endl;
        for ( it = listaSolucao.begin(); it != listaSolucao.end(); it++){
            
            cout<< *it << " ";
        }
        cout << endl;
    }
    arrumaVisitado();
    return listaSolucao;
}
list<int> Grafo::fechoDiretoAux(int ID, list<int> ListaFechoDireto)//funçao auxiliar recursiva de fecho direto
{
    Vertices* VerticeAux = procurarNo(ID);//procura o vertice com o id passado 
    for (auto i = VerticeAux->ListAdj.begin(); i != VerticeAux->ListAdj.end(); i++)//percorre os ids adjacentes a esse no 
    {
        Vertices* verticeAdj = procurarNo(*i);//variavel com o proximo vertice
        if(verticeAdj->getVisitado()==true)//se o no ja foi visitado
        {
            //nao faz nada
        }
        else//caso nao tenha sido visitado
        {
            verticeAdj->setVisitado(true);//coloque como visitado
            ListaFechoDireto.push_back(verticeAdj->getId());//adiciona na lista soluçao
            ListaFechoDireto = fechoDiretoAux(verticeAdj->getId(),ListaFechoDireto);//entra novamente na recursao
        }
    }
    return ListaFechoDireto;//volta a lista no final
}

list<int> Grafo::fechoIndireto(int ID){
    list<int> solucao;
    Vertices* aux = procurarNo(ID);
    if(this->direcionado == false){
        cout << "Esse grafo nao eh direcionado, portanto, nao contem fecho transitivo indireto"<< endl;
    }
    else if(aux->getGrauEntrada() == 0){
        cout << "Vertice nao possue fecho transitivo indireto." << endl;
    }
    else {
        for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
            Vertices* aux = *i;
            aux->setVisitado(false);
        }

        solucao = fechoIndiretoAux(ID, solucao);
        cout<< endl << "Os vertices que alcansao o vertice "<< ID << " sao: " << endl;
        for (auto i = solucao.begin(); i!=solucao.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }
    arrumaVisitado();
    return solucao;
}
list<int> Grafo::fechoIndiretoAux(int ID, list<int> solucao){
    Vertices* alvo = procurarNo(ID);
    alvo->setVisitado(true);
    for(auto i = alvo->ListAnt.begin(); i != alvo->ListAnt.end(); i++){
        Vertices* verifica = procurarNo(*i);
        if(!verifica->getVisitado()){
            solucao.push_back(*i);
            solucao = fechoIndiretoAux(*i, solucao);
        }
    }
    return solucao;
}


Agm* Grafo::caminhoEmProfundidade(int id){
    Agm* solucao = new Agm();
    int ultimo = -1;
    for(auto i = nosGrafo.begin(); i != nosGrafo.end(); i++){
        Vertices* aux = *i;
        aux->setVisitado(false);
    }
    ultimo = caminhoEmProfundidadeAux(solucao, id, ultimo);
    return solucao;
}
int Grafo::caminhoEmProfundidadeAux(Agm* solucao, int id, int ultimo){
    Vertices* inicial = procurarNo(id);
    solucao->insereVertice(inicial);
    inicial->setVisitado(true);
    int aux;
    cout<<"entrei no: "<<inicial->getNome()<<endl;
    for (auto i = inicial->ListAdj.begin(); i != inicial->ListAdj.end(); i++) {
        aux = *i;
        Vertices* vVisitado = procurarNo(aux);
        cout<< "vvisitado ta como: "<< vVisitado->getNome() <<endl;
        if(!vVisitado->getVisitado()){
            cout<<"entrei na recursao"<<endl;
            ultimo = caminhoEmProfundidadeAux(solucao, aux, ultimo);
        }
        if(i != inicial->ListAdj.begin() && ultimo != -1){
            Vertices* verifica = procurarNo(ultimo);
            cout<< "valor do ultimo: "<<verifica->getNome()<<endl;
            cout<< "entrei aqui"<<endl;
            Arestas *peso = existeAresta(inicial->getId(), ultimo);
            Arestas* retorno = new Arestas(ultimo, inicial->getId(), peso->getPeso());
            solucao->insereAresta(retorno);
            cout<<"inseri a aresta: (" << inicial->getNome() << ", "<< verifica->getNome()<<") "<<endl;
            ultimo = -1;
        }
    }
    ultimo = inicial->getId();
    cout<<"voltei"<<endl;
    return ultimo;
}


list<string> Grafo::caminhoMinimoDijkstra(string nome1, string nome2){
    Dijkstra aux;
    Vertices* noI = procurarNome(nome1);
    Vertices* no_alvo = procurarNome(nome2);
    list<string> caminhoD = aux.caminhoMinimo(this, noI->getId(), no_alvo->getId());
    if(caminhoD.size()>0){
        cout << "Caminho minimo: ";
        for(auto i = caminhoD.begin(); i != caminhoD.end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }
    return caminhoD;
}

void Grafo::caminhoMinimoFloyd(int ID1, int ID2){
    Floyd aux;
    aux.caminhoMinimo(this, ID1, ID2);
}


Agm* Grafo::arvoreGeradoraMinimaKruskal(){
    Agm *agm = new Agm();             // Criando o conjunto solucao das arestas com menor peso
    vector<Arestas*> arestasAux;      // Criando vetor que guarda as arestas
    int *ciclo;
    ciclo = new int [arestasGrafo.size()];
    
    // Atribuindo as arestas do grafo no vetor que sera ordenado 
    for (auto  i = arestasGrafo.begin(); i != arestasGrafo.end(); i++){    
        Arestas* auxs = *i;
        arestasAux.push_back(auxs);
    }    
   
    Arestas* aux = NULL;   

    // Ordenar as arestas conforme o peso
    for(int i  = arestasAux.size() - 1 ;i >= 0 ;i--){
        for(int j = 0;j < i;j++){
            if(arestasAux[j]->getPeso() > arestasAux[j+1]->getPeso()){
                aux = arestasAux[j];
                arestasAux[j] = arestasAux[j + 1];
                arestasAux[j + 1] = aux;    
            }
        }
    }
     
    for (int i = 0;i < arestasAux.size();i++){
        ciclo[i] = i;
    }
    
    
    for (auto  i = arestasAux.begin(); i != arestasAux.end(); i++){
        Arestas*  j       = *i;
        // Detectando se com esta aresta forma ciclo:
		if ( pai(j->getId(), ciclo) != pai(j->getId_alvo(), ciclo)){ 
			unir(j->getId(), j->getId_alvo(), ciclo);

            agm->insereVertice(procurarNo(j->getId()));
            agm->insereVertice(procurarNo(j->getId_alvo()));
            agm->insereAresta(j);       // Insere aresta na arvore agm 
		}
    
    }
    delete[] ciclo;
    return agm;
  
}

// Funcao que uni o pai de dois vertices no ciclo para descobrir se forma ciclo
void Grafo::unir(int v1,int v2, int *ciclo){
    ciclo[pai(v1, ciclo)] = pai(v2, ciclo);
}

int Grafo::pai(int v, int *ciclo){
     if (ciclo[v] == v){
        return v;
	}
 
    ciclo[v] = pai(ciclo[v], ciclo);
 
    return ciclo[v];
}

void Grafo::ordenacaoTopologica(){

    vector<Vertices*> copia;
    copia.reserve(ordem);

    for (auto i = nosGrafo.begin(); i != nosGrafo.end();i++)//copia lista de vertices
        copia.push_back(*i);

    quickSort(&copia, 0, ordem-1); // ordenacao pelo metodo de quiksort com o grau de saido como parametro

    cout << "Vertices ordenados a partir do grau de saida: ";
    for(int i = 0; i < ordem; i++)
        cout << copia[i]->getNome() << " "; //imprime vertices ordenados
    cout << endl;
}

void Grafo::quickSort(vector<Vertices*> *copia, int inicio, int fim){ 
    if(inicio < fim){ // Enquanto posicao de inicio nao ultrapassar final
        int p = partQuick(copia, inicio, fim); // Calcula posicao do pivo
        quickSort(copia, inicio, p - 1); // Recursividade da primeira metade do vetor
        quickSort(copia, p, fim); // Recursividade da segunda metade do vetor
    }
}
int Grafo::partQuick(vector<Vertices*> *copia, int esq, int dir){
    int p = esq + (dir - esq) / 2; // indicado do pivo recebe a metade do vetor como posicao
    Vertices* pivo = copia->at(p); // posiciona pivo utilizando ponteiro
    int i = esq; // Posicao percorrida pela esquerda
    int j = dir; // Posicao percorrida pela direita
    while(i<=j) { // Enquanto esquerda nao ultrapassar direita
        while(copia->at(i)->getGrauSaida() < pivo->getGrauSaida())  // Compara grau de saida de pivo com posicao mais a esquerda
            i++;
        while(copia->at(j)->getGrauSaida() > pivo->getGrauSaida())  // Compara grau de saida de pivo com posicao mais a direita
            j--;
         if(i <= j) { 
            Vertices *aux = copia->at(i); // auxiliar para fazer a troca
            copia->at(i) = copia->at(j);
            copia->at(j) = aux;
            i++;
            j--;
        }
    }
    return i; // Retorna indice para o pivo
}
