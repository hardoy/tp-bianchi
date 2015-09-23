#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

struct structA
{
	int dia;
	int horaE;
	int horaS;
}registro;

//-----------------------
int horasDia (int, int);
int acumulaHoras(int, int);
int promedio(int, int);
//-----------------------

//-----------------------
int NM; // número de mes sobre el que se trabaja
int DM; // cantidad de días del mes
string NE; // Número de Empleado
string meses[12] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", 
	"julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
//-----------------------

int main()
{
	// Pedimos datos del mes y del empleado
	cout << "Ingrese el número de mes: " << endl;
	cin >> NM;
	cout << "Ingrese la cantidad de días del mes: " << endl;
	cin >> DM;
	cout << "Ingrese el Número de Empleado: " << endl;
	cin >> NE;

	int faltasVec[30] = {}; // vector para almacenar inasistencias
	int cortosVec[30] = {}; // vector para almacenar dias cortos
	
	// Abrimos el archivo de asistencias
	FILE* arch = fopen("asisten.dat", "r+b");
	structA registro;
	
	int i;
	int horasTotales = 0;
	
	// Leer el archivo
	fread(&registro,sizeof(registro),1,arch);
	
	for (i=1; i<DM+1; i++) 
		{
		// Las faltas las cargamos en faltasVec[]
		if ( registro.dia != i) 
		{
			faltasVec[i-1] = i;
		}
		
		// Por cada día asistido hay que calcular las horas trabajadas
		else 
			{
			int horasDelDia = horasDia(registro.horaE, registro.horaS);
		
			// Registrar los días que trabajó menos de 8 horas en cortosVec[]
			if (horasDelDia < 800)
				{
				cortosVec[i-1] = i;
				}
			horasTotales = acumulaHoras(horasDelDia, horasTotales);
			fread(&registro,sizeof(registro),1,arch);
			}
	}
	
	
	//~ // Abrimos archivo de texto donde volcamos las salidas.
	ofstream salida;
	salida.open ("salida.txt");
	
	salida << "Empleado Nº: " << NE << "\n\n";
	salida << "Mes de " << meses[NM-1] << "\n\n";
	
	salida << "El empleado trabajó un total de " << horasTotales/100 << " horas y " << horasTotales%100 << " minutos" << "\n\n";
	
	salida << "El empleado trabajó un promedio de" << promedio(horasTotales, DM) /100 << " horas y " << promedio(horasTotales, DM)%100 << " minutos por día" << "\n\n";
	
	salida << "El empleado faltó los días: " << "\n\n";
	for (i = 0; i < 30; i++) 
	{
		if (faltasVec[i] != 0) {
			salida << faltasVec[i] << endl;
		}
	}
	salida << "\n\n" << "El empleado trabajó menos de 8 horas los días: " << endl;
	for (i = 0; i < 30; i++) 
	{
		if (cortosVec[i] != 0) {
			salida << cortosVec[i] << endl;
		}
	}

	
	
	return 0;
	
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

int acumulaHoras(int horasDelDia, int horasTotales)
{
	// Acumula horas en formato HHMM.
	
	int minutosTotales = 0;
	int minutosDelDia = 0;

		//~ Contar Minutos
		minutosTotales = horasTotales / 100 * 60 + horasTotales % 100;
		minutosDelDia = horasDelDia / 100 * 60 + horasDelDia % 100;
		
		minutosTotales = minutosTotales + minutosDelDia;
		
		horasTotales = minutosTotales / 60 *100 + minutosTotales % 60; 
		
	return horasTotales;
}

int promedio(int horasTotales, int DM)
{
	// Acumula horas en formato HHMM.
	int promedio;
	int minutosTotales = 0;

		//~ Contar Minutos
		minutosTotales = horasTotales / 100 * 60 + horasTotales % 100;
		
		promedio = minutosTotales / DM;
		
		promedio = promedio / 60 *100 + promedio % 60;
		
	return promedio;
}
