#ifndef CONTACTO_H
#define CONTACTO_H
#include <iostream>
#include <string>
#include <list>

using namespace std;

	typedef struct{

		string fecha;
		string hora;
		string motivo;
	}citas;

	class Contacto{

		private:

			string _dni;
			string _nombre;
			string _apellidos;
			string _fechanacimiento;
			string _telefono;
			list <citas> _citas;

		public:


		string getDni() const{

			return _dni;
		}

		void setDni(string dni){

			_dni = dni;
		}

		string getNombre() const{

			return _nombre;
		}

		void setNombre(string nombre){

			_nombre = nombre;
		}

		string getApellidos() const{

			return _apellidos;
		}
		
		void setApellidos(string apellidos){

			_apellidos = apellidos;
		}

		string getFechanacimiento() const{

			return _fechanacimiento;
		}

		void setFechanacimiento(string fecha){

			_fechanacimiento = fecha;
		}

		string getTelefono() const{

			return _telefono;
		}

		void setTelefono(string telefono){

			_telefono = telefono;
		}

		list <citas> getCitas() const{

			return _citas;
		}

		void setCitas(list <citas> citas){

			_citas = citas;
		}

	};

#endif
