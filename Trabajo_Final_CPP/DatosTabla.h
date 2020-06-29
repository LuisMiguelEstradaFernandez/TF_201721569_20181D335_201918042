#pragma once
#ifndef  __DATOSTABLA_H_
#define __DATOSTABLA_H_

#include <string>

class Usuario {
	//nombre apellido liga dni club edad sexo
	std::string nombre;
	std::string apellido;
	std::string liga;
	std::string club;
	char sexo;
	long long dni;
	int edad;
public:
	Usuario(std::string nombre, std::string apellido, int edad, char sexo, std::string club, std::string liga, long long dni)
		:nombre(nombre), apellido(apellido), edad(edad), sexo(sexo), club(club), liga(liga), dni(dni) {}
	std::string getNombre() { return nombre; }
	std::string getApellido() { return apellido; }
	std::string getLiga() { return liga; }
	std::string getClub() { return club; }
	char getSexo() { return sexo; }
	long long getDni() { return dni; }
	int getEdad() { return edad; }

	void setNombre(std::string nombre) { this->nombre = nombre; }
	void setApellido(std::string apellido) { this->apellido = apellido; }
	void setLiga(std::string liga) { this->liga = liga; }
	void setClub(std::string club) { this->club = club; }
	void setSexo(char sexo) { this->sexo = sexo; }
	void setDni(long long dni) { this->dni = dni; }
	void setEdad(int edad) { this->edad = edad; }
};

#endif // ! __DATOSTABLA_H_