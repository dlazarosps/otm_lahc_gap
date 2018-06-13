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
int DEBUG;
#define TRUE		1
#define FALSE		0
#define ERROR		-1

#define NUM_OPS			3		// Quantidade de operações vizinhos
#define COLS_SWAP		0		// Troca tarefa entre agentes (Coluna)
#define DUO_SWAP		1		// Troca tarefa A => B / B => A
#define GREEDY			2		// Seleciona a de menor custo daquele agente remove a de maior custo

using namespace std;

/* Váriaveis Globais */
int agents;			// i £ I
int tasks;			// j £ J
int **cost; 		// Cij
int **resource;		// Aij
int *capacity;		// Bi

int limit;  		//critério de parada
int listSize; 		//tamanho da lista (t)

int *actualCapacity;	// Bi atual (s)
int *candidateCapacity;	// Bi candidato (s')

int **bestMatrix; 		// Matriz melhor solução de combinações (i x j)
int **actualMatrix; 		// Matriz atual solução de combinações (i x j)
int **candidateMatrix; 	// Matriz candidata solução de combinações (i x j)

int bestSolution;			// Melhor Solução 		(s*)
int actualSolution;			// Solução Atual		(s)
int candidateSolution;		// Solução candidata 	(s')
vector <int> costList;		// Lista de custos		(Lw)

vector <int> indexList;		// Lista de indices das tarefas
int tasksPerAgent;			// média de tarefas por agentes size(tasks/agents)

int interaction; 	// (i)
int listIndex; 		// (v)

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

#define GET_VARIABLE_NAME(Variable) (#Variable)

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

void print_agents(){
	cout << " Agents: " << agents << endl;
	cout << "--------" << endl << endl;
}

void print_tasks(){
	cout << " Tasks: " << tasks << endl;
	cout << "--------" << endl << endl;
}

void print_listSize(){
	cout << " List Size: " << listSize << endl;
	cout << "--------" << endl << endl;
}

void print_limit(){
	cout << " Limit: " << limit << endl;
	cout << "--------" << endl << endl;
}

void print_instance(){
	cout << "Cost: " << endl << endl;
	print_matrix(cost, agents, tasks);
	cout << "--------" << endl << endl;

	cout << "Resource: " << endl << endl;
	print_matrix(resource, agents, tasks);
	cout << "--------" << endl << endl;

	cout << "Capacity: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		cout << capacity[i] << " ";
	}
	cout << endl << "--------" << endl << endl;
}

void print_capacity(){
	cout << "Capacity: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		cout << capacity[i] << " ";
	}
	cout << endl << "--------" << endl << endl;

	cout << "Actual Capacity: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		cout << actualCapacity[i] << " ";
	}
	cout << endl << "--------" << endl << endl;

	cout << "Candidate Capacity: " << endl << endl;
	for (int i = 0; i < agents; ++i)
	{
		cout << candidateCapacity[i] << " ";
	}
	cout << endl << "--------" << endl << endl;

}

void print_best(){
	cout << "bestSolution: " << endl << endl;
	cout << bestSolution << endl;
	cout << "--------" << endl << endl;

	cout << "bestMatrix: " << endl << endl;
	print_matrix(bestMatrix, agents, tasks);
	cout << "--------" << endl << endl;

}

void print_actual(){
	cout << "actualSolution: " << endl << endl;
	cout << actualSolution << endl;
	cout << "--------" << endl << endl;

	cout << "actualMatrix: " << endl << endl;
	print_matrix(actualMatrix, agents, tasks);
	cout << "--------" << endl << endl;

}

void print_candidate(){
	cout << "candidateSolution: " << endl << endl;
	cout << candidateSolution << endl;
	cout << "--------" << endl << endl;

	cout << "candidateMatrix: " << endl << endl;
	print_matrix(candidateMatrix, agents, tasks);
	cout << "--------" << endl << endl;

}

void print_solution(){
	
	cout << "actualSolution: " << endl << endl;
	cout << actualSolution << endl;
	cout << "--------" << endl << endl;

	cout << "candidateSolution: " << endl << endl;
	cout << candidateSolution << endl;
	cout << "--------" << endl << endl;

	cout << "bestSolution: " << endl << endl;
	cout << bestSolution << endl;
	cout << "--------" << endl << endl;
}

