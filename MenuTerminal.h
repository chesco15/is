#ifndef MENUTERMINAL_H
#define MENUTERMINAL_H

#include <iostream>
#include <list>
#include <cstring>
#include <cstdlib>
#include "agenda.h"
#include "contacto.h"

using namespace std;

	class MenuTerminal{


		private:

			Agenda _agenda;
		public:

			void salto(){

				cout << "\n\t\t\t---------------------------------------------------------------------------------\n";
			}

			MenuTerminal(Agenda a):_agenda(a){};

			void visualizarContacto(Contacto_it iterador){

				Contacto c=*iterador;
				list<citas>::iterator i;
		
				salto();

				cout <<"\t\t\t"<< "Nombre y Apellidos: " << c.getNombre() << " " << c.getApellidos() <<" DNI: "<< c.getDni() << endl;
				cout <<"\t\t\t"<< "Fecha Nacimiento: " << c.getFechanacimiento() << endl;
				cout <<"\t\t\t"<< "Telefono: " << c.getTelefono() << endl;

				list <citas> ld =c.getCitas();

				for(i=ld.begin() ; i!=ld.end() ; i++){

					if(i->fecha!=""){

						cout <<"\t\t\t"<<"Fecha: "<< i->fecha <<" Hora "<< i->hora <<" Motivo "<< i->motivo <<endl;
					}
				}
				cout << "\t\t\t---------------------------------------------------------------------------------\n";
			}



			void visualizarAgenda(){

				list <Contacto> auxiliar;
				auxiliar=_agenda.mostrarAgenda();
				
				Contacto_it i;
				

				cout << "\t\t\t---------------------------------------------------------------------------------\n";
				cout <<"\t\t\t"<<"*******************************AGENDA DE CONTACTOS*******************************";
				cout << "\n\t\t\t---------------------------------------------------------------------------------\n\n";

				if(!auxiliar.empty()){ //comprobamos que la agenda no este vacia

					for(i=auxiliar.begin() ; i!=auxiliar.end() ; i++){

						this->visualizarContacto(i); //Imprimir contacto a contacto
					}
				
				}else{
					salto();
					cout <<"\n\t\t\t\t\t" <<"*Actualmente no hay contactos en la agenda.\n";
					salto();
				}
			}


			void buscarContacto(){

				string apellido;
				salto();
				cout <<"\t\t\t"<< "Introduce el/los apellido/s del contacto que desea buscar:"<<endl<<"\t\t\t";
				getline(cin,apellido);

				list<Contacto>auxiliar;

				auxiliar=_agenda.buscarApellido(apellido);

				if(auxiliar.empty()){

					salto();
					cout <<"\n\t\t\t\t\t" <<"*No se han encontrado resultados en la búsqueda.\n";
					salto();
				}

				Contacto_it i;

				for(i=auxiliar.begin();i!=auxiliar.end();i++){

					this->visualizarContacto(i);//Imprimir contacto a contacto
				}
			}

			void rellenarContacto(Contacto &c){

				int Citas, i, e;

				string dni, nombre, apellidos, fechanacimiento, telefono, fecha, hora, motivo, cita;

				citas CitasAuxiliar;
				list <citas> CitasAux;
				

				salto();

				cout <<"\t\t\t"<< "¿Cuantas citas vas a guardar de este contacto? (Máximo 5)" << endl<<"\t\t\t";
				getline(cin,cita);

				Citas=atoi(cita.c_str());//Si meto una letra atoi() la convierte a 0, por lo tanto si hay equivocacion
										//metiendo una letra se guardarán 0 direcciones, ni te las pide que las metas.

				//es un problema que atoi devuelva 0 si meto una letra, porque si meto 0 por teclado
				//no puedo diferenciar esos dos casos
				if((Citas>5) || (Citas<0)){ //Si he metido un numero de direcciones que no se puede meter, direcciones=0
				
					Citas=0;
				}

				salto();

				cout <<"\t\t\t"<< "Introduce el dni del contacto: " << endl<<"\t\t\t";
				getline(cin,dni);
				c.setDni(dni);

				cout <<"\t\t\t"<< "Introduce el nombre del contacto: " << endl<<"\t\t\t";
				getline(cin,nombre);
				c.setNombre(nombre);

				cout <<"\t\t\t"<< "Introduce los apellidos del contacto: " << endl<<"\t\t\t";
				getline(cin,fechanacimiento);
				c.setFechanacimiento(fechanacimiento);

				cout <<"\t\t\t"<< "Introduce la fecha de nacimiento del contacto: " << endl<<"\t\t\t";
				getline(cin,telefono);
				c.setTelefono(telefono);

				cout <<"\t\t\t"<< "Introduce el telefono del contacto: " << endl<<"\t\t\t";
				getline(cin,telefono);
				c.setTelefono(telefono);


				for(i=0 ; i<Citas ; i++){

					cout <<"\t\t\t"<< "Fecha: " << endl<<"\t\t\t";
					getline(cin, CitasAuxiliar.fecha);

					cout <<"\t\t\t"<< "Hora: " << endl<<"\t\t\t";
					getline(cin, CitasAuxiliar.hora);

					cout <<"\t\t\t"<< "Motivo: " << endl<<"\t\t\t";
					getline(cin, CitasAuxiliar.motivo);

					CitasAux.push_back(CitasAuxiliar);

				}

				for(e=i ; e<5 ; e++){ //Añade los que faltan como vacío

					CitasAuxiliar.hora="";
					CitasAuxiliar.fecha="";
					CitasAuxiliar.motivo="";
					
					CitasAux.push_back(CitasAuxiliar);
				}
				c.setCitas(CitasAux);
	
			}

			void insertarContacto(){
				Contacto c;
				this->rellenarContacto(c);
				if(_agenda.insertar(c)){

					cout <<"\n\t\t\t\t\t" <<"*Nuevo contacto guardado correctamente.\n";
					salto();
				}
			}


			void modificarContacto(){

				Contacto c;
				string apellido, dni, coin, opcion;
				list<Contacto> auxiliar;
				list<Contacto>::iterator i,j;

				int contador=1, aux, k, var;

				salto();
				cout <<"\t\t\t"<< "Introduce el/los apellido/s para buscar al contacto que desea modificar: "<<endl<<"\t\t\t";
				getline(cin,apellido);
				cout <<"\n";

				auxiliar=_agenda.buscarApellido(apellido);


				if(!auxiliar.empty()){

					salto();
					cout <<"\t\t\tCoincidencias: ("<<auxiliar.size()<<")\n";

					for(i=auxiliar.begin();i!=auxiliar.end();i++){

						cout<<"\t\t\t\t\t\t\t\t|"<<contador<<"|";
						this->visualizarContacto(i);
						contador++;
					}

					j=auxiliar.begin();

					var=auxiliar.size();

					if(auxiliar.size()>1){

						cout <<"\n\t\t\t"<< "Ahora introduce el número de coincidencia que deseas modificar:"<<endl<<"\t\t\t";
						getline(cin,coin);
						cout <<"\n";

						aux=atoi(coin.c_str());
						if((aux>=1) && (aux<=var) ){ //si el numero introducido está en el rango que debe estar..
			
							for(k=1;k<aux;k++){
								j++;
							}


							if(_agenda.buscarDni(j->getDni())){

								this->rellenarContacto(c);
								if(_agenda.modificar(j->getDni(),c)){

									salto();
									cout <<"\n\t\t\t\t\t\t" <<"*Modificado con éxito.\n";
									salto();
								}
							}
						}else{

							salto();
							cout <<"\n\t\t\t\t" <<"*Error, el número de coincidencia introducido no es válido.\n";
							salto();
						}
					}else{

						cout <<"\n\t\t\t"<< "¿Está seguro de que desea modificar este contacto? (s/n)"<<endl<<"\t\t\t";
						getline(cin,opcion);


						if(opcion=="s"){

							if(_agenda.buscarDni(j->getDni())){

								this->rellenarContacto(c);
								if(_agenda.modificar(j->getDni(),c)){

									salto();
									cout <<"\n\t\t\t\t\t\t" <<"*Modificado con éxito.\n";
									salto();
								}
							}
		
						}else{

							salto();
							cout <<"\n\t\t\t\t\t\t" <<"*Contacto no modificado.\n";
							salto();
						}

					}

				}else{  //este if comprueba si esta o no esta el apellido de esa persona

					salto();
					cout <<"\n\t\t\t\t\t" <<"*No se han encontrado resultados en la búsqueda.\n";
					salto();
				}
			}

			void  borrarContacto(){

				string dni, apellido, coin, opcion;
				int contador=1, aux, k, var;
				list<Contacto> auxiliar;
				list<Contacto>::iterator i, j;

				salto();
				cout <<"\t\t\t"<< "Introduce el/los apellido/s para buscar al contacto que desea borrar:"<<endl<<"\t\t\t";
				getline(cin,apellido);
				cout <<"\n";



				auxiliar=_agenda.buscarApellido(apellido);

				if(!auxiliar.empty()){

					salto();
					cout <<"\t\t\tCoincidencias: ("<<auxiliar.size()<<")\n";

					for(i=auxiliar.begin();i!=auxiliar.end();i++){

						cout<<"\t\t\t\t\t\t\t\t|"<<contador<<"|";
						this->visualizarContacto(i);
						contador++;
					}

					j=auxiliar.begin();

					var=auxiliar.size();

					if(auxiliar.size()>1){ 
		
						cout <<"\n\t\t\t"<< "Ahora introduce el número de coincidencia que deseas borrar: "<<endl<<"\t\t\t";
						getline(cin,coin);
						cout <<"\n";

						aux=atoi(coin.c_str());
						if((aux>=1) && (aux<=var) ){
			
							for(k=1;k<aux;k++){ 
								j++;
							}

							if(_agenda.eliminar(j->getDni())){

								salto();
								cout <<"\n\t\t\t\t\t\t" <<"*Borrado con éxito.\n";
								salto();
							}else{

								salto();
								cout <<"\n\t\t\t\t\t\t" <<"*Error eliminando.\n";
								salto();
							}
						}else{

							salto();
							cout <<"\n\t\t\t\t\t" <<"*Error, el número de coincidencia introducido no es válido.\n";
							salto();
						}
					}else{

						cout <<"\n\t\t\t"<< "¿Está seguro de borrar este contacto? (s/n)"<<endl<<"\t\t\t";
						getline(cin,opcion);

						if(opcion=="s"){

							if(_agenda.eliminar(j->getDni())){

								salto();
								cout <<"\n\t\t\t\t\t\t" <<"*Borrado con éxito.\n";
								salto();
							}else{

								salto();
								cout <<"\n\t\t\t\t\t\t" <<"*Error eliminando.\n";
								salto();
							}
						}else{

							salto();
							cout <<"\n\t\t\t\t\t\t" <<"*Contacto no borrado.\n";
							salto();
						}
					}

				}else{       
	
					salto();
					cout <<"\n\t\t\t\t\t" <<"*No se han encontrado resultados en la búsqueda.\n";
					salto();
				}
			}

	};

#endif
