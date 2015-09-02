#ifndef AGENDA_H
#define AGENDA_H
#include <iostream>
#include <string>
#include <list>
#include<fstream>
#include<cstdlib>
#include<locale>

#include "contacto.h"
#include "GestorFichero.h"

using namespace std;

typedef list<Contacto>::iterator Contacto_it;

	class Agenda{


		private:

			list<Contacto> _contactos;
			GestorFichero *GestorDB;

		public:

			Agenda(GestorFichero * p): GestorDB(p){}; //constructor de agenda

			string minuscula(string cadena){ //funcion que devuelve los apellidos en minuscula

				locale loc;
				string str=cadena;

				for (string::size_type i=0; i<str.length(); ++i)
	 				str[i] = tolower(str[i],loc);
				return str;
			}



			list <Contacto> buscarApellido(string apellido){

				//cargar del fichero
				list<Contacto> auxiliar; //fichero completo hecho lista
				auxiliar = GestorDB->cargar();
				string apellidos;

				list<Contacto> retorno; //lista

				list<Contacto>::iterator i;

				for (i = auxiliar.begin(); i != auxiliar.end(); i++){

					apellidos=minuscula(i->getApellidos());//pasamos a minuscula los apellidos

					size_t encontrado=apellidos.find(minuscula(apellido));//Buscamos el apellido en minuscula en los apellidos del contacto

					if(encontrado!=string::npos){ //Si hay resultado se añadirá a la lista de retorno

						retorno.push_back(*i); //iterator i es un puntero, por tanto para pasar su valor es necesario el operador *

					}
				}
			return retorno;
			}

			bool buscarDni(string dni){
				list<Contacto> auxiliar;
				auxiliar = GestorDB->cargar();

				list<Contacto>::iterator i;
				bool encontrado = false;

				for (i = auxiliar.begin(); i != auxiliar.end(); i++){

				if (i->getDni() == dni){

					encontrado=true;
					
					return encontrado;
				}
			}
			return false;

			}


			
			bool insertar(const Contacto &c) {

				list<Contacto> auxiliar;
				auxiliar = GestorDB->cargar();
				auxiliar.push_back(c);

				if(GestorDB->guardar(auxiliar)){

					return true;
				}else{

					return false;
				}
			}


			bool eliminar(string dni){

				list <Contacto> auxiliar;
				list <Contacto>::iterator i,j;
				int encontrado;
				auxiliar = GestorDB->cargar();

				for (i = auxiliar.begin(); i != auxiliar.end(); i++) {
					if (i->getDni() == dni) {
						j=i;
						encontrado=1;
					}
				}

				if(encontrado==1){
					auxiliar.erase(j);
					GestorDB->guardar(auxiliar);
					return true;
				}else{
					return false;
				}
			}


			bool modificar(string dni, Contacto &c) {

				list<Contacto> auxiliar;
				auxiliar = GestorDB->cargar();
				list<Contacto>::iterator i;


				for (i = auxiliar.begin(); i != auxiliar.end(); i++){

					if (i->getDni() == dni){

						*i=c; 
						GestorDB->guardar(auxiliar);
						return true;
					}
				}
				return false;
			}

			list<Contacto> mostrarAgenda(){

				return GestorDB->cargar();
			}

			
	};

#endif