/* Função para printar variáveis */
void print_all(){
	
	print_agents();
	print_tasks();
	print_listSize();
	print_limit();
	print_instance();
	print_capacity();
	print_best();
	print_actual();
	print_candidate();


}

/* Função para calcular o custo */
int calc_cost(int **matrix){
	int count = 0;

	for (int i = 0; i < agents; ++i)
	{
		for (int j = 0; j < tasks; ++j)
		{
			if (matrix[i][j] == TRUE)
				count += cost[i][j];
		}
	}

	return count;
}
/* Função para copiar um array para outro */
void copy_capacity(int* from, int* to){
	memcpy(&to, &from, sizeof(from)); 
}

/* Função para inicializar vetor de indices de tarefas */
void init_listIndex(){
	// incrementa indexList de 0 até n (tasks)
	for (int j = 0; j < tasks; ++j)
	{
		indexList.push_back(j);
	}
}

/* Função para copiar bestMatrix para candidateMatrix */
void copy_matrix(int **from, int **to){
	
	memcpy(&to, &from, sizeof(from));
	
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

	// allocate_matrix(actualMatrix, agents, tasks);
	actualMatrix = new int *[agents];
	for (i = 0; i < agents; i++)
		actualMatrix[i] = new int[tasks];

	// allocate_matrix(candidateMatrix, agents, tasks);
	candidateMatrix = new int *[agents];
	for(i = 0; i < agents; i++)
	    candidateMatrix[i] = new int[tasks];

	//aloca capacidade de cada agente
	capacity = new int[agents];
	actualCapacity = new int[agents];
	candidateCapacity = new int[agents];


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
		actualCapacity[i] = stoi(aux);	
		candidateCapacity[i] = stoi(aux);	
	}

	// preenche matriz com zeros
	for (int i = 0; i < agents; ++i)
	{
		for (int j = 0; j < tasks; ++j)
		{
			bestMatrix[i][j] = FALSE;
			actualMatrix[i][j] = FALSE;
			candidateMatrix[i][j] = FALSE;
		}
	}

	init_listIndex();

	tasksPerAgent = tasks/agents;

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

				if (DEBUG) cout << randIndex << " - ";
	
				indexTask = indexList[randIndex]; // pega valor do elemento de indice randomico

				if((actualCapacity[i] - resource[i][indexTask]) >= 0){

					bestMatrix[i][indexTask] = TRUE; //seta tarefa j para o agente i
					actualMatrix[i][indexTask] = TRUE; //seta tarefa j para o agente i
					candidateMatrix[i][indexTask] = TRUE; //seta tarefa j para o agente i

					actualCapacity[i] -= resource[i][indexTask]; //subitrai a capacidade corrente
					candidateCapacity[i] -= resource[i][indexTask]; //subitrai a capacidade corrente

					indexList.erase(indexList.begin() + randIndex); // apaga elemento utilizado da lista

					flag = FALSE; // pula loop
				}
				else{
					flag = TRUE; // caso tenha estourado os recursos repete o procedimento (loop)
				}

			} while (flag); // enquanto seleciona indices aleatórios

			
		}
	}

	if(DEBUG) cout << endl;

	actualSolution = calc_cost(actualMatrix); 	// s = cost (s)
	candidateSolution = actualSolution; 	// s' = cost (s)

}

/* Função que inicializa valores de custo */
void init_costList(){

	costList.reserve(listSize); // aloca lista de custos

	for(int i = 0; i < listSize; i++)
	{
		costList.push_back(bestSolution);
	}
		
}

/* Função que gera vetor com os indices de tarefas do agente */
void list_task(int agent){
	indexList.clear();
	init_listIndex();

	for (int j = 0; j < tasks; j++)
	{
		if (candidateMatrix[agent][j] == FALSE)
		{
			indexList.erase(find(indexList.begin(), indexList.end(), j)); // apaga elemento utilizado da lista
		}
	}
}

