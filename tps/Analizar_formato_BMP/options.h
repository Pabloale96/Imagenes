// #########################################################
// Algoritmos y Programacion II (95.12)
// Trabajo Practico 0: Programacion C++
// Nombre del archivo: options.h
// #########################################################

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;


static void opt_input(string const &);
static void opt_output(string const &);
//static void opt_data(string const &);
static void opt_help(string const &);
//static void opt_option(string const &);
//static void opt_method(string const &);

// Tabla de opciones de linea de comando. El formato de la tabla
// consta de un elemento por cada opcion a definir. A su vez, en
// cada entrada de la tabla tendremos:
//
// o La primera columna indica si la opcion lleva (1) o no (0) un
//   argumento adicional.
//
// o La segunda columna representa el nombre corto de la opcion.
//
// o Similarmente, la tercera columna determina el nombre largo.
//
// o La cuarta columna contiene el valor por defecto a asignarle
//   a esta opcion en caso que no este explicitamente presente
//   en la linea de comandos del programa. Si la opcion no tiene
//   argumento (primera columna nula), todo esto no tiene efecto.
//
// o La quinta columna apunta al metodo de parseo de la opcion,
//   cuyo prototipo debe ser siempre void (*m)(string const &arg);
//
// o La ultima columna sirve para especificar el comportamiento a
//   adoptar en el momento de procesar esta opcion: cuando la
//   opcion es obligatoria, deberá activarse OPT_MANDATORY.
//
// Además, la ultima entrada de la tabla debe contener todos sus
// elementos nulos, para indicar el final de la misma.
//
/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

//static istream *dss = 0;
//static fstream dfs;

//static string option;
//static string method;
/*****************************************************/

static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.
	//
	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		//ifs.open(arg.c_str(),ios::in);
		ifs.open(arg.c_str(),ios::binary|ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.
	//
	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.
	//
	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		//ofs.open(arg.c_str(), ios::out);
		ofs.open(arg.c_str(), ios::binary|ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.
	//
	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminacion del programa en su totalidad
	}
}

static void
opt_help(string const &arg)
{
	ifstream help_file;
    help_file.open("help.txt");

	while(help_file.good())
    	cout << (char)help_file.get();

	exit(0);
}
