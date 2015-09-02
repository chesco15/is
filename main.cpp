#include <iostream>
#include "agenda.h"
#include "MenuTerminal.h"
#include "GestorFichero.h"
#include <cstdlib>
#include <cstring>

using namespace std;

void enter()
{
	string enter;
	cout << "\n\n\t\t\t---------------------------------------------------------------------------------\n";
	cout<<"\t\t\t\t       ***PRESIONA ENTER PARA VOLVER A LAS OPCIONES DE LA AGENDA***";
	cout << "\n\t\t\t---------------------------------------------------------------------------------\n\t\t\t";
	getline(cin,enter);
}

int main(){

	GestorFichero *mi_gestor = new GestorFichero("agendaContactos.txt");

	Agenda a = Agenda(mi_gestor);

	MenuTerminal m(a);

	int menu;
	string nomFich;
	char ruta[50]="cp agendaContactos.txt copiaSeguridad.bk";
	system("clear");

	do{
		system("clear");
		cout<<"\n"<<"\t\t\t\t"<<"****************************AGENDA***************************"<<endl;
		cout<<"\t\t\t\t"<<"(1) Visualizar la agenda completa."<<endl;
		cout<<"\t\t\t\t"<<"(2) Insertar un nuevo contacto en la agenda."<<endl;
		cout<<"\t\t\t\t"<<"(3) Buscar un contacto en la agenda."<<endl;
		cout<<"\t\t\t\t"<<"(4) Modificar un contacto de la agenda."<<endl;
		cout<<"\t\t\t\t"<<"(5) Borrar un contacto de la agenda."<<endl;
		cout<<"\t\t\t\t"<<"(0) Salir."<<endl;
		cout<<"\t\t\t\t"<<"*************************************************************"<<endl<<"\t\t\t\t";
		cin >>menu;
		cout<<"\n";
		cin.ignore(256,'\n');
		switch(menu){

			case 1:
				system("clear");
				m.visualizarAgenda();
				enter();
				system("clear");
				break;

			case 2:
				system("clear");
				m.insertarContacto();
				enter();
				system("clear");

				break;

			case 3:

				system("clear");
				m.buscarContacto();
				enter();
				system("clear");
				break;

			case 4:
				system("clear");
				m.modificarContacto();
				enter();
				system("clear");
				break;

			case 5:
				system("clear");
				m.borrarContacto();
				enter();
				system("clear");
				break;
			
		}
	}while(menu!=0);

return 0;
}