void generate_solution(){

	// cout << "TO DO" << endl;
	int agent1, agent2, taskIndex, task1, task2, opRandom, flag; // variaveis locais

	copy_matrix(actualMatrix, candidateMatrix);
	copy_capacity(actualCapacity, candidateCapacity);
	candidateSolution = actualSolution;

	if(DEBUG){
		print_candidate();
		cout << "--------" << endl << endl;
	}

	flag = TRUE;	
	do
	{
		srand(time(NULL));
		opRandom = rand() % NUM_OPS;
		
		srand(time(NULL));
		agent1 = rand() % agents; // indice do agente UM

		list_task(agent1);
		srand(time(NULL));
		taskIndex = rand() % indexList.size();   // indice da tarefa UM
		task1 = indexList[taskIndex];

		srand(time(NULL));
		agent2 = rand() % agents; // indice do agente DOIS
		if(agent1 == agent2){
			if(agent2 == (agents - 1)){
				agent2 = 0;
			}
			else{
				agent2++;
			}
		}

		list_task(agent2);
		srand(time(NULL));
		taskIndex = rand() % indexList.size(); // indice da tarefa UM
		task2 = indexList[taskIndex];


		if(DEBUG){
			cout << "--------" << endl << endl;
			cout << "agent1 " << agent1 << endl;
			cout << "task1 " << task1 << endl;
			cout << "agent2 " << agent2 << endl;
			cout << "task2 " << task2 << endl;
			cout << "opRamdom " << opRandom << endl;
			cout << "--------" << endl << endl;
			opRandom = COLS_SWAP;
		}
		

		switch (opRandom)
		{
		case COLS_SWAP: // Troca tarefa entre agentes (Coluna)

			if(DEBUG) cout << "COLS_SWAP" << endl;

			if (candidateMatrix[agent1][task1] == TRUE){
				if(DEBUG) cout << "candidate" << endl;
				if ((candidateCapacity[agent2] - resource[agent2][task1]) >= 0){
					if(DEBUG) cout << "resource" << endl;
					candidateMatrix[agent1][task1] = FALSE;			   		// seta tarefa do agent1 para FALSE
					candidateCapacity[agent1] += resource[agent1][task1]; 		// add a capacidade corrente

					candidateMatrix[agent2][task1] = TRUE;					// seta tarefa do agent2 para TRUE
					candidateCapacity[agent2] -= resource[agent2][task1]; 		// subtrai a capacidade corrente

					flag = FALSE;
				}
			}
		
			break;

		case DUO_SWAP: // Troca tarefa no mesmo agente (Linha)
			// flag = FALSE;
			break;

		case GREEDY: // Seleciona a de menor custo daquele agente remove a de maior custo
			// flag = FALSE;
			break;

		default:
			break;
		}
	
	} while (flag);

	if(DEBUG) cout << "--------" << endl << endl;

	candidateSolution = calc_cost(candidateMatrix);
}


int main(int argc, char * argv[]){

	if (argc < 3 || argc > 4)
	{
		/*						 ARGV[0]		ARGV[1]	 	ARGV[2]		ARGV[3]					CIN							COUT 			   */
		cerr << " USO CORRETO:	./bin/main 		limit		listSize	[debugflag]	 <	./instances/gapa-X.txt		>	output/OUT.dat " << endl;
		return 0;
	}

	limit = atoi(argv[1]);		// critério de parada
	listSize = atoi(argv[2]);   // tamanho da lista (t)
	DEBUG = atoi(argv[3]);   // tamanho da lista (t)

	parse_instance();

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

	init_solution(); // gera solução inicial aleatória	

	bestSolution = actualSolution; // (s*) = (s)
	
	init_costList(); // preenche lista com o custo de (s)

	interaction = 0; // zera interação (i)

	/* PRINT DEBUG */
	if (DEBUG)
	{
		print_all();
	}
	
	print_solution();


	for(int i = 0; i < limit; i++)
	
	{
		if(DEBUG) cout << "for " << endl;
		generate_solution();

		listIndex = interaction % listSize; // (v)

		if ((candidateSolution <= costList[listIndex]) || (candidateSolution <= actualSolution) ) {

			if(DEBUG) cout << "IF s' <= s " << endl;
			
			actualSolution = candidateSolution;
			copy_matrix(candidateMatrix, actualMatrix);
			copy_capacity(candidateCapacity, actualCapacity);
			
			if (actualSolution <= bestSolution) {
				if(DEBUG) cout << "IF s <= s* " << endl;
				bestSolution = actualSolution;
				copy_matrix(actualMatrix, bestMatrix);
			}
			
		} 

		costList.pop_back(); // remove ultimo da lista
		costList.insert(costList.begin(), bestSolution); // insere na frente
		
		interaction++;

		if(DEBUG) cout << "--------" << endl << endl;
	}

	print_solution();
	
	return 0;
}