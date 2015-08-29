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

			Agenda(GestorFichero * p): GestorDB(p){};

			std::string minuscula(std::string cadena){
				std::locale loc;
				std::string str=cadena;
				for (std::string::size_type i=0; i<str.length(); ++i)
	 				str[i] = std::tolower(str[i],loc);
				return str;
			}



			list <Contacto> buscarApellido(std::string apellido){
				//cargar del fichero
				std::list<Contacto> auxiliar; //fichero completo hecho lista
				auxiliar = GestorDB->cargar();
				std::string apellidos;

				list<Contacto> retorno; //lista

				std::list<Contacto>::iterator i;

				for (i = auxiliar.begin(); i != auxiliar.end(); i++){

					apellidos=minuscula(i->getApellidos());//pasamos a minuscula los apellidos

					std::size_t encontrado=apellidos.find(minuscula(apellido));//Buscamos el apellido en minuscula en los apellidos del contacto

					if(encontrado!=std::string::npos){ //Si hay resultado se añadirá a la lista de retorno

						retorno.push_back(*i); //iterator i es un puntero, por tanto para pasar su valor es necesario el operador *

						//Incorporacion

						//i->aumentaFrecuencia();
						//this->modificar(i->getDni(),*i);//modificamos el contacto tras incrementar su frecuencia

						//Fin de incorporacion

						// COMENTARIOS: Para añadir funcionalidad de más frecuentes i->incrementarFrecuente();
					}
				}
			return retorno;
			}

			bool buscarDni(std::string dni){
				std::list<Contacto> auxiliar;
				auxiliar = GestorDB->cargar();

				std::list<Contacto>::iterator i;
				bool encontrado = false;

				for (i = auxiliar.begin(); i != auxiliar.end(); i++){

				if (i->getDni() == dni){

					encontrado=true;
					/* COMENTARIO: incluso se puede hacer el return aquí para no
					 * seguir recorriendo la lista*/
					return encontrado;
				}
			}
			return false;

			}


			
			bool insertar(const Contacto &c) {

				std::list<Contacto> auxiliar;
				auxiliar = GestorDB->cargar();
				auxiliar.push_back(c);

				if(GestorDB->guardar(auxiliar)){

					return true;
				}else{

					return false;
				}
			}


			bool eliminar(std::string dni){

				std::list<Contacto> auxiliar;
				std::list<Contacto>::iterator i,j;
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


			bool modificar(std::string dni, Contacto &c) {
				std::list<Contacto> auxiliar;
				auxiliar = GestorDB->cargar();
				std::list<Contacto>::iterator i;


				for (i = auxiliar.begin(); i != auxiliar.end(); i++){

					if (i->getDni() == dni){

						*i=c; //iterator i es un puntero, por tanto para pasar su valor es necesario el operador *
						GestorDB->guardar(auxiliar);
						return true;
					}
				}
				return false;
			}

			std::list<Contacto> mostrarAgenda(){

				return GestorDB->cargar();
			}

			
	};

#endif
