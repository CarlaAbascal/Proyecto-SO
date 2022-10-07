//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexi￳n: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexin
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "Othello",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//iniciamos la consulta
	char consulta [110];
	strcpy (consulta, "SELECT Jugador.Username FROM Jugador WHERE Jugador.Nivel = (SELECT MAX(Jugador.Nivel))");
	strcat (consulta);
	
	
	//Para comprobar errores en la consulta
	err=mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//recogemos el resultado de la consulta. El resultado de la
	//consulta se devuelve en una variable del tipo puntero a
	//MYSQL_RES tal y como hemos declarado anteriormente.
	//Se trata de una tabla virtual en memoria que es la copia
	//de la tabla real en disco.
	resultado = mysql_store_result (conn);
	// El resultado es una estructura matricial en memoria
	// en la que cada fila contiene los datos de una persona.

	// Ahora obtenemos la primera fila que se almacena en una
	// variable de tipo MYSQL_ROW
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf("El Jugador con Nivel Mas alto es %s\n", row[0]);
	
	mysql_close (conn);
	exit(0);
}
