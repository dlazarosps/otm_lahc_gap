#include <algorithm>    // std::copy
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <stdlib.h>
#include <vector>

#include <bits/stdc++.h>

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


int *currentCapacity;	// Bi corrente
int **bestMatrix; 		// Matriz melhor solução de combinações (i x j)
int **candidateMatrix; 	// Matriz candidata solução de combinações (i x j)

int bestSolution;			// Melhor Solução 		(s*)
int actualSolution;			// Solução Atual		(s)
int candidateSolution;		// Solução candidata 	(s')
vector <int> costList;		// Lista de custos		(Lw)

vector <int> indexList;		// Lista de indices das tarefas
int tasksPerAgent;			// média de tarefas por agentes size(tasks/agents)


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
	cout << "--------" << endl << endl;
	
	cout << " List Size: " << listsize << endl;
	cout << " Limit: " << limit << endl;
	cout << "--------" << endl << endl;

	cout << "Cost: " << endl << endl;
	print_matrix(cost, agents, tasks);
	cout << "--------" << endl << endl;

	cout << "Resource: " << endl << endl;
	print_matrix(resource, agents, tasks);
	cout << "--------" << endl << endl;

	cout << "Capacity: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		cout << capacity[i] << endl;
	}
	cout << "--------" << endl << endl;

	cout << "Current Capacity: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		cout << currentCapacity[i] << endl;
	}
	cout << "--------" << endl << endl;

	int count = 0;
	cout << "Current Cost: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		for (int j = 0; j < tasks; ++j)
		{
			if(bestMatrix[i][j] == TRUE)
				count += cost[i][j];
		}
	}
	cout << count << endl  << "--------" << endl << endl;

	cout << "Binary: " << endl << endl;
	print_matrix(bestMatrix, agents, tasks);
	cout << "--------" << endl << endl;
	
	cout << "index list (" << indexList.size() << "): " << endl << endl;
	for (int i = 0; i < tasks; ++i)
	{
		cout << indexList[i] << " ";
	}
	cout << endl << "--------" << endl << endl;
}

/* Função para resetar capacidade corrente com valores da capacidade original */
void reset_capacity(){
	memcpy(&currentCapacity, &capacity, sizeof(capacity)); 
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

	// allocate_matrix(bestMatrix, agents, tasks);
	bestMatrix = new int *[agents];
	for(i = 0; i < agents; i++)
	    bestMatrix[i] = new int[tasks];

	// allocate_matrix(candidateMatrix, agents, tasks);
	candidateMatrix = new int *[agents];
	for(i = 0; i < agents; i++)
	    candidateMatrix[i] = new int[tasks];

	//aloca capacidade de cada agente
	capacity = new int[agents];
	currentCapacity = new int[agents];


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

	// preenche matriz com zeros
	for (int i = 0; i < agents; ++i)
	{
		for (int j = 0; j < tasks; ++j)
		{
			bestMatrix[i][j] = FALSE;
			candidateMatrix[i][j] = FALSE;
		}
	}

	// incrementa indexList de 0 até n (tasks)
	for (int j = 0; j < tasks; ++j)
	{
		indexList.push_back(j);
	}

	tasksPerAgent = tasks/agents;

	reset_capacity(); //seta valores da capacidade currente
}

/* Função para gerar solução inicial randomica */
void init_solution(){

	int flag = FALSE;
	int randIndex;
	int indexTask;

	for (int i = 0; i < agents; ++i)
	{
		for (int j = 0; j < tasksPerAgent; ++j)
		{
			do
			{
				srand(time(NULL)); // gera semente randomica

				randIndex = rand() % indexList.size(); // seleciona indice randomico das tarefas

				if (DEBUG) cout << randIndex << endl;
	
				indexTask = indexList[randIndex]; // pega valor do elemento de indice randomico

				if((currentCapacity[i] - resource[i][indexTask]) >= 0){

					bestMatrix[i][indexTask] = TRUE; //seta tarefa j para o agente i
					currentCapacity[i] -= resource[i][indexTask]; //subitrai a capacidade corrente

					indexList.erase(indexList.begin() + randIndex); // apaga elemento utilizado da lista

					flag = FALSE; // pula loop
				}
				else{
					flag = TRUE; // caso tenha estourado os recursos repete o procedimento (loop)
				}

			} while (flag); // enquanto seleciona indices aleatórios

			
		}
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

	parse_instance();

	costList.reserve(listsize); 	// aloca lista de custos
	
	init_solution(); // gera solução inicial aleatória

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