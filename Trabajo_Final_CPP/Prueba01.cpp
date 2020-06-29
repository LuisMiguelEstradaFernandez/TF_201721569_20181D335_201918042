#include <iostream>
#include <vector>
#include <functional>
#include <conio.h>
#include "DatosTabla.h"

using namespace std;

#define max(a, b) (a > b? a : b)
#ifndef __AVL_H__
#define __AVL_H__

template<typename T, typename R = T, T NONE = 0>

class AVLBST {
	struct Node {
		T       element;
		Node* left;
		Node* right;
		int     height;

		Node(T element)
			: element(element), height(0),
			left(nullptr), right(nullptr) {}
	};

	Node* root;
	function<R(T)>  key;
	int             len;
public:
	AVLBST(function<R(T)> key = [](T a) { return a; })
		: key(key), root(nullptr), len(0) {}
	~AVLBST() { clear(root); }

	int height() { return height(root); }
	int size() { return len; }
	void clear() { clear(root); len = 0; }

	void add(T elem) { add(root, elem); }

	T find(R val) { return find(root, val); }
	T MayorA(R val) { return MayorA(root, val); }
	T MenorA(R val) { return MenorA(root, val); }
	T IgualA(R val) { return IgualA(root, val); }
	void inOrder(function<void(T)> proc) { inOrder(root, proc); }

private:

	//Operaciones básicas

	void clear(Node*& node) {
		if (node != nullptr) {
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}

	int height(Node* node) {
		return node == nullptr ? -1 : node->height;
	}


	void add(Node*& node, T elem) {
		if (node == nullptr) {
			node = new Node(elem);
			++len;
		}
		else {
			if (key(elem) < key(node->element)) {
				add(node->left, elem);
			}
			else {
				add(node->right, elem);
			}
			balance(node);
		}
	}

	T find(Node* node, R val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val == key(node->element)) {
			return node->element;
		}
		else if (val < key(node->element)) {
			return find(node->left, val);
		}
		else {
			return find(node->right, val);
		}
	}

	T MayorA(Node* node, R val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val < key(node->element)) {
			return node->element;
		}
		return MayorA(node->right, val);
	}
	T MenorA(Node* node, R val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val > key(node->element)) {
			return node->element;
		}
		return MenorA(node->right, val);
	}
	T IgualA(Node* node, R val) {
		if (node == nullptr) {
			return NONE;
		}
		else if (val == key(node->element)) {
			return node->element;
		}
		return IgualA(node->right, val);
	}

	void inOrder(Node* node,
		function<void(T)> proc) {
		if (node != nullptr) {
			inOrder(node->left, proc);
			proc(node->element);
			inOrder(node->right, proc);
		}
	}

	void updateHeight(Node* node) {
		if (node != nullptr) {
			int hl = height(node->left);
			int hr = height(node->right);

			node->height = max(hl, hr) + 1;
		}
	}

	//Operaciones para el balanceo

	void rotateLeft(Node*& node) {
		Node* aux = node->right;
		node->right = aux->left;
		updateHeight(node);
		aux->left = node;
		updateHeight(aux);
		node = aux;
	}

	void rotateRight(Node*& node) {
		Node* aux = node->left;
		node->left = aux->right;
		updateHeight(node);
		aux->right = node;
		updateHeight(aux);
		node = aux;
	}

	void balance(Node*& node) {
		int hl = height(node->left);
		int hr = height(node->right);

		if (hr - hl < -1) {
			hl = height(node->left->left);
			hr = height(node->left->right);
			if (hr > hl) {
				rotateLeft(node->left);
			}
			rotateRight(node);
		}
		else if (hr - hl > 1) {
			hl = height(node->right->left);
			hr = height(node->right->right);
			if (hl > hr) {
				rotateRight(node->right);
			}
			rotateLeft(node);
		}
		else {
			updateHeight(node);
		}
	}

};


#endif // !__AVL_H__

void genera_columnas(vector<int> n) {
	int columna = 1;

	cout << "\t";

	for (int i = 0; i < n.size(); i++) {
		//	:nombre(nombre), apellido(apellido), edad(edad), sexo(sexo), club(club), liga(liga), dni(dni){}

		if (n[i] == 1)
			cout << "NOMBRE";

		if (n[i] == 2)
			cout << "APELLIDO";

		if (n[i] == 3)
			cout << "EDAD";

		if (n[i] == 4)
			cout << "SEXO";

		if (n[i] == 5)
			cout << "CLUB";
		if (n[i] == 6)
			cout << "LIGA";
		if (n[i] == 7)
			cout << "DNI";
		cout << "          ";
	}
	cout << endl;
	cout << "Presione cualquier tecla para comenzar a llenar los datos" << endl;
}

void genera_Filas(int n) {
	int filas = 1;

	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << filas << endl;
		filas++;
		cout << endl;
	}
}

