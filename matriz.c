#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 9999

int floydWarshall(int V, int matriz[V][V]);
void iniciarMatriz(int V, int matriz[V][V]);
void mostrarMatriz(int V, int matriz[V][V]);
void llenarMatriz(int V, int matriz[V][V], float prob);
int clean_stdin();



int main()
{
	int V=512;
	float prob = 20 /(float) V;
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

/* adaptacion de algoritmo de Floyd-Warshall
 * encuentra ciclo minimo iterando para cada vertice
 * el algoritmo clasico y luego busca el ciclo minimo
 * para cada par de vertices conectados a este
*/
int floydWarshall(int V, int matriz[V][V]) {

	int dist[V][V], actual, i, j, k, min = INF;
	// actual representa el vertice para el cual se busca el ciclo minimo
	for (actual = 0; actual < V; ++actual) {

		// Se inicia la matriz de distancias
		for (i = 0; i < V; ++i) {
			for (j = 0; j < V; ++j) {
				if (matriz[i][j] == 1 && i != actual && j != actual)
					dist[i][j] = matriz[i][j];
				else
					dist[i][j] = INF;
			}
		}

		// Algoritmo de Floyd-Warshall ignorando el vertice actual
		for (k = 0; k < V; ++k) {
			if (k != actual) {
				for (i = 0; i < V; ++i) {
					if (i != actual) {
						for (j = 0; j < V; ++j) {
							if (j != actual) {
								if (dist[i][k] + dist[k][j] < dist[i][j])
									dist[i][j] = dist[i][k] + dist[k][j];
							}
						}
					}
				}
			}
		}

		// Se busca la distancia minima entre dos vertices conectados al vertice actual
		for (i = 0; i < V; ++i) {
			if (matriz[actual][i] == 1) {
				for (j = i + 1; j < V; ++j) {
					if (matriz[actual][j] == 1) {
						if (dist[i][j] < min) {
							min = dist[i][j];
						}
					}
				}
			}
		}
	}
	// La distancia minima encontrada mas 2 representando la conexion de ambos vertices con el vertice central
	// -1 en caso de que no exista ciclo
	if (min == INF)
		return -1;
	else
		return min+2;
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


// verificar ingreso correcto de datos
int clean_stdin()
{
	while (getchar()!='\n');
	return 1;
}