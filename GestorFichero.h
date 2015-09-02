#ifndef GESTORFICHERO
#define GESTORFICHERO

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include "contacto.h"

using namespace std;


	class GestorFichero{

		private:

			string _fichero;

		public:

			GestorFichero(string nomFich) : _fichero(nomFich){}; //constructor que le pasamos un fichero

			string getFichero()const{ //observador del fichero

				return _fichero;
			}

			bool guardar(list <Contacto> lista){ //funcion que guarda el fichero

				list <Contacto>::iterator c;
				list <citas>:: iterator d;

				ofstream archivo;
				archivo.open(getFichero().c_str());

				if(archivo.is_open()){

					for(c=lista.begin();c!=lista.end();c++){ //Lista de contactos

						archivo << c->getDni() << ",";
						archivo << c->getNombre() << ",";
						archivo << c->getApellidos() << ",";
						archivo << c->getFechanacimiento()<< ",";
						archivo << c->getTelefono() << ",";
						
						list<citas> citas = (*c).getCitas();
						

						for(d=citas.begin() ; d!=citas.end() ; d++){ //Lista de citas

							
							archivo << d->fecha << ",";
							archivo << d->hora << ",";
							archivo << d->motivo << ",";	
						}
						
						
					}
					archivo.close(); //cerramos el fichero
					return true; //Guardado en fichero con exito
				}

			return false; //Error en apertura de fichero
			}


			list <Contacto> cargar() { //funcion que carga el fichero en una lista auxiliar

				//Variables auxiliares del getline
				char dni[9], nombre[30], apellidos[60], telefono[12], fechanacimiento[20]; //D.Personales
				char fecha[20], hora[20], motivo[20]; //D.Citas
				int i;

				list <citas> auxCitas;
				citas auxCita;

				list <Contacto> auxContactos; //creo una lista auxiliar de contactos
				Contacto auxContacto; //creo un objeto auxiliar contacto

				ifstream archivo; //creamos el fichero
				archivo.open(getFichero().c_str()); //abrimos el fichero

				if(archivo.is_open()){


					while(archivo.getline(dni,200,',')){ //añadimos los datos personales

						archivo.getline(nombre,200,',');
						archivo.getline(apellidos,200,',');
						archivo.getline(fechanacimiento,200,',');
						archivo.getline(telefono,200,',');

						auxContacto.setDni(dni);
						auxContacto.setNombre(nombre);
						auxContacto.setApellidos(apellidos);
						auxContacto.setFechanacimiento(fechanacimiento);
						auxContacto.setTelefono(telefono);


						auxCitas.clear(); //vaciamos lista de citas

						for(i=0 ; i<5 ; i++){ //añadimos los datos de las citas

							archivo.getline(fecha,200,',');
							archivo.getline(hora,200,',');
							archivo.getline(motivo,200,',');	

							auxCita.fecha = fecha;
							auxCita.hora = hora;
							auxCita.motivo = motivo;

							auxCitas.push_back(auxCita); //Añadimos nuevo elemento de Citas a la lista
							
						}

						auxContacto.setCitas(auxCitas); //Añadimos esta lista de citas al contacto

						auxContactos.push_back(auxContacto); //añadimos la lista auxiliar ya cargada a nuestra lista 

					}

					archivo.close(); //cerramos el fichero
				}
			return auxContactos; //Al colocarlo aqui en caso de no haber nada en el fichero devuelve lista vacia
			}
	
	};


#endif