void inicio() {
	cout << "\t\t\t\t.:TABLA:." << endl << endl;
	int opc;
	vector<int> opciones;
	//	:nombre(nombre), apellido(apellido), edad(edad), sexo(sexo), club(club), liga(liga), dni(dni){}

	do {
		cout << "Selecciones las columnas que desea utilizar: ";
		cout << "\n1.Nombre" << endl;
		cout << "2.Apellido" << endl;
		cout << "3.Edad" << endl;
		cout << "4.Sexo" << endl;
		cout << "5.Club" << endl;
		cout << "6.Liga" << endl;
		cout << "7.Dni" << endl;
		cout << "8.Siguiente" << endl;
		//cout << "Columnas: ";
		cin >> opc;

		if (opc != 8)
			opciones.push_back(opc);

		system("cls");
	} while (opc != 8);


	genera_columnas(opciones);

	//Aca escriban la magia

	system("pause>>null");
}


int main() {

	inicio();
	system("cls");
	string Nombre, Apellido, Liga, Club; int Edad; char Sexo; long long Dni;
	vector<Usuario*> usuarios;
	cout << endl;
	auto k1 = [](Usuario* a) {return a->getNombre(); };
	AVLBST<Usuario*, string, nullptr>* idxNombre =
		new AVLBST<Usuario*, string, nullptr>(k1);

	auto k2 = [](Usuario* a) {return a->getApellido(); };
	AVLBST<Usuario*, string, nullptr>* idxApellido =
		new AVLBST<Usuario*, string, nullptr>(k2);

	auto k3 = [](Usuario* a) {return a->getDni(); };
	AVLBST<Usuario*, long long, nullptr>* idxDni =
		new AVLBST<Usuario*, long long, nullptr>(k3);

	auto k4 = [](Usuario* a) {return a->getClub(); };
	AVLBST<Usuario*, string, nullptr>* idxClub =
		new AVLBST<Usuario*, string, nullptr>(k4);

	auto k5 = [](Usuario* a) {return a->getLiga(); };
	AVLBST<Usuario*, string, nullptr>* idxLiga =
		new AVLBST<Usuario*, string, nullptr>(k5);

	auto k6 = [](Usuario* a) {return a->getEdad(); };
	AVLBST<Usuario*, int, nullptr>* idxEdad =
		new AVLBST<Usuario*, int, nullptr>(k6);

	auto k7 = [](Usuario* a) {return a->getSexo(); };
	AVLBST<Usuario*, char, nullptr>* idxSexo =
		new AVLBST<Usuario*, char, nullptr>(k7);


	//	:nombre(nombre), apellido(apellido), edad(edad), sexo(sexo), club(club), liga(liga), dni(dni){}

	usuarios.push_back(new Usuario("Pedro", "Luna", 15, 'M', "Club1", "Liga1", 777777777));
	usuarios.push_back(new Usuario("Lucas", "Solo", 34, 'F', "Club2", "Liga3", 775577777));
	usuarios.push_back(new Usuario("Juan", "Malosa", 25, 'M', "Club3", "Liga2", 154777777));

	/*for (auto user : usuarios) {
		idxNombre->add(user);
		idxApellido->add(user);
		idxEdad->add(user);
		idxSexo->add(user);
		idxClub->add(user);
		idxLiga->add(user);
		idxDni->add(user);
	}*/
	auto print = [](Usuario* a) {
		if (a == nullptr) return;
		cout << a->getNombre()
			<< "\t" << a->getApellido()
			<< "\t" << a->getEdad()
			<< "\t" << a->getSexo()
			<< "\t" << a->getClub()
			<< "\t" << a->getLiga()
			<< "\t" << a->getDni() << endl;

	};

	//Menu Principal
	int options = 20;
	while (options != 0)
	{
		system("cls");
		cout << endl << "TF" << endl;
		cout << "________________________" << endl;
		cout << "1) Agregar usuario" << endl;
		cout << "2) Eliminar usuario/s" << endl;
		cout << "3) Buscar usuario" << endl;
		cout << "4) Mostrar usuarios por orden" << endl;
		cout << "5) Filtrado de datos" << endl;
		cout << "0) Cerrar lista" << endl;

		cout << endl << "Selecciona una opcion: "; cin >> options;
		system("cls");
		string nombreE, apellidoE; int orden = 7;
		//Datos para filtro
		int edadF; char sexoF;
		switch (options)
		{
		default:
			cout << "La opcion no existe" << endl;
			_getch();
			break;
		case 0:
			break;
		case 1:
			cout << "NOTA: En caso de que no exista ese dato, dejar un espacio en blanco" << endl;
			cout << "Ingrese nombre: "; cin >> Nombre; cout << endl;
			cout << "Ingrese apellido: "; cin >> Apellido; cout << endl;
			cout << "Ingrese edad: "; cin >> Edad; cout << endl;
			cout << "Ingrese sexo: "; cin >> Sexo; cout << endl;
			cout << "Ingrese club: "; cin >> Club; cout << endl;
			cout << "Ingrese liga: "; cin >> Liga; cout << endl;
			cout << "Ingrese dni: "; cin >> Dni; cout << endl;
			usuarios.push_back(new Usuario(Nombre, Apellido, Edad, Sexo, Club, Liga, Dni));
			for (auto user : usuarios) {
				idxNombre->add(user);
				idxApellido->add(user);
				idxEdad->add(user);
				idxSexo->add(user);
				idxClub->add(user);
				idxLiga->add(user);
				idxDni->add(user);
			}
			_getch();
			break;
		case 2:
			int  opcioneliminar;
			cout << "Desea eliminar un usuario[1] o un grupo de usuarios[2]?" << endl; cin >> opcioneliminar;
			if (opcioneliminar == 1) {
				cout << "Inserte nombre, apellido y DNI del usuario a eliminar: "; cin >> nombreE; cout << " "; cin >> apellidoE;
			}
			else if (opcioneliminar == 2) {
				cout << "Puede eliminar los siguiente grupos de usuarios" << endl;
				cout << "1) Eliminar usuarios por sexo" << endl;
				cout << "1) Eliminar usuarios por edad" << endl;
				cout << "1) Eliminar usuarios por liga" << endl;
				cout << "1) Eliminar usuarios por club" << endl;
				cout << "Esto aun no elimina" << endl;
			}
			else {
				cout << "La opcion no existe" << endl;
			}
			_getch();
			break;
		case 3:
			//NOTA: solo busca por nombre, por ahora
			cout << "Ingrese el nombre y apellido del usuario a buscar: " << endl;
			cin >> nombreE; cout << " "; cin >> apellidoE;
			print(idxNombre->find(nombreE));
			_getch();
			break;
		case 4:

			cout << "¿Como desea mostrar los datos de la tabla?" << endl;
			cout << "1. Ordenado por nombre" << endl;
			cout << "2. Orneado por apellido" << endl;
			cout << "3. Ordenado por edad" << endl;
			cout << "4. Ordenado por sexo" << endl;
			cout << "5. Ordenado por club" << endl;
			cout << "6. Ordenado por liga" << endl;
			cout << "7. Ordenado por dni" << endl;
			cout << "8. Salir " << endl;
			cout << "Elige una opcion: "; cin >> orden; cout << endl;
			switch (orden)
			{
			case 1:
				idxNombre->inOrder(print);
				_getch();
				break;
			case 2:
				idxApellido->inOrder(print);

				_getch();
				break;
			case 3:
				idxEdad->inOrder(print);

				_getch();
				break;
			case 4:
				idxSexo->inOrder(print);

				_getch();
				break;
			case 5:
				idxClub->inOrder(print);

				_getch();
				break;
			case 6:
				idxLiga->inOrder(print);

				_getch();
				break;
			case 7:
				idxDni->inOrder(print);
				_getch();
				break;
			case 8:
				break;
			default:
				cout << "La opcion no existeeeeeeeeeeeeeeeee" << endl;
				_getch();
				break;
			}
			_getch();
			break;
		case 5:
			int opcionfiltrado;
			cout << "|-| Filtrado de datos |-|" << endl;
			cout << "¿Como desea filtrar los datos?" << endl;
			cout << "1) Mostras los usuarios con una edad mayor a " << endl;
			cout << "2) Mostrar los usuarios con una edad menor a " << endl;
			cout << "3) Mostrar los usuarios con una edad igual a " << endl;
			cout << "4) Filtrar por genero " << endl;
			cout << "5) Mostrar los usuarios lo cual su nombre inicia con " << endl;
			cout << "6) Mostrar los usuarios lo cual su apellido inicia con " << endl;
			cout << "7) Mostrar los usuarios lo cual su nombre finaliza con " << endl;
			cout << "8) Mostrar los usuarios lo cual su apellido finaliza con " << endl;
			cout << "9) Esta contenido en " << endl;
			cout << "10) No esta contenido en " << endl;
			//Esos dos ultimos no se a que se refiere xd
			cout << "Eliga la opcion: "; cin >> opcionfiltrado;
			switch (opcionfiltrado)
			{
			case 1:
				cout << "Ingrese la edad a filtrar: "; cin >> edadF;
				print(idxEdad->MayorA(edadF));
				_getch();
				break;
			case 2:
				cout << "Ingrese la edad a filtrar: "; cin >> edadF;
				print(idxEdad->MenorA(edadF));
				_getch();
				break;
			case 3:
				cout << "Ingrese la edad a filtrar: "; cin >> edadF;
				print(idxEdad->IgualA(edadF));
				_getch();
				break;
			case 4:
				cout << "¿Que genero desea mostrar?" << endl;
				cout << "M] Masculino F] Femenino" << endl;
				cin >> sexoF;
				print(idxSexo->IgualA('F'));
				_getch();
				break;
			case 5:

				_getch();
				break;
			case 6:

				_getch();
				break;
			case 7:

				_getch();
				break;
			case 8:

				_getch();
				break;
			case 9:

				_getch();
				break;
			case 10:

				_getch();
				break;
			}
		}
	}

	delete idxDni;
	delete idxApellido;
	delete idxNombre;
	delete idxEdad;
	delete idxLiga;
	delete idxClub;
	delete idxSexo;
	system("pause");
	return 0;
}