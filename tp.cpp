#include <iostream>
#include <stdio.h>

using namespace std;

struct structA
{
	int dia;
	int horaE;
	int horaS;
}registro;

//-----------------------
int horasDia (int, int);
int acumulaHoras();
void leer();
int inasistencias();
//-----------------------

int main()
{
	int NM; // número de mes sobre el que se trabaja
	int DM; // cantidad de días del mes
	int NE; // Número de Empleado
	
	
	// Pedimos datos del mes y del empleado
	cout << "Ingrese el número de mes: " << endl;
	cin >> NM;
	cout << "Ingrese la cantidad de días del mes: " << endl;
	cin >> DM;
	cout << "Ingrese el Número de Empleado: " << endl;
	cin >> NE;
	
	inasistencias();
	leer();	
	acumulaHoras();
	
}

int horasDia (int entrada, int salida)
{
	// Toma la hora de entrada y la hora de salida y 
	// calcula la cantidad de horas trabajadas en el día.
	// Todo en formato HHMM.
	
	int ht = 0; // horas trabajadas
	int mt = 0; // minutos trabajados
	int ac = 0; // acarreo de horas
	int resultado = 0;
		//~ Contar Minutos
		
		mt = (salida % 100) - (entrada % 100); //Minutos de salida menos minutos de entrada
		ac = mt / 100; //Si acumulamos más de 60 min calculamos el acarreo en horas
		mt = mt % 100; //Nos quedamos solo con los minutos
		
		if (mt < 0) {
			mt = mt + 60;
			ac = ac - 1;
		}
		
		//~ Contar Horas
		ht = (salida / 100) - (entrada / 100) + ac;
		
		resultado = ht*100+mt;
		
		return resultado;
}

int acumulaHoras ()
{
	// Acumula horas en formato HHMM.
	
	FILE* arch = fopen("asisten.dat","r+b");
	structA registro;
	
	int ht = 0; // horas trabajadas
	int mt = 0; // minutos trabajados
	int ac = 0; // acarreo de horas
	int resultado = 0; // total de horas acumuladas en esta función
	int parcial = 0;
	
	fread(&registro,sizeof(registro),1,arch);
	
	while( !feof(arch) )
	{
		parcial = horasDia(registro.horaE, registro.horaS);
		//~ Contar Minutos
		
		mt = (resultado % 100) + (parcial % 100); //Minutos de salida menos minutos de entrada
		ac = mt / 100; //Si acumulamos más de 60 min calculamos el acarreo en horas
		mt = mt % 100; //Nos quedamos solo con los minutos
		
		//~ Contar Horas
		ht = (resultado / 100) + (parcial / 100) + ac;
		
		resultado = ht*100+mt; 
		
		fread(&registro,sizeof(registro),1,arch);
	}
				
	cout << endl << "Las horas acumuladas son " << resultado;

	return 0;
}

void leer()
{
	// Devuelve la cantidad de horas trabajadas todos los días
	// en formato HHMM.
	
	FILE* arch = fopen("asisten.dat","r+b");
	structA registro;
	
	
	fread(&registro,sizeof(registro),1,arch);
	
	while( !feof(arch) )
	{
		cout << horasDia(registro.horaE, registro.horaS) << endl;
		fread(&registro,sizeof(registro),1,arch);
	}
}

int inasistencias()
{
	FILE* arch = fopen("asisten.dat","r+b");
	structA registro;
	
	int i;
	
	fread(&registro,sizeof(registro),1,arch);
	
	for (i=1; i<32; i++)
	{
		if ( registro.dia != i)
		{
			cout << i << " ";
		}
		else
		{
			fread(&registro,sizeof(registro),1,arch);
		}
	}	
	return 0;
}




