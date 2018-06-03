#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include <algorithm>    // std::copy

/* Constantes */
#define DEBUG		1
#define TRUE		1
#define FALSE		0
#define ERROR		-1

using namespace std;

/* Váriaveis Globais */
int agents;			// i £ I
int tasks;			// j £ J
int **cost; 		// Cij
int **resource;		// Aij
int *capacity;		// Bi

int bestSolution;			// Melhor Solução 	(s*)
int actualSolution;			// Solução Atual	(s)
int candidateSolution;		// Solução Atual	(s')
int *costList;				// Lista de custos	(Lw)


/* Função para alocar dinamicamente matrizes 2D */
/*
//ERRO falha de segmentação parâmetro matrix
void allocate_matrix(int **matrix, int rows, int cols){ 
	int i;
	matrix = new int *[rows];
	for(i = 0; i < rows; i++)
	    matrix[i] = new int[cols];

}
*/

/* Função para printar matrizes */
void print_matrix(int **matrix, int rows, int cols){
	int i, j;

	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < cols; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
		cout << endl;
	}
}

void print_all(int limit, int listsize){

	cout << " Agents: " << agents << endl;
	cout << " Tasks: " << tasks << endl;
	
	cout << " List Size: " << listsize << endl;
	cout << " Limit: " << limit << endl;

	cout << "Cost: " << endl << endl;
	print_matrix(cost, agents, tasks);

	cout << "Resource: " << endl << endl;
	print_matrix(resource, agents, tasks);

	for (int i = 0; i < agents; ++i)
	{
		cout << capacity[i] << endl;
	}

}

/* Funcão de leitura do arquivo input de instancias usando std::cin */
void parse_instance(){ 
	int i, j;
	string aux;

	cin >> aux;
	agents = stoi(aux);		// número de agentes
	cin >> aux;
	tasks = stoi(aux);		// número de tarefas

	// allocate_matrix(cost, agents, tasks);
	cost = new int *[agents];
	for(i = 0; i < agents; i++)
	    cost[i] = new int[tasks];

	// allocate_matrix(resource, agents, tasks);
	resource = new int *[agents];
	for(i = 0; i < agents; i++)
	    resource[i] = new int[tasks];

	//aloca capacidade de cada agente
	capacity = new int[agents];

	// preenche matrix de custos
	for (i = 0; i < agents; ++i) 
	{
		for (j = 0; j < tasks; ++j)
		{
			cin >> aux;
			cost[i][j] = stoi(aux);
		}
	}

	// preenche matrix de recursos consumidos
	for (i = 0; i < agents; ++i)
	{
		for (j = 0; j < tasks; ++j)
		{
			cin >> aux;
			resource[i][j] = stoi(aux);
		}
	}

	// preenche lista de capacidade
	for (i = 0; i < agents; ++i)
	{
		cin >> aux;
		capacity[i] = stoi(aux);	
	}

}

int main(int argc, char * argv[]){

	if (argc != 3)
	{
		/*						 ARGV[0]		ARGV[1]	 	ARGV[2]					CIN							COUT 			   */
		cerr << " USO CORRETO:	./bin/main 		limit		listsize	<	./instances/gapa-X.txt		>	output/OUT.dat " << endl;
		return 0;
	}

	int limit = atoi(argv[1]); 		// critério de parada
	int listsize = atoi(argv[2]); 	// tamanho da lista (t)

	// costList = new int[listsize]; 	// aloca lista de custos

	parse_instance();

	/* PRINT DEBUG */
	if (DEBUG)
	{
		print_all(limit, listsize);
	}
	

	/*** LAHC ***/
	/*
	* 	Gera solução inicial (s)
	* 	Atribui melhor solução com o valor da solução inicial (s*) = (s) 
	* 	Preenche lista (Lw) com o Custo (s)
	*	Zera iteração (i) = 0
	*	ENQUANTO numero de iterações (i) for menor que (<) critério de parada (limit)
	*		Gera solução candiata (s')
	*		Atribui indice lista  (v) =  (i) mod (t)
	*		SE Custo (s') <= Custo na lista (Lv) OU Custo (s') <= Custo (s)
	*			Atribui (s) = (s')
	*			SE (s) < (s*)
	*				Atribui (s*) = (s)
	*		Atribui Custo na lista (Lv) = Custo (s)
	*		Incrementa interação (i++)
	*	Retorna (s*)
	*/

	return 0;
}