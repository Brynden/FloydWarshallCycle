#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999
void floydWarshall(int V, int graph[V][V]);
void iniciarMatriz(int V, int matriz[V][V]);
void mostrarMatriz(int V, int matriz[V][V]);
void llenarMatriz(int V, int matriz[V][V], float prob);
int cuentaAdyacente(int vertice[], int V);
int verticeAdyacente(int V, int vertices[]);
int clean_stdin();



int main()
{
	int V=128;
	char c;
	float prob=0.2;
	int matriz[V][V];
	iniciarMatriz(V, matriz);
	llenarMatriz(V, matriz, prob);


	if (V < 33)
	{
		printf("\n\n La matriz de adyacencia del grafo es: \n\n");
		mostrarMatriz(V, matriz);
	}

	clock_t start, end;
	double cpu_time_used;
	
    start = clock();
	floydWarshall(V, matriz);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	

	
	printf("\nSe encontro matriz dist min en %lf segundos \n", cpu_time_used);
	
	return 0;
}

/*
 * Iniciliza una matriz VxV de ceros
 */
void iniciarMatriz(int V, int matriz[V][V])
{
	int i, j;
	for (i = 0; i < V; i++)
	{
		for (j = 0; j < V; j++)
			matriz[i][j] = 0;
	}

}


/*
 * Funcion para mostrar la matriz en pantalla
 */
void mostrarMatriz(int V, int matriz[V][V])
{
	int i, j;
	for (i = 0; i < V; i++)
	{
		printf("\t");
		for (j = 0; j < V; j++) {
			if (matriz[i][j] == INF)
				printf("%7s", "INF");
			else
				printf("%7d", matriz[i][j]);
		}
		printf("\n");
	}
}

void floydWarshall(int V, int graph[V][V])
{
	/* dist[][] will be the output matrix that will finally have the shortest
      distances between every pair of vertices */
	int dist[V][V], temp[V], actual, i, j, k, min = INF, vertice1, vertice2, vertice3;

	/* Initialize the solution matrix same as input graph matrix. Or
       we can say the initial values of shortest distances are based
       on shortest paths considering no intermediate vertex. */


	for (actual = 0; actual < V; ++actual) {
		for (i = 0; i < V; ++i) {
			for (j = 0; j < V; ++j) {
				if (graph[i][j] == 1 && i != actual && j != actual)
					dist[i][j] = graph[i][j];
				else
					dist[i][j] = INF;
			}
		}

		for (k = 0; k < V; ++k) {
			// Pick all vertices as source one by one
			if (k != actual) {
				for (i = 0; i < V; ++i) {
					// Pick all vertices as destination for the
					// above picked source
					if (i != actual) {
						for (j = 0; j < V; ++j) {
							// If vertex k is on the shortest path from
							// i to j, then update the value of dist[i][j]
							if (j != actual) {
								if (dist[i][k] + dist[k][j] < dist[i][j])
									dist[i][j] = dist[i][k] + dist[k][j];
							}
						}
					}
				}
			}
		}
		for (i = 0; i < V; ++i) {
			if (graph[actual][i] == 1) {
				for (j = i + 1; j < V; ++j) {
					if (graph[actual][j] == 1) {
						if (dist[i][j] < min) {
							min = dist[i][j];
							vertice1 = actual;
							vertice2 = i;
							vertice3 = j;
						}
					}
				}
			}
		}
	}
	if (min == INF)
		printf("no hay ciclo\n");
	else
		printf("distancia minima = %d, conectado, %d, %d, %d \n", min+2, vertice1, vertice2, vertice3);
	// Print the shortest distance matrix
}

/*
 * Completa el grafo no-dirigido
 * agregando cada arista con una probabilidad determinada
 * por parametro prob
 * la arista (a, a+1) ya existe y no se considera al igual
 * que la arista lazo (a, a)
 */
void llenarMatriz(int V, int matriz[V][V], float prob)
{
	int i, j;
	float aleatorio;
	for (i = 0; i < V; i++)
		for (j = i+1; j < V; j++)
		{
			aleatorio = ((double) rand() / (RAND_MAX));
			if (aleatorio < prob)
			{
				matriz[i][j] = 1;
				matriz[j][i] = 1;
			}
		}
}


/*
 * Cuenta la cantidad de vertices adyacentes a un vertice determinado
 */
int cuentaAdyacente(int vertice[], int V)
{
	int i, vecino=0;
	for (i = 0; i < V; i++)
		if (vertice[i] == 1)
			vecino++;
	return vecino;
}


/*
 * Devuelve el primer vertice adyacente a un vertice determinado
 */
int verticeAdyacente(int V, int vertices[])
{
	int i;
	for (i = 0; i < V; i++)
		if (vertices[i] == 1)
			return i;
	return -1;
}



// verificar ingreso correcto de datos
int clean_stdin()
{
	while (getchar()!='\n');
	return 1;
}