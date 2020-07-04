#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;

template<typename T1, typename T2>
constexpr auto max(T1 a, T2  b) { return (a > b ? a : b); }
#ifndef __AVL_H__
#define __AVL_H__

template<typename T, typename R = T/*, T NONE = 0*/>

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
	//void remove(R val) { remove(root, val); }



	T find(R val) { return find(root, val); }
	T MayorA(R val, function<void(T)> proc) { return MayorA(root, val, proc); }
	T MenorA(R val) { return MenorA(root, val); }
	T IgualA(R val) { return IgualA(root, val); }


	void inOrder(function<void(T)> proc) { inOrder(root, proc); }

private:

	//Operaciones bÃ¡sicas

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
	/*void    removeAux(Node*& node) {
		if (node->left == nullptr) {
			auto aux = node;
			node = node->right;
			delete aux;
		}
		else {
			node->element = max(node->left, node->right);
		}
	}
	void    remove(Node*& node, R val) {
		if (node != nullptr) {
			if (val == key(node->element)) {
				removeAux(node);
			}
			else {
				if (val < key(node->element)) {
					remove(node->left, val);
				}
				else {
					remove(node->right, val);
				}
				balance(node);
			}
		}
	}*/

	T find(Node* node, R val) {
		if (node == nullptr) {
			return "No Se Encontro";/////////////////////////AQUI AGREGUE ESTO, ME DABA ERROR EL TEMPLATE
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


	T MenorA(Node* node, R val) {
		if (node == nullptr) {
			//return NONE;
		}
		else if (val > key(node->element)) {
			return node->element;
		}
		return MenorA(node->right, val);
	}
	T IgualA(Node* node, R val) {
		if (node == nullptr) {
			//return NONE;
		}
		else if (val == key(node->element)) {
			return node->element;
		}
		return IgualA(node->right, val);
	}
	T MayorA(Node* node, R val, function<void(T)> proc) {
		/**/
		if (node == nullptr) {
			//return NONE;
		}
		else if (val < key(node->element)) {
			return node->element;
		}
		return MayorA(node->right, val, proc);

	}
	void inOrder(Node* node,
		function<void(T)> proc) {
		if (node != nullptr) {
			inOrder(node->left, proc);
			proc(node->element);
			inOrder(node->right, proc);
			//idxDni->inOrder(print);
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
//

#endif // !__AVL_H__

#ifndef __CLASECOLUMNA_H__
#define __CLASECOLUMNA_H__

template<typename T>
//template<typename T, T NADA = 0>
class ListaSimplementeEnlazada_Columna {
	struct Nodo {
		T elem;
		Nodo* next;
		Nodo(T elem = 0, Nodo* next = nullptr) : elem(elem), next(next) {}
	};
	Nodo* head;
	int len;

public:
	ListaSimplementeEnlazada_Columna() : head(nullptr), len(0) {}

	~ListaSimplementeEnlazada_Columna() {
		while (head != nullptr)
		{
			auto aux = head;
			head = head->next;
			delete aux;
		}
	}

	int size() {
		return len;
	}

	bool vacia() {
		return (len == 0);
	}

	void addInicio(T elem) {
		auto nuevo = new Nodo(elem, head);

		if (nuevo != nullptr) {
			head = nuevo;
			len++;
		}

	}
	void addPos(T elem, int pos) {
		if (pos > len || pos < 0)
			return;

		if (pos == 0)
			addInicio(elem);
		else
		{
			auto aux = head;

			for (int i = 1; i < pos; i++)
				aux = aux->next;

			auto nuevo = new Nodo(elem, aux->next);

			if (nuevo != nullptr) {
				aux->next = nuevo;
				++len;
			}

		}

	}

	void addEnd(T elem) {
		addPos(elem, len);
	}

	//MÃ©todos para eliminar
	void eliminarInicial() {
		if (len > 0) {
			auto aux = head;
			head = head->next;
			delete aux;
			--len;
		}

	}
	void eliminarPos(int pos) {

		if (pos < 0 || pos >= len)
			return;

		if (pos == 0)
			eliminarInicial();
		else {

			auto aux = head;

			for (int i = 1; i < pos; i++)
				aux = aux->next;

			auto aux2 = aux->next;
			aux->next = aux2->next;
			delete aux2;
			--len;

		}
	}

	void eliminarFinal() {
		eliminarPos(len - 1);
	}

	//MÃ©todos para buscar
	T buscarElemen(T buscar) {

		//Es lamba es opcional

		auto aux = head;

		auto lamba_comparar = [](T comp, T buscar) {

			if (comp - buscar == 0)
				return true;
			else
				return false;

		};

		while (aux != nullptr) {

			if (lamba_comparar(aux->elem, buscar))
				return aux->elem;

			aux = aux->next;

		}
		//return NADA;
	}

	//MÃ©todo para modificar 
	void modificarInicial(T nuevo, string nombre) {

		if (len > 0) {
			head->elem = nuevo;
			head->nombre = nombre;
		}


	}
	void modificarPos(T nuevo, string nombre, int pos) {

		if (pos >= 0 && pos < len) {

			auto aux = head;

			for (int i = 0; i < pos; i++)
				aux = aux->next;

			aux->elem = nuevo;
			aux->nombre = nombre;
		}

	}
	void modificarFinal(T nuevo, string nombre) {
		modificarPos(nuevo, nombre, len - 1);
	}

	//MÃ©todos get
	T getInicial() {
		getPos(0);
	}
	T getPos(int pos) {

		if (pos >= 0 && pos < len) {

			auto aux = head;

			for (int i = 0; i < pos; i++)
				aux = aux->next;

			return aux->elem;

		}
		//else
			//return ;

	}
	T getFinal() {
		getPos(len - 1);
	}

	class iterator {
		Nodo* aux;
		int pos;
	public:
		iterator(Nodo* aux, int pos)
			: aux(aux), pos(pos) {}
		bool operator!=(iterator other) {
			return pos != other.pos;
		}
		int operator++() {
			aux = aux->next;
			++pos;
			return 0;
		}
		T operator*() {
			return aux->elem;
		}
	};
	iterator begin() {
		return iterator(head, 0);
	}
	iterator end() {
		return iterator(nullptr, len);
	}

};

#endif // !__CLASECOLUMNA_H__

int main() {
	int numero_columnas = 0;
	do {
		system("cls");
		cout << "Ingrese el numero de columnas que desee[maximo 20]: ";
		cin >> numero_columnas;
	} while (numero_columnas > 20 || numero_columnas < 1);

	string nombre_columnas[20];//mÃ ximo 20. columnas, c++ no nos permite definir el tamaÃ±o del array de string
	char tipos_de_datos_columnas[20];
	for (int i = 0; i < numero_columnas; i++) {
		system("cls");
		cout << "Ingrese el numero de columnas que desee[maximo 20]: " << numero_columnas << endl;
		cout << "Ingrese el nombre de la columna " << i + 1 << " : ";
		cin >> nombre_columnas[i];
	}

	system("cls");

	for (int j = 0; j < numero_columnas; j++) {
		system("cls");
		cout << "Ingrese el tipo de dato de la columna '" << nombre_columnas[j] << "' [c:letras, i: enteros, f: flotanes]: ";
		cin >> tipos_de_datos_columnas[j];
	}

	//Crear columnas
	//Columna 01

	ListaSimplementeEnlazada_Columna<string>* columna1S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna1I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna1F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 02

	ListaSimplementeEnlazada_Columna<string>* columna2S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna2I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna2F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 03

	ListaSimplementeEnlazada_Columna<string>* columna3S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna3I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna3F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 04

	ListaSimplementeEnlazada_Columna<string>* columna4S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna4I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna4F = new ListaSimplementeEnlazada_Columna<float>();


	//Columna 05

	ListaSimplementeEnlazada_Columna<string>* columna5S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna5I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna5F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 06

	ListaSimplementeEnlazada_Columna<string>* columna6S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna6I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna6F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 07


	ListaSimplementeEnlazada_Columna<string>* columna7S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna7I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna7F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 08


	ListaSimplementeEnlazada_Columna<string>* columna8S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna8I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna8F = new ListaSimplementeEnlazada_Columna<float>();



	//Columna 09

	ListaSimplementeEnlazada_Columna<string>* columna9S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna9I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna9F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 10


	ListaSimplementeEnlazada_Columna<string>* columna10S = new ListaSimplementeEnlazada_Columna<string>();


	ListaSimplementeEnlazada_Columna<int>* columna10I = new ListaSimplementeEnlazada_Columna<int>();


	ListaSimplementeEnlazada_Columna<float>* columna10F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 11


	ListaSimplementeEnlazada_Columna<string>* columna11S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna11I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna11F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 12


	ListaSimplementeEnlazada_Columna<string>* columna12S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna12I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna12F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 13

	ListaSimplementeEnlazada_Columna<string>* columna13S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna13I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna13F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 14

	ListaSimplementeEnlazada_Columna<string>* columna14S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna14I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna14F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 15

	ListaSimplementeEnlazada_Columna<string>* columna15S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna15I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna15F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 16

	ListaSimplementeEnlazada_Columna<string>* columna16S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna16I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna16F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 17

	ListaSimplementeEnlazada_Columna<string>* columna17S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna17I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna17F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 18


	ListaSimplementeEnlazada_Columna<string>* columna18S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna18I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna18F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 19

	ListaSimplementeEnlazada_Columna<string>* columna19S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna19I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna19F = new ListaSimplementeEnlazada_Columna<float>();

	//Columna 20


	ListaSimplementeEnlazada_Columna<string>* columna20S = new ListaSimplementeEnlazada_Columna<string>();

	ListaSimplementeEnlazada_Columna<int>* columna20I = new ListaSimplementeEnlazada_Columna<int>();

	ListaSimplementeEnlazada_Columna<float>* columna20F = new ListaSimplementeEnlazada_Columna<float>();


	int opcion = 20;
	string elemString;
	int elemInt;
	float elemFloat;

	int numFilas = 0;
	ofstream trabajofinal;
	ifstream trabajofinalB;

	int pos_eliminar = 50;

	//Para ordenar
	int opc_ordenar = 50;
	AVLBST<string>* arbolOrd_String = new AVLBST<string>();
	auto print = [](string x) { cout << x << endl; };

	//Para buscar
	int col_buscar = 50;
	string buscar_elemento;

	//Filtros
	string datoE;

	while (opcion != 0) {
		system("cls");
		cout << endl << "-|-|-|-|-|-|-TF-|-|-|-|-|-|-" << endl;
		cout << "1) Agregar fila" << endl;
		cout << "2) Eliminar fila" << endl;
		cout << "3) Buscar" << endl;
		cout << "4) Mostrar por orden" << endl;
		cout << "5) Filtrado de datos" << endl;
		cout << "6) Mostrar tabla " << endl;
		cout << "7) Exportar datos" << endl;
		cout << "8) Llenar tabla automaticamente..." << endl;
		cout << "0) Cerrar lista" << endl;

		cout << endl << "Selecciona una opcion: ";
		cin >> opcion;
		system("cls");
		int edadF;
		switch (opcion)
		{
		case 0:
			break;
		case 1:
			//Solo basta entender el primer caso, el resto es lo mismo
			for (int i = 0; i < numero_columnas; i++) {
				//Columna 01
				if (i == 0) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna1S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna1I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna1F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 02
				if (i == 1) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna2S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna2I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna2F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 03
				if (i == 2) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna3S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna3I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna3F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 04
				if (i == 3) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna4S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna4I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna4F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}
				//Columna 05
				if (i == 4) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna5S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna5I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna5F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 06
				if (i == 5) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna6S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna6I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna6F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 07
				if (i == 6) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna7S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna7I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna7F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 08
				if (i == 7) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna8S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna8I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna8F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 09
				if (i == 8) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna9S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna9I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna9F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 10
				if (i == 9) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna10S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna10I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna10F->addPos(elemFloat, numFilas)
							;
						system("cls");
					}
				}

				//Columna 11
				if (i == 10) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna11S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna11I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna11F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 12
				if (i == 11) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna12S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna12I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna12F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 13
				if (i == 12) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna13S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna13I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna13F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 14
				if (i == 13) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna14S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna14I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna14F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 15
				if (i == 14) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna15S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna15I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna15F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 16
				if (i == 15) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna16S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna16I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna16F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 17
				if (i == 16) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna17S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna17I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna17F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 18
				if (i == 17) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna18S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna18I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna18F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 19
				if (i == 18) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna19S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna19I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna19F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}

				//Columna 20
				if (i == 19) {
					if (tipos_de_datos_columnas[i] == 'c' || tipos_de_datos_columnas[i] == 'C') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemString;

						columna20S->addPos(elemString, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'I' || tipos_de_datos_columnas[i] == 'i') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemInt;

						columna20I->addPos(elemInt, numFilas);

						system("cls");
					}

					if (tipos_de_datos_columnas[i] == 'F' || tipos_de_datos_columnas[i] == 'f') {
						cout << "Ingrese dato para la fila " << numFilas + 1 << ", columna " << nombre_columnas[i] << " : ";
						cin >> elemFloat;

						columna20F->addPos(elemFloat, numFilas);

						system("cls");
					}
				}



			}

			numFilas++;
			break;
		case 2:
			if (numFilas == 0) {
				system("cls");
				cout << "No hay elementos por eliminar" << endl;
				_getch();
				break;
			}

			do {
				system("cls");
				cout << "Ingrese numero de fila a eliminar: ";
				cin >> pos_eliminar;

				if (pos_eliminar > numFilas) {
					cout << "\Numero de fila no valido" << endl;
					_getch();
				}

			} while (pos_eliminar > numFilas || pos_eliminar < 0);

			if (5 == 5) {
				//Columna 1
				columna1S->eliminarPos(pos_eliminar);
				columna1I->eliminarPos(pos_eliminar);
				columna1F->eliminarPos(pos_eliminar);

				//Columna 2
				columna2S->eliminarPos(pos_eliminar);
				columna2I->eliminarPos(pos_eliminar);
				columna2F->eliminarPos(pos_eliminar);

				//Columna 3
				columna3S->eliminarPos(pos_eliminar);
				columna3I->eliminarPos(pos_eliminar);
				columna3F->eliminarPos(pos_eliminar);

				//Columna 4
				columna4S->eliminarPos(pos_eliminar);
				columna4I->eliminarPos(pos_eliminar);
				columna4F->eliminarPos(pos_eliminar);

				//Columna 5
				columna5S->eliminarPos(pos_eliminar);
				columna5I->eliminarPos(pos_eliminar);
				columna5F->eliminarPos(pos_eliminar);

				//Columna 6
				columna6S->eliminarPos(pos_eliminar);
				columna6I->eliminarPos(pos_eliminar);
				columna6F->eliminarPos(pos_eliminar);

				//Columna 7
				columna7S->eliminarPos(pos_eliminar);
				columna7I->eliminarPos(pos_eliminar);
				columna7F->eliminarPos(pos_eliminar);

				//Columna 8
				columna8S->eliminarPos(pos_eliminar);
				columna8I->eliminarPos(pos_eliminar);
				columna8F->eliminarPos(pos_eliminar);

				//Columna 9
				columna9S->eliminarPos(pos_eliminar);
				columna9I->eliminarPos(pos_eliminar);
				columna9F->eliminarPos(pos_eliminar);

				//Columna 10
				columna10S->eliminarPos(pos_eliminar);
				columna10I->eliminarPos(pos_eliminar);
				columna10F->eliminarPos(pos_eliminar);

				//Columna 11
				columna11S->eliminarPos(pos_eliminar);
				columna11I->eliminarPos(pos_eliminar);
				columna11F->eliminarPos(pos_eliminar);

				//Columna 12
				columna12S->eliminarPos(pos_eliminar);
				columna12I->eliminarPos(pos_eliminar);
				columna12F->eliminarPos(pos_eliminar);

				//Columna 13
				columna13S->eliminarPos(pos_eliminar);
				columna13I->eliminarPos(pos_eliminar);
				columna13F->eliminarPos(pos_eliminar);

				//Columna 14
				columna14S->eliminarPos(pos_eliminar);
				columna14I->eliminarPos(pos_eliminar);
				columna14F->eliminarPos(pos_eliminar);

				//Columna 15
				columna15S->eliminarPos(pos_eliminar);
				columna15I->eliminarPos(pos_eliminar);
				columna15F->eliminarPos(pos_eliminar);

				//Columna 16
				columna16S->eliminarPos(pos_eliminar);
				columna16I->eliminarPos(pos_eliminar);
				columna16F->eliminarPos(pos_eliminar);

				//Columna 17
				columna17S->eliminarPos(pos_eliminar);
				columna17I->eliminarPos(pos_eliminar);
				columna17F->eliminarPos(pos_eliminar);

				//Columna 18
				columna18S->eliminarPos(pos_eliminar);
				columna18I->eliminarPos(pos_eliminar);
				columna18F->eliminarPos(pos_eliminar);

				//Columna 19
				columna19S->eliminarPos(pos_eliminar);
				columna19I->eliminarPos(pos_eliminar);
				columna19F->eliminarPos(pos_eliminar);

				//Columna 20
				columna20S->eliminarPos(pos_eliminar);
				columna20I->eliminarPos(pos_eliminar);
				columna20F->eliminarPos(pos_eliminar);

				numFilas--;

			}

			break;

		case 3:
			do {
				system("cls");
				for (int i = 0; i < numero_columnas; i++) {
					cout << "Columna " << i << " '" << nombre_columnas[i] << "'" << endl;
				}

				cout << "Indique la columna en la que quiere buscar : ";
				cin >> col_buscar;

			} while (col_buscar < 0 || col_buscar > numero_columnas);

			for (int i = 0; i < numero_columnas; i++) {
				if (i == col_buscar) {

					if (tipos_de_datos_columnas[i] == 'C' || tipos_de_datos_columnas[i] == 'c') {
						for (int j = 0; j < numFilas; j++) {
							switch (col_buscar)
							{
							case 0:
								arbolOrd_String->add(columna1S->getPos(j));
								break;
							case 1:
								arbolOrd_String->add(columna2S->getPos(j));
								break;
							case 2:
								arbolOrd_String->add(columna3S->getPos(j));
								break;
							case 3:
								arbolOrd_String->add(columna4S->getPos(j));
								break;
							case 4:
								arbolOrd_String->add(columna5S->getPos(j));
								break;
							case 5:
								arbolOrd_String->add(columna6S->getPos(j));
								break;
							case 6:
								arbolOrd_String->add(columna7S->getPos(j));
								break;
							case 7:
								arbolOrd_String->add(columna8S->getPos(j));
								break;
							case 8:
								arbolOrd_String->add(columna9S->getPos(j));
								break;
							case 9:
								arbolOrd_String->add(columna10S->getPos(j));
								break;
							case 10:
								arbolOrd_String->add(columna11S->getPos(j));
								break;
							case 11:
								arbolOrd_String->add(columna12S->getPos(j));
								break;
							case 12:
								arbolOrd_String->add(columna13S->getPos(j));
								break;
							case 13:
								arbolOrd_String->add(columna14S->getPos(j));
								break;
							case 14:
								arbolOrd_String->add(columna15S->getPos(j));
								break;
							case 15:
								arbolOrd_String->add(columna16S->getPos(j));
								break;
							case 16:
								arbolOrd_String->add(columna17S->getPos(j));
								break;
							case 17:
								arbolOrd_String->add(columna18S->getPos(j));
								break;
							case 18:
								arbolOrd_String->add(columna19S->getPos(j));
								break;
							case 19:
								arbolOrd_String->add(columna20S->getPos(j));
								break;
							}

						}
					}

					if (tipos_de_datos_columnas[i] == 'i' || tipos_de_datos_columnas[i] == 'I') {
						for (int j = 0; j < numFilas; j++) {
							switch (col_buscar)
							{
							case 0:
								arbolOrd_String->add(to_string(columna1I->getPos(j)));
								break;
							case 1:
								arbolOrd_String->add(to_string(columna2I->getPos(j)));
								break;
							case 2:
								arbolOrd_String->add(to_string(columna3I->getPos(j)));
								break;
							case 3:
								arbolOrd_String->add(to_string(columna4I->getPos(j)));
								break;
							case 4:
								arbolOrd_String->add(to_string(columna5I->getPos(j)));
								break;
							case 5:
								arbolOrd_String->add(to_string(columna6I->getPos(j)));
								break;
							case 6:
								arbolOrd_String->add(to_string(columna7I->getPos(j)));
								break;
							case 7:
								arbolOrd_String->add(to_string(columna8I->getPos(j)));
								break;
							case 8:
								arbolOrd_String->add(to_string(columna9I->getPos(j)));
								break;
							case 9:
								arbolOrd_String->add(to_string(columna10I->getPos(j)));
								break;
							case 10:
								arbolOrd_String->add(to_string(columna11I->getPos(j)));
								break;
							case 11:
								arbolOrd_String->add(to_string(columna12I->getPos(j)));
							case 12:
								arbolOrd_String->add(to_string(columna13I->getPos(j)));
								break;
							case 13:
								arbolOrd_String->add(to_string(columna14I->getPos(j)));
								break;
							case 14:
								arbolOrd_String->add(to_string(columna15I->getPos(j)));
								break;
							case 15:
								arbolOrd_String->add(to_string(columna16I->getPos(j)));
								break;
							case 16:
								arbolOrd_String->add(to_string(columna17I->getPos(j)));
								break;
							case 17:
								arbolOrd_String->add(to_string(columna18I->getPos(j)));
								break;
							case 18:
								arbolOrd_String->add(to_string(columna19I->getPos(j)));
								break;
							case 19:
								arbolOrd_String->add(to_string(columna20I->getPos(j)));
								break;
							}
						}
					}

					if (tipos_de_datos_columnas[i] == 'f' || tipos_de_datos_columnas[i] == 'F') {
						for (int j = 0; j < numFilas; j++) {
							switch (col_buscar)
							{
							case 0:
								arbolOrd_String->add(to_string(columna1F->getPos(j)));
								break;
							case 1:
								arbolOrd_String->add(to_string(columna2F->getPos(j)));
								break;
							case 2:
								arbolOrd_String->add(to_string(columna3F->getPos(j)));
								break;
							case 3:
								arbolOrd_String->add(to_string(columna4F->getPos(j)));
								break;
							case 4:
								arbolOrd_String->add(to_string(columna5F->getPos(j)));
								break;
							case 5:
								arbolOrd_String->add(to_string(columna6F->getPos(j)));
								break;
							case 6:
								arbolOrd_String->add(to_string(columna7F->getPos(j)));
								break;
							case 7:
								arbolOrd_String->add(to_string(columna8F->getPos(j)));
								break;
							case 8:
								arbolOrd_String->add(to_string(columna9F->getPos(j)));
								break;
							case 9:
								arbolOrd_String->add(to_string(columna10F->getPos(j)));
								break;
							case 10:
								arbolOrd_String->add(to_string(columna11F->getPos(j)));
								break;
							case 11:
								arbolOrd_String->add(to_string(columna12F->getPos(j)));
							case 12:
								arbolOrd_String->add(to_string(columna13F->getPos(j)));
								break;
							case 13:
								arbolOrd_String->add(to_string(columna14F->getPos(j)));
								break;
							case 14:
								arbolOrd_String->add(to_string(columna15F->getPos(j)));
								break;
							case 15:
								arbolOrd_String->add(to_string(columna16F->getPos(j)));
								break;
							case 16:
								arbolOrd_String->add(to_string(columna17F->getPos(j)));
								break;
							case 17:
								arbolOrd_String->add(to_string(columna18F->getPos(j)));
								break;
							case 18:
								arbolOrd_String->add(to_string(columna19F->getPos(j)));
								break;
							case 19:
								arbolOrd_String->add(to_string(columna20F->getPos(j)));
								break;
							}
						}
					}
				}
			}

			system("cls");

			for (int i = 0; i < numero_columnas; i++) {

				if (i == col_buscar) {
					cout << "Ingrese el dato de la columna '" << nombre_columnas[i] << "' para buscar: ";
					cin >> buscar_elemento;
					break;
				}
			}

			if (arbolOrd_String->find(buscar_elemento) != "No Se Encontro") {
				cout << "Si se encontro dicho elemento: " << arbolOrd_String->find(buscar_elemento);
			}
			else {
				cout << "Lo sentimos, no se encontro dicho elemento, intente digitar otra vez";
			}

			arbolOrd_String->clear();
			_getch();
			break;

		case 4:
			do {
				system("cls");
				for (int i = 0; i < numero_columnas; i++) {
					cout << "Ordenar por " << i << " '" << nombre_columnas[i] << "'" << endl;
				}

				cout << "Indique como quiere ordenar los datos: ";
				cin >> opc_ordenar;

			} while (opc_ordenar < 0 || opc_ordenar > numero_columnas);

			for (int i = 0; i < numero_columnas; i++) {
				if (i == opc_ordenar) {

					if (tipos_de_datos_columnas[i] == 'C' || tipos_de_datos_columnas[i] == 'c') {
						for (int j = 0; j < numFilas; j++) {
							switch (opc_ordenar)
							{
							case 0:
								arbolOrd_String->add(columna1S->getPos(j));
								break;
							case 1:
								arbolOrd_String->add(columna2S->getPos(j));
								break;
							case 2:
								arbolOrd_String->add(columna3S->getPos(j));
								break;
							case 3:
								arbolOrd_String->add(columna4S->getPos(j));
								break;
							case 4:
								arbolOrd_String->add(columna5S->getPos(j));
								break;
							case 5:
								arbolOrd_String->add(columna6S->getPos(j));
								break;
							case 6:
								arbolOrd_String->add(columna7S->getPos(j));
								break;
							case 7:
								arbolOrd_String->add(columna8S->getPos(j));
								break;
							case 8:
								arbolOrd_String->add(columna9S->getPos(j));
								break;
							case 9:
								arbolOrd_String->add(columna10S->getPos(j));
								break;
							case 10:
								arbolOrd_String->add(columna11S->getPos(j));
								break;
							case 11:
								arbolOrd_String->add(columna12S->getPos(j));
								break;
							case 12:
								arbolOrd_String->add(columna13S->getPos(j));
								break;
							case 13:
								arbolOrd_String->add(columna14S->getPos(j));
								break;
							case 14:
								arbolOrd_String->add(columna15S->getPos(j));
								break;
							case 15:
								arbolOrd_String->add(columna16S->getPos(j));
								break;
							case 16:
								arbolOrd_String->add(columna17S->getPos(j));
								break;
							case 17:
								arbolOrd_String->add(columna18S->getPos(j));
								break;
							case 18:
								arbolOrd_String->add(columna19S->getPos(j));
								break;
							case 19:
								arbolOrd_String->add(columna20S->getPos(j));
								break;
							}

						}
					}

					if (tipos_de_datos_columnas[i] == 'i' || tipos_de_datos_columnas[i] == 'I') {
						for (int j = 0; j < numFilas; j++) {
							switch (opc_ordenar)
							{
							case 0:
								arbolOrd_String->add(to_string(columna1I->getPos(j)));
								break;
							case 1:
								arbolOrd_String->add(to_string(columna2I->getPos(j)));
								break;
							case 2:
								arbolOrd_String->add(to_string(columna3I->getPos(j)));
								break;
							case 3:
								arbolOrd_String->add(to_string(columna4I->getPos(j)));
								break;
							case 4:
								arbolOrd_String->add(to_string(columna5I->getPos(j)));
								break;
							case 5:
								arbolOrd_String->add(to_string(columna6I->getPos(j)));
								break;
							case 6:
								arbolOrd_String->add(to_string(columna7I->getPos(j)));
								break;
							case 7:
								arbolOrd_String->add(to_string(columna8I->getPos(j)));
								break;
							case 8:
								arbolOrd_String->add(to_string(columna9I->getPos(j)));
								break;
							case 9:
								arbolOrd_String->add(to_string(columna10I->getPos(j)));
								break;
							case 10:
								arbolOrd_String->add(to_string(columna11I->getPos(j)));
								break;
							case 11:
								arbolOrd_String->add(to_string(columna12I->getPos(j)));
							case 12:
								arbolOrd_String->add(to_string(columna13I->getPos(j)));
								break;
							case 13:
								arbolOrd_String->add(to_string(columna14I->getPos(j)));
								break;
							case 14:
								arbolOrd_String->add(to_string(columna15I->getPos(j)));
								break;
							case 15:
								arbolOrd_String->add(to_string(columna16I->getPos(j)));
								break;
							case 16:
								arbolOrd_String->add(to_string(columna17I->getPos(j)));
								break;
							case 17:
								arbolOrd_String->add(to_string(columna18I->getPos(j)));
								break;
							case 18:
								arbolOrd_String->add(to_string(columna19I->getPos(j)));
								break;
							case 19:
								arbolOrd_String->add(to_string(columna20I->getPos(j)));
								break;
							}
						}
					}

					if (tipos_de_datos_columnas[i] == 'f' || tipos_de_datos_columnas[i] == 'F') {
						for (int j = 0; j < numFilas; j++) {
							switch (opc_ordenar)
							{
							case 0:
								arbolOrd_String->add(to_string(columna1F->getPos(j)));
								break;
							case 1:
								arbolOrd_String->add(to_string(columna2F->getPos(j)));
								break;
							case 2:
								arbolOrd_String->add(to_string(columna3F->getPos(j)));
								break;
							case 3:
								arbolOrd_String->add(to_string(columna4F->getPos(j)));
								break;
							case 4:
								arbolOrd_String->add(to_string(columna5F->getPos(j)));
								break;
							case 5:
								arbolOrd_String->add(to_string(columna6F->getPos(j)));
								break;
							case 6:
								arbolOrd_String->add(to_string(columna7F->getPos(j)));
								break;
							case 7:
								arbolOrd_String->add(to_string(columna8F->getPos(j)));
								break;
							case 8:
								arbolOrd_String->add(to_string(columna9F->getPos(j)));
								break;
							case 9:
								arbolOrd_String->add(to_string(columna10F->getPos(j)));
								break;
							case 10:
								arbolOrd_String->add(to_string(columna11F->getPos(j)));
								break;
							case 11:
								arbolOrd_String->add(to_string(columna12F->getPos(j)));
							case 12:
								arbolOrd_String->add(to_string(columna13F->getPos(j)));
								break;
							case 13:
								arbolOrd_String->add(to_string(columna14F->getPos(j)));
								break;
							case 14:
								arbolOrd_String->add(to_string(columna15F->getPos(j)));
								break;
							case 15:
								arbolOrd_String->add(to_string(columna16F->getPos(j)));
								break;
							case 16:
								arbolOrd_String->add(to_string(columna17F->getPos(j)));
								break;
							case 17:
								arbolOrd_String->add(to_string(columna18F->getPos(j)));
								break;
							case 18:
								arbolOrd_String->add(to_string(columna19F->getPos(j)));
								break;
							case 19:
								arbolOrd_String->add(to_string(columna20F->getPos(j)));
								break;
							}
						}
					}
				}
			}
			system("cls");

			arbolOrd_String->inOrder(print);

			_getch();
			arbolOrd_String->clear();
			break;

		case 5:
			cout << "|-| Filtrado de datos |-|" << endl;

			cout << "1) Numero mayor a " << endl;
			cout << "2) Numero menor a " << endl;
			cout << "3) Numero igual a " << endl;
			cout << "4) Pertenece a..." << endl;
			cout << "5) No pertenece a..." << endl;
			cout << "Elija una opcion: "; cin >> opcion;
			if (opcion >= 6) cout << "OPCION INCORRECTA" << endl;

			cout << endl;
			if (opcion == 1)
			{
				cout << "Que edad desea filtrar? " << endl;
				cin >> edadF;
				cout << "\t\t.:TABLA:." << endl;
				cout << "\t";
				for (auto f : nombre_columnas) {
					cout << f << "    \t      ";
				}

				cout << endl;

				for (int i = 0; i < numFilas; i++) {
					cout << i << "\t";

					if (i == ((numFilas - numFilas) + i)) {
						//Columna 1

						if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {

							if (columna1I->getPos(i) >= edadF) {
								cout << columna1I->getPos(i);

								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}

								//Columna 3

								if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
								cout << "    \t      ";
								cout << endl;
							}
						}

						//Columna 2

						if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
							if (columna2I->getPos(i) >= edadF)
							{

								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna1I->getPos(i);
									//if(columna1F->getPos(i) == 12){}
									cout << "    \t      ";
								}

								//Columna 2
								cout << columna2I->getPos(i);
								cout << "     \t     ";

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna1F->getPos(i);
									cout << "    \t      ";
								}


								//Columna 3

								if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
							}
							cout << endl;
						}

						//Columna 3

						if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
							if (columna3I->getPos(i) >= edadF)
							{

								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna1I->getPos(i);
									//if(columna1F->getPos(i) == 12){}
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna1F->getPos(i);
									cout << "    \t      ";
								}

								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna3
								cout << columna3I->getPos(i);
								cout << "     \t     ";

							}
							cout << endl;
						}
					}
				}
			}
			if (opcion == 2)
			{
				cout << "Que edad desea filtrar? " << endl;
				cin >> edadF;
				cout << "\t\t.:TABLA:." << endl;
				cout << "\t";
				for (auto f : nombre_columnas) {
					cout << f << "    \t      ";
				}

				cout << endl;

				for (int i = 0; i < numFilas; i++) {
					cout << i << "\t";

					if (i == ((numFilas - numFilas) + i)) {
						//Columna 1

						if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {

							if (columna1I->getPos(i) <= edadF) {
								cout << columna1I->getPos(i);

								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}

								//Columna 3

								if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
								cout << "    \t      ";
								cout << endl;
							}
						}

						//Columna 2

						if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
							if (columna2I->getPos(i) <= edadF)
							{

								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna1I->getPos(i);
									//if(columna1F->getPos(i) == 12){}
									cout << "    \t      ";
								}

								//Columna 2
								cout << columna2I->getPos(i);
								cout << "     \t     ";

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna1F->getPos(i);
									cout << "    \t      ";
								}


								//Columna 3

								if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
							}
							cout << endl;
						}

						//Columna 3

						if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
							if (columna3I->getPos(i) <= edadF)
							{

								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna1I->getPos(i);
									//if(columna1F->getPos(i) == 12){}
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna1F->getPos(i);
									cout << "    \t      ";
								}

								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna3
								cout << columna3I->getPos(i);
								cout << "     \t     ";

							}
							cout << endl;
						}
					}
				}
			}
			if (opcion == 3)
			{
				cout << "Que edad desea filtrar? " << endl;
				cin >> edadF;
				cout << "\t\t.:TABLA:." << endl;
				cout << "\t";
				for (auto f : nombre_columnas) {
					cout << f << "    \t      ";
				}

				cout << endl;

				for (int i = 0; i < numFilas; i++) {
					cout << i << "\t";

					if (i == ((numFilas - numFilas) + i)) {
						//Columna 1

						if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {

							if (columna1I->getPos(i) == edadF) {
								cout << columna1I->getPos(i);

								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}

								//Columna 3

								if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
								cout << "    \t      ";
								cout << endl;
							}
						}

						//Columna 2

						if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
							if (columna2I->getPos(i) == edadF)
							{

								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna1I->getPos(i);
									//if(columna1F->getPos(i) == 12){}
									cout << "    \t      ";
								}

								//Columna 2
								cout << columna2I->getPos(i);
								cout << "     \t     ";

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna1F->getPos(i);
									cout << "    \t      ";
								}


								//Columna 3

								if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
							}
							cout << endl;
						}

						//Columna 3

						if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
							if (columna3I->getPos(i) == edadF)
							{

								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna1I->getPos(i);
									//if(columna1F->getPos(i) == 12){}
									cout << "    \t      ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna1F->getPos(i);
									cout << "    \t      ";
								}

								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna3
								cout << columna3I->getPos(i);
								cout << "     \t     ";

							}
							cout << endl;
						}
					}
				}
			}

			if (opcion == 4)
			{
				cout << "Que columna desea filtrar?";
				cin >> opcion;
				if (opcion == 0)
				{
					cout << "Ingreso el dato a filtrar en la columna " << nombre_columnas[0] << " :"; cin >> datoE; cout << endl;

					cout << "\t\t.:TABLA:." << endl;
					cout << "\t";
					for (auto f : nombre_columnas) {
						cout << f << "    \t      ";
					}

					cout << endl;

					for (int i = 0; i < numFilas; i++) {
						cout << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {

								if (columna1S->getPos(i) == datoE) {
									cout << columna1S->getPos(i);

									//Columna 2

									if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
										cout << columna2S->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
										cout << columna2I->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
										cout << columna2F->getPos(i);
										cout << "    \t      ";
									}

									//Columna 3

									if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
										cout << columna3S->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
										cout << columna3I->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
										cout << columna3F->getPos(i);
										cout << "     \t     ";
									}
									cout << "    \t      ";
									cout << endl;
								}
							}
						}
					}

				}
				if (opcion == 1)
				{
					cout << "Ingreso el dato a filtrar en la columna " << nombre_columnas[1] << " :"; cin >> datoE; cout << endl;

					cout << "\t\t.:TABLA:." << endl;
					cout << "\t";
					for (auto f : nombre_columnas) {
						cout << f << "    \t      ";
					}

					cout << endl;

					for (int i = 0; i < numFilas; i++) {
						cout << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {



								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna 2
								if (columna1S->getPos(i) == datoE) {
									cout << columna1S->getPos(i);
									//Columna 3

									if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
										cout << columna3S->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
										cout << columna3I->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
										cout << columna3F->getPos(i);
										cout << "     \t     ";
									}
									cout << "    \t      ";
									cout << endl;
								}
							}
						}
					}
				}
				if (opcion == 2)
				{
					cout << "Ingreso el dato a filtrar en la columna " << nombre_columnas[2] << " :"; cin >> datoE; cout << endl;

					cout << "\t\t.:TABLA:." << endl;
					cout << "\t";
					for (auto f : nombre_columnas) {
						cout << f << "    \t      ";
					}

					cout << endl;

					for (int i = 0; i < numFilas; i++) {
						cout << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {



								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
								//Columna 3
								if (columna1S->getPos(i) == datoE) {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
									cout << endl;
								}
							}
						}
					}

				}
			}
			if (opcion == 5) {
				cout << "Que columna desea filtrar?";
				cin >> opcion;
				if (opcion == 0)
				{
					cout << "Ingreso el dato a filtrar en la columna " << nombre_columnas[0] << " :"; cin >> datoE; cout << endl;

					cout << "\t\t.:TABLA:." << endl;
					cout << "\t";
					for (auto f : nombre_columnas) {
						cout << f << "    \t      ";
					}

					cout << endl;

					for (int i = 0; i < numFilas; i++) {
						cout << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {

								if (columna1S->getPos(i) != datoE) {
									cout << columna1S->getPos(i);

									//Columna 2

									if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
										cout << columna2S->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
										cout << columna2I->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
										cout << columna2F->getPos(i);
										cout << "    \t      ";
									}

									//Columna 3

									if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
										cout << columna3S->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
										cout << columna3I->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
										cout << columna3F->getPos(i);
										cout << "     \t     ";
									}
									cout << "    \t      ";
									cout << endl;
								}
							}
						}
					}

				}
				if (opcion == 1)
				{
					cout << "Ingreso el dato a filtrar en la columna " << nombre_columnas[1] << " :"; cin >> datoE; cout << endl;

					cout << "\t\t.:TABLA:." << endl;
					cout << "\t";
					for (auto f : nombre_columnas) {
						cout << f << "    \t      ";
					}

					cout << endl;

					for (int i = 0; i < numFilas; i++) {
						cout << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {



								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna 2
								if (columna1S->getPos(i) != datoE) {
									cout << columna1S->getPos(i);
									//Columna 3

									if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
										cout << columna3S->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
										cout << columna3I->getPos(i);
										cout << "     \t     ";
									}

									if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
										cout << columna3F->getPos(i);
										cout << "     \t     ";
									}
									cout << "    \t      ";
									cout << endl;
								}
							}
						}
					}
				}
				if (opcion == 2)
				{
					cout << "Ingreso el dato a filtrar en la columna " << nombre_columnas[2] << " :"; cin >> datoE; cout << endl;

					cout << "\t\t.:TABLA:." << endl;
					cout << "\t";
					for (auto f : nombre_columnas) {
						cout << f << "    \t      ";
					}

					cout << endl;

					for (int i = 0; i < numFilas; i++) {
						cout << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {



								//Columna 1

								if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
									cout << columna2S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
									cout << columna2I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
									cout << columna2F->getPos(i);
									cout << "    \t      ";
								}
								//Columna 2

								if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
									cout << columna3S->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
									cout << columna3I->getPos(i);
									cout << "     \t     ";
								}

								if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
									cout << columna3F->getPos(i);
									cout << "     \t     ";
								}
								//Columna 3
								if (columna1S->getPos(i) != datoE) {
									cout << columna1S->getPos(i);
									cout << "    \t      ";
									cout << endl;
								}
							}
						}
					}

				}
			}
			_getch();
			break;

		case 6:

			cout << "\t\t.:TABLA:." << endl;
			cout << "\t";
			for (auto f : nombre_columnas) {
				cout << f << "    \t      ";
			}

			cout << endl;

			for (int i = 0; i < numFilas; i++) {
				cout << i << "\t";

				if (i == ((numFilas - numFilas) + i)) {
					//Columna 1

					if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
						cout << columna1S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
						cout << columna1I->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
						cout << columna1F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 2

					if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
						cout << columna2S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
						cout << columna2I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
						cout << columna2F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 3

					if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
						cout << columna3S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
						cout << columna3I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
						cout << columna3F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 4

					if (tipos_de_datos_columnas[3] == 'c' || tipos_de_datos_columnas[3] == 'C') {
						cout << columna4S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[3] == 'i' || tipos_de_datos_columnas[3] == 'I') {
						cout << columna4I->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[3] == 'f' || tipos_de_datos_columnas[3] == 'F') {
						cout << columna4F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 5

					if (tipos_de_datos_columnas[4] == 'c' || tipos_de_datos_columnas[4] == 'C') {
						cout << columna5S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[4] == 'i' || tipos_de_datos_columnas[4] == 'I') {
						cout << columna5I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[4] == 'f' || tipos_de_datos_columnas[4] == 'F') {
						cout << columna5F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 6

					if (tipos_de_datos_columnas[5] == 'c' || tipos_de_datos_columnas[5] == 'C') {
						cout << columna6S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[5] == 'i' || tipos_de_datos_columnas[5] == 'I') {
						cout << columna6I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[5] == 'f' || tipos_de_datos_columnas[5] == 'F') {
						cout << columna6F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 7

					if (tipos_de_datos_columnas[6] == 'c' || tipos_de_datos_columnas[6] == 'C') {
						cout << columna7S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[6] == 'i' || tipos_de_datos_columnas[6] == 'I') {
						cout << columna7I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[6] == 'f' || tipos_de_datos_columnas[6] == 'F') {
						cout << columna7F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 8

					if (tipos_de_datos_columnas[7] == 'c' || tipos_de_datos_columnas[7] == 'C') {
						cout << columna8S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[7] == 'i' || tipos_de_datos_columnas[7] == 'I') {
						cout << columna8I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[7] == 'f' || tipos_de_datos_columnas[7] == 'F') {
						cout << columna8F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 9

					if (tipos_de_datos_columnas[8] == 'c' || tipos_de_datos_columnas[8] == 'C') {
						cout << columna9S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[8] == 'i' || tipos_de_datos_columnas[8] == 'I') {
						cout << columna9I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[8] == 'f' || tipos_de_datos_columnas[8] == 'F') {
						cout << columna9F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 10

					if (tipos_de_datos_columnas[9] == 'c' || tipos_de_datos_columnas[9] == 'C') {
						cout << columna10S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[9] == 'i' || tipos_de_datos_columnas[9] == 'I') {
						cout << columna10I->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[9] == 'f' || tipos_de_datos_columnas[9] == 'F') {
						cout << columna10F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 11

					if (tipos_de_datos_columnas[10] == 'c' || tipos_de_datos_columnas[10] == 'C') {
						cout << columna11S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[10] == 'i' || tipos_de_datos_columnas[10] == 'I') {
						cout << columna11I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[10] == 'f' || tipos_de_datos_columnas[10] == 'F') {
						cout << columna11F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 12

					if (tipos_de_datos_columnas[11] == 'c' || tipos_de_datos_columnas[11] == 'C') {
						cout << columna12S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[11] == 'i' || tipos_de_datos_columnas[11] == 'I') {
						cout << columna12I->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[11] == 'f' || tipos_de_datos_columnas[11] == 'F') {
						cout << columna12F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 13

					if (tipos_de_datos_columnas[12] == 'c' || tipos_de_datos_columnas[12] == 'C') {
						cout << columna13S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[12] == 'i' || tipos_de_datos_columnas[12] == 'I') {
						cout << columna13I->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[12] == 'f' || tipos_de_datos_columnas[12] == 'F') {
						cout << columna13F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 14

					if (tipos_de_datos_columnas[13] == 'c' || tipos_de_datos_columnas[13] == 'C') {
						cout << columna14S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[13] == 'i' || tipos_de_datos_columnas[13] == 'I') {
						cout << columna14I->getPos(i);
						cout << "   \t       ";
					}

					if (tipos_de_datos_columnas[13] == 'f' || tipos_de_datos_columnas[13] == 'F') {
						cout << columna14F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 15

					if (tipos_de_datos_columnas[14] == 'c' || tipos_de_datos_columnas[14] == 'C') {
						cout << columna15S->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[14] == 'i' || tipos_de_datos_columnas[14] == 'I') {
						cout << columna15I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[14] == 'f' || tipos_de_datos_columnas[14] == 'F') {
						cout << columna15F->getPos(i);
						cout << "    \t      ";
					}

					//Columna 16

					if (tipos_de_datos_columnas[15] == 'c' || tipos_de_datos_columnas[15] == 'C') {
						cout << columna16S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[15] == 'i' || tipos_de_datos_columnas[15] == 'I') {
						cout << columna16I->getPos(i);
						cout << "    \t      ";
					}

					if (tipos_de_datos_columnas[15] == 'f' || tipos_de_datos_columnas[15] == 'F') {
						cout << columna16F->getPos(i);
						cout << "     \t     ";
					}


					//Columna 17

					if (tipos_de_datos_columnas[16] == 'c' || tipos_de_datos_columnas[16] == 'C') {
						cout << columna17S->getPos(i);
						cout << "      \t    ";
					}

					if (tipos_de_datos_columnas[16] == 'i' || tipos_de_datos_columnas[16] == 'I') {
						cout << columna17I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[16] == 'f' || tipos_de_datos_columnas[16] == 'F') {
						cout << columna17F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 18

					if (tipos_de_datos_columnas[17] == 'c' || tipos_de_datos_columnas[17] == 'C') {
						cout << columna18S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[17] == 'i' || tipos_de_datos_columnas[17] == 'I') {
						cout << columna18I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[17] == 'f' || tipos_de_datos_columnas[17] == 'F') {
						cout << columna18F->getPos(i);
						cout << "    \t      ";
					}


					//Columna 19

					if (tipos_de_datos_columnas[18] == 'c' || tipos_de_datos_columnas[18] == 'C') {
						cout << columna19S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[18] == 'i' || tipos_de_datos_columnas[18] == 'I') {
						cout << columna19I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[18] == 'f' || tipos_de_datos_columnas[18] == 'F') {
						cout << columna19F->getPos(i);
						cout << "     \t     ";
					}

					//Columna 20

					if (tipos_de_datos_columnas[19] == 'c' || tipos_de_datos_columnas[19] == 'C') {
						cout << columna20S->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[19] == 'i' || tipos_de_datos_columnas[19] == 'I') {
						cout << columna20I->getPos(i);
						cout << "     \t     ";
					}

					if (tipos_de_datos_columnas[19] == 'f' || tipos_de_datos_columnas[19] == 'F') {
						cout << columna20F->getPos(i);
						cout << "     \t     ";
					}


				}

				cout << endl;
			}

			_getch();
			break;
		case 7:
			int archivo;
			cout << "En que tipo de archivo desea guardar los datos?" << endl;
			cout << "1) Archivo.txt" << endl;
			cout << "2) Archivo.csv" << endl;
			cout << "3) Archivo.dat" << endl;
			cout << "Escriba la opcion: "; cin >> archivo;
			if (archivo == 1)
			{
				trabajofinal.open("trabajofinal.txt", ios::out);
				if (trabajofinal.is_open()) {

					trabajofinal << "\t\t.:TABLA:." << endl;
					trabajofinal << "\t";
					for (auto f : nombre_columnas) {
						trabajofinal << f << "    \t      ";
					}

					trabajofinal << endl;

					for (int i = 0; i < numFilas; i++) {
						trabajofinal << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
								trabajofinal << columna1S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
								trabajofinal << columna1I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
								trabajofinal << columna1F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 2

							if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
								trabajofinal << columna2S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
								trabajofinal << columna2I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
								trabajofinal << columna2F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 3

							if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
								trabajofinal << columna3S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
								trabajofinal << columna3I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
								trabajofinal << columna3F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 4

							if (tipos_de_datos_columnas[3] == 'c' || tipos_de_datos_columnas[3] == 'C') {
								trabajofinal << columna4S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[3] == 'i' || tipos_de_datos_columnas[3] == 'I') {
								trabajofinal << columna4I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[3] == 'f' || tipos_de_datos_columnas[3] == 'F') {
								trabajofinal << columna4F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 5

							if (tipos_de_datos_columnas[4] == 'c' || tipos_de_datos_columnas[4] == 'C') {
								trabajofinal << columna5S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[4] == 'i' || tipos_de_datos_columnas[4] == 'I') {
								trabajofinal << columna5I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[4] == 'f' || tipos_de_datos_columnas[4] == 'F') {
								trabajofinal << columna5F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 6

							if (tipos_de_datos_columnas[5] == 'c' || tipos_de_datos_columnas[5] == 'C') {
								trabajofinal << columna6S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[5] == 'i' || tipos_de_datos_columnas[5] == 'I') {
								trabajofinal << columna6I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[5] == 'f' || tipos_de_datos_columnas[5] == 'F') {
								trabajofinal << columna6F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 7

							if (tipos_de_datos_columnas[6] == 'c' || tipos_de_datos_columnas[6] == 'C') {
								trabajofinal << columna7S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[6] == 'i' || tipos_de_datos_columnas[6] == 'I') {
								trabajofinal << columna7I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[6] == 'f' || tipos_de_datos_columnas[6] == 'F') {
								trabajofinal << columna7F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 8

							if (tipos_de_datos_columnas[7] == 'c' || tipos_de_datos_columnas[7] == 'C') {
								trabajofinal << columna8S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[7] == 'i' || tipos_de_datos_columnas[7] == 'I') {
								trabajofinal << columna8I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[7] == 'f' || tipos_de_datos_columnas[7] == 'F') {
								trabajofinal << columna8F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 9

							if (tipos_de_datos_columnas[8] == 'c' || tipos_de_datos_columnas[8] == 'C') {
								trabajofinal << columna9S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[8] == 'i' || tipos_de_datos_columnas[8] == 'I') {
								trabajofinal << columna9I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[8] == 'f' || tipos_de_datos_columnas[8] == 'F') {
								trabajofinal << columna9F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 10

							if (tipos_de_datos_columnas[9] == 'c' || tipos_de_datos_columnas[9] == 'C') {
								trabajofinal << columna10S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[9] == 'i' || tipos_de_datos_columnas[9] == 'I') {
								trabajofinal << columna10I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[9] == 'f' || tipos_de_datos_columnas[9] == 'F') {
								trabajofinal << columna10F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 11

							if (tipos_de_datos_columnas[10] == 'c' || tipos_de_datos_columnas[10] == 'C') {
								trabajofinal << columna11S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[10] == 'i' || tipos_de_datos_columnas[10] == 'I') {
								trabajofinal << columna11I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[10] == 'f' || tipos_de_datos_columnas[10] == 'F') {
								trabajofinal << columna11F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 12

							if (tipos_de_datos_columnas[11] == 'c' || tipos_de_datos_columnas[11] == 'C') {
								trabajofinal << columna12S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[11] == 'i' || tipos_de_datos_columnas[11] == 'I') {
								trabajofinal << columna12I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[11] == 'f' || tipos_de_datos_columnas[11] == 'F') {
								trabajofinal << columna12F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 13

							if (tipos_de_datos_columnas[12] == 'c' || tipos_de_datos_columnas[12] == 'C') {
								trabajofinal << columna13S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[12] == 'i' || tipos_de_datos_columnas[12] == 'I') {
								trabajofinal << columna13I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[12] == 'f' || tipos_de_datos_columnas[12] == 'F') {
								trabajofinal << columna13F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 14

							if (tipos_de_datos_columnas[13] == 'c' || tipos_de_datos_columnas[13] == 'C') {
								trabajofinal << columna14S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[13] == 'i' || tipos_de_datos_columnas[13] == 'I') {
								trabajofinal << columna14I->getPos(i);
								trabajofinal << "   \t       ";
							}

							if (tipos_de_datos_columnas[13] == 'f' || tipos_de_datos_columnas[13] == 'F') {
								trabajofinal << columna14F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 15

							if (tipos_de_datos_columnas[14] == 'c' || tipos_de_datos_columnas[14] == 'C') {
								trabajofinal << columna15S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[14] == 'i' || tipos_de_datos_columnas[14] == 'I') {
								trabajofinal << columna15I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[14] == 'f' || tipos_de_datos_columnas[14] == 'F') {
								trabajofinal << columna15F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 16

							if (tipos_de_datos_columnas[15] == 'c' || tipos_de_datos_columnas[15] == 'C') {
								trabajofinal << columna16S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[15] == 'i' || tipos_de_datos_columnas[15] == 'I') {
								trabajofinal << columna16I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[15] == 'f' || tipos_de_datos_columnas[15] == 'F') {
								trabajofinal << columna16F->getPos(i);
								trabajofinal << "     \t     ";
							}


							//Columna 17

							if (tipos_de_datos_columnas[16] == 'c' || tipos_de_datos_columnas[16] == 'C') {
								trabajofinal << columna17S->getPos(i);
								trabajofinal << "      \t    ";
							}

							if (tipos_de_datos_columnas[16] == 'i' || tipos_de_datos_columnas[16] == 'I') {
								trabajofinal << columna17I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[16] == 'f' || tipos_de_datos_columnas[16] == 'F') {
								trabajofinal << columna17F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 18

							if (tipos_de_datos_columnas[17] == 'c' || tipos_de_datos_columnas[17] == 'C') {
								trabajofinal << columna18S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[17] == 'i' || tipos_de_datos_columnas[17] == 'I') {
								trabajofinal << columna18I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[17] == 'f' || tipos_de_datos_columnas[17] == 'F') {
								trabajofinal << columna18F->getPos(i);
								trabajofinal << "    \t      ";
							}


							//Columna 19

							if (tipos_de_datos_columnas[18] == 'c' || tipos_de_datos_columnas[18] == 'C') {
								trabajofinal << columna19S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[18] == 'i' || tipos_de_datos_columnas[18] == 'I') {
								trabajofinal << columna19I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[18] == 'f' || tipos_de_datos_columnas[18] == 'F') {
								trabajofinal << columna19F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 20

							if (tipos_de_datos_columnas[19] == 'c' || tipos_de_datos_columnas[19] == 'C') {
								trabajofinal << columna20S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[19] == 'i' || tipos_de_datos_columnas[19] == 'I') {
								trabajofinal << columna20I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[19] == 'f' || tipos_de_datos_columnas[19] == 'F') {
								trabajofinal << columna20F->getPos(i);
								trabajofinal << "     \t     ";
							}


						}

						trabajofinal << endl;
					}

					trabajofinal.close();
				}
			}

			if (archivo == 2)
			{
				trabajofinal.open("trabajofinal.csv", ios::out);
				if (trabajofinal.is_open()) {

					trabajofinal << "\t\t.:TABLA:." << endl;
					trabajofinal << "\t";
					for (auto f : nombre_columnas) {
						trabajofinal << f << "    \t      ";
					}

					trabajofinal << endl;

					for (int i = 0; i < numFilas; i++) {
						trabajofinal << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
								trabajofinal << columna1S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
								trabajofinal << columna1I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
								trabajofinal << columna1F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 2

							if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
								trabajofinal << columna2S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
								trabajofinal << columna2I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
								trabajofinal << columna2F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 3

							if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
								trabajofinal << columna3S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
								trabajofinal << columna3I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
								trabajofinal << columna3F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 4

							if (tipos_de_datos_columnas[3] == 'c' || tipos_de_datos_columnas[3] == 'C') {
								trabajofinal << columna4S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[3] == 'i' || tipos_de_datos_columnas[3] == 'I') {
								trabajofinal << columna4I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[3] == 'f' || tipos_de_datos_columnas[3] == 'F') {
								trabajofinal << columna4F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 5

							if (tipos_de_datos_columnas[4] == 'c' || tipos_de_datos_columnas[4] == 'C') {
								trabajofinal << columna5S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[4] == 'i' || tipos_de_datos_columnas[4] == 'I') {
								trabajofinal << columna5I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[4] == 'f' || tipos_de_datos_columnas[4] == 'F') {
								trabajofinal << columna5F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 6

							if (tipos_de_datos_columnas[5] == 'c' || tipos_de_datos_columnas[5] == 'C') {
								trabajofinal << columna6S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[5] == 'i' || tipos_de_datos_columnas[5] == 'I') {
								trabajofinal << columna6I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[5] == 'f' || tipos_de_datos_columnas[5] == 'F') {
								trabajofinal << columna6F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 7

							if (tipos_de_datos_columnas[6] == 'c' || tipos_de_datos_columnas[6] == 'C') {
								trabajofinal << columna7S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[6] == 'i' || tipos_de_datos_columnas[6] == 'I') {
								trabajofinal << columna7I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[6] == 'f' || tipos_de_datos_columnas[6] == 'F') {
								trabajofinal << columna7F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 8

							if (tipos_de_datos_columnas[7] == 'c' || tipos_de_datos_columnas[7] == 'C') {
								trabajofinal << columna8S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[7] == 'i' || tipos_de_datos_columnas[7] == 'I') {
								trabajofinal << columna8I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[7] == 'f' || tipos_de_datos_columnas[7] == 'F') {
								trabajofinal << columna8F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 9

							if (tipos_de_datos_columnas[8] == 'c' || tipos_de_datos_columnas[8] == 'C') {
								trabajofinal << columna9S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[8] == 'i' || tipos_de_datos_columnas[8] == 'I') {
								trabajofinal << columna9I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[8] == 'f' || tipos_de_datos_columnas[8] == 'F') {
								trabajofinal << columna9F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 10

							if (tipos_de_datos_columnas[9] == 'c' || tipos_de_datos_columnas[9] == 'C') {
								trabajofinal << columna10S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[9] == 'i' || tipos_de_datos_columnas[9] == 'I') {
								trabajofinal << columna10I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[9] == 'f' || tipos_de_datos_columnas[9] == 'F') {
								trabajofinal << columna10F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 11

							if (tipos_de_datos_columnas[10] == 'c' || tipos_de_datos_columnas[10] == 'C') {
								trabajofinal << columna11S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[10] == 'i' || tipos_de_datos_columnas[10] == 'I') {
								trabajofinal << columna11I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[10] == 'f' || tipos_de_datos_columnas[10] == 'F') {
								trabajofinal << columna11F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 12

							if (tipos_de_datos_columnas[11] == 'c' || tipos_de_datos_columnas[11] == 'C') {
								trabajofinal << columna12S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[11] == 'i' || tipos_de_datos_columnas[11] == 'I') {
								trabajofinal << columna12I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[11] == 'f' || tipos_de_datos_columnas[11] == 'F') {
								trabajofinal << columna12F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 13

							if (tipos_de_datos_columnas[12] == 'c' || tipos_de_datos_columnas[12] == 'C') {
								trabajofinal << columna13S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[12] == 'i' || tipos_de_datos_columnas[12] == 'I') {
								trabajofinal << columna13I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[12] == 'f' || tipos_de_datos_columnas[12] == 'F') {
								trabajofinal << columna13F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 14

							if (tipos_de_datos_columnas[13] == 'c' || tipos_de_datos_columnas[13] == 'C') {
								trabajofinal << columna14S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[13] == 'i' || tipos_de_datos_columnas[13] == 'I') {
								trabajofinal << columna14I->getPos(i);
								trabajofinal << "   \t       ";
							}

							if (tipos_de_datos_columnas[13] == 'f' || tipos_de_datos_columnas[13] == 'F') {
								trabajofinal << columna14F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 15

							if (tipos_de_datos_columnas[14] == 'c' || tipos_de_datos_columnas[14] == 'C') {
								trabajofinal << columna15S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[14] == 'i' || tipos_de_datos_columnas[14] == 'I') {
								trabajofinal << columna15I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[14] == 'f' || tipos_de_datos_columnas[14] == 'F') {
								trabajofinal << columna15F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 16

							if (tipos_de_datos_columnas[15] == 'c' || tipos_de_datos_columnas[15] == 'C') {
								trabajofinal << columna16S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[15] == 'i' || tipos_de_datos_columnas[15] == 'I') {
								trabajofinal << columna16I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[15] == 'f' || tipos_de_datos_columnas[15] == 'F') {
								trabajofinal << columna16F->getPos(i);
								trabajofinal << "     \t     ";
							}


							//Columna 17

							if (tipos_de_datos_columnas[16] == 'c' || tipos_de_datos_columnas[16] == 'C') {
								trabajofinal << columna17S->getPos(i);
								trabajofinal << "      \t    ";
							}

							if (tipos_de_datos_columnas[16] == 'i' || tipos_de_datos_columnas[16] == 'I') {
								trabajofinal << columna17I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[16] == 'f' || tipos_de_datos_columnas[16] == 'F') {
								trabajofinal << columna17F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 18

							if (tipos_de_datos_columnas[17] == 'c' || tipos_de_datos_columnas[17] == 'C') {
								trabajofinal << columna18S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[17] == 'i' || tipos_de_datos_columnas[17] == 'I') {
								trabajofinal << columna18I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[17] == 'f' || tipos_de_datos_columnas[17] == 'F') {
								trabajofinal << columna18F->getPos(i);
								trabajofinal << "    \t      ";
							}


							//Columna 19

							if (tipos_de_datos_columnas[18] == 'c' || tipos_de_datos_columnas[18] == 'C') {
								trabajofinal << columna19S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[18] == 'i' || tipos_de_datos_columnas[18] == 'I') {
								trabajofinal << columna19I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[18] == 'f' || tipos_de_datos_columnas[18] == 'F') {
								trabajofinal << columna19F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 20

							if (tipos_de_datos_columnas[19] == 'c' || tipos_de_datos_columnas[19] == 'C') {
								trabajofinal << columna20S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[19] == 'i' || tipos_de_datos_columnas[19] == 'I') {
								trabajofinal << columna20I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[19] == 'f' || tipos_de_datos_columnas[19] == 'F') {
								trabajofinal << columna20F->getPos(i);
								trabajofinal << "     \t     ";
							}


						}

						trabajofinal << endl;
					}

					trabajofinal.close();
				}
			}

			if (archivo == 3)
			{
				trabajofinal.open("trabajofinalB.dat", ios::binary);
				if (trabajofinal.is_open()) {

					trabajofinal << "\t\t.:TABLA:." << endl;
					trabajofinal << "\t";
					for (auto f : nombre_columnas) {
						trabajofinal << f << "    \t      ";
					}

					trabajofinal << endl;

					for (int i = 0; i < numFilas; i++) {
						trabajofinal << i << "\t";

						if (i == ((numFilas - numFilas) + i)) {
							//Columna 1

							if (tipos_de_datos_columnas[0] == 'c' || tipos_de_datos_columnas[0] == 'C') {
								trabajofinal << columna1S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[0] == 'i' || tipos_de_datos_columnas[0] == 'I') {
								trabajofinal << columna1I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[0] == 'f' || tipos_de_datos_columnas[0] == 'F') {
								trabajofinal << columna1F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 2

							if (tipos_de_datos_columnas[1] == 'c' || tipos_de_datos_columnas[1] == 'C') {
								trabajofinal << columna2S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[1] == 'i' || tipos_de_datos_columnas[1] == 'I') {
								trabajofinal << columna2I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[1] == 'f' || tipos_de_datos_columnas[1] == 'F') {
								trabajofinal << columna2F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 3

							if (tipos_de_datos_columnas[2] == 'c' || tipos_de_datos_columnas[2] == 'C') {
								trabajofinal << columna3S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[2] == 'i' || tipos_de_datos_columnas[2] == 'I') {
								trabajofinal << columna3I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[2] == 'f' || tipos_de_datos_columnas[2] == 'F') {
								trabajofinal << columna3F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 4

							if (tipos_de_datos_columnas[3] == 'c' || tipos_de_datos_columnas[3] == 'C') {
								trabajofinal << columna4S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[3] == 'i' || tipos_de_datos_columnas[3] == 'I') {
								trabajofinal << columna4I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[3] == 'f' || tipos_de_datos_columnas[3] == 'F') {
								trabajofinal << columna4F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 5

							if (tipos_de_datos_columnas[4] == 'c' || tipos_de_datos_columnas[4] == 'C') {
								trabajofinal << columna5S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[4] == 'i' || tipos_de_datos_columnas[4] == 'I') {
								trabajofinal << columna5I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[4] == 'f' || tipos_de_datos_columnas[4] == 'F') {
								trabajofinal << columna5F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 6

							if (tipos_de_datos_columnas[5] == 'c' || tipos_de_datos_columnas[5] == 'C') {
								trabajofinal << columna6S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[5] == 'i' || tipos_de_datos_columnas[5] == 'I') {
								trabajofinal << columna6I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[5] == 'f' || tipos_de_datos_columnas[5] == 'F') {
								trabajofinal << columna6F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 7

							if (tipos_de_datos_columnas[6] == 'c' || tipos_de_datos_columnas[6] == 'C') {
								trabajofinal << columna7S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[6] == 'i' || tipos_de_datos_columnas[6] == 'I') {
								trabajofinal << columna7I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[6] == 'f' || tipos_de_datos_columnas[6] == 'F') {
								trabajofinal << columna7F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 8

							if (tipos_de_datos_columnas[7] == 'c' || tipos_de_datos_columnas[7] == 'C') {
								trabajofinal << columna8S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[7] == 'i' || tipos_de_datos_columnas[7] == 'I') {
								trabajofinal << columna8I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[7] == 'f' || tipos_de_datos_columnas[7] == 'F') {
								trabajofinal << columna8F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 9

							if (tipos_de_datos_columnas[8] == 'c' || tipos_de_datos_columnas[8] == 'C') {
								trabajofinal << columna9S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[8] == 'i' || tipos_de_datos_columnas[8] == 'I') {
								trabajofinal << columna9I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[8] == 'f' || tipos_de_datos_columnas[8] == 'F') {
								trabajofinal << columna9F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 10

							if (tipos_de_datos_columnas[9] == 'c' || tipos_de_datos_columnas[9] == 'C') {
								trabajofinal << columna10S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[9] == 'i' || tipos_de_datos_columnas[9] == 'I') {
								trabajofinal << columna10I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[9] == 'f' || tipos_de_datos_columnas[9] == 'F') {
								trabajofinal << columna10F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 11

							if (tipos_de_datos_columnas[10] == 'c' || tipos_de_datos_columnas[10] == 'C') {
								trabajofinal << columna11S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[10] == 'i' || tipos_de_datos_columnas[10] == 'I') {
								trabajofinal << columna11I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[10] == 'f' || tipos_de_datos_columnas[10] == 'F') {
								trabajofinal << columna11F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 12

							if (tipos_de_datos_columnas[11] == 'c' || tipos_de_datos_columnas[11] == 'C') {
								trabajofinal << columna12S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[11] == 'i' || tipos_de_datos_columnas[11] == 'I') {
								trabajofinal << columna12I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[11] == 'f' || tipos_de_datos_columnas[11] == 'F') {
								trabajofinal << columna12F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 13

							if (tipos_de_datos_columnas[12] == 'c' || tipos_de_datos_columnas[12] == 'C') {
								trabajofinal << columna13S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[12] == 'i' || tipos_de_datos_columnas[12] == 'I') {
								trabajofinal << columna13I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[12] == 'f' || tipos_de_datos_columnas[12] == 'F') {
								trabajofinal << columna13F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 14

							if (tipos_de_datos_columnas[13] == 'c' || tipos_de_datos_columnas[13] == 'C') {
								trabajofinal << columna14S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[13] == 'i' || tipos_de_datos_columnas[13] == 'I') {
								trabajofinal << columna14I->getPos(i);
								trabajofinal << "   \t       ";
							}

							if (tipos_de_datos_columnas[13] == 'f' || tipos_de_datos_columnas[13] == 'F') {
								trabajofinal << columna14F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 15

							if (tipos_de_datos_columnas[14] == 'c' || tipos_de_datos_columnas[14] == 'C') {
								trabajofinal << columna15S->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[14] == 'i' || tipos_de_datos_columnas[14] == 'I') {
								trabajofinal << columna15I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[14] == 'f' || tipos_de_datos_columnas[14] == 'F') {
								trabajofinal << columna15F->getPos(i);
								trabajofinal << "    \t      ";
							}

							//Columna 16

							if (tipos_de_datos_columnas[15] == 'c' || tipos_de_datos_columnas[15] == 'C') {
								trabajofinal << columna16S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[15] == 'i' || tipos_de_datos_columnas[15] == 'I') {
								trabajofinal << columna16I->getPos(i);
								trabajofinal << "    \t      ";
							}

							if (tipos_de_datos_columnas[15] == 'f' || tipos_de_datos_columnas[15] == 'F') {
								trabajofinal << columna16F->getPos(i);
								trabajofinal << "     \t     ";
							}


							//Columna 17

							if (tipos_de_datos_columnas[16] == 'c' || tipos_de_datos_columnas[16] == 'C') {
								trabajofinal << columna17S->getPos(i);
								trabajofinal << "      \t    ";
							}

							if (tipos_de_datos_columnas[16] == 'i' || tipos_de_datos_columnas[16] == 'I') {
								trabajofinal << columna17I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[16] == 'f' || tipos_de_datos_columnas[16] == 'F') {
								trabajofinal << columna17F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 18

							if (tipos_de_datos_columnas[17] == 'c' || tipos_de_datos_columnas[17] == 'C') {
								trabajofinal << columna18S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[17] == 'i' || tipos_de_datos_columnas[17] == 'I') {
								trabajofinal << columna18I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[17] == 'f' || tipos_de_datos_columnas[17] == 'F') {
								trabajofinal << columna18F->getPos(i);
								trabajofinal << "    \t      ";
							}


							//Columna 19

							if (tipos_de_datos_columnas[18] == 'c' || tipos_de_datos_columnas[18] == 'C') {
								trabajofinal << columna19S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[18] == 'i' || tipos_de_datos_columnas[18] == 'I') {
								trabajofinal << columna19I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[18] == 'f' || tipos_de_datos_columnas[18] == 'F') {
								trabajofinal << columna19F->getPos(i);
								trabajofinal << "     \t     ";
							}

							//Columna 20

							if (tipos_de_datos_columnas[19] == 'c' || tipos_de_datos_columnas[19] == 'C') {
								trabajofinal << columna20S->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[19] == 'i' || tipos_de_datos_columnas[19] == 'I') {
								trabajofinal << columna20I->getPos(i);
								trabajofinal << "     \t     ";
							}

							if (tipos_de_datos_columnas[19] == 'f' || tipos_de_datos_columnas[19] == 'F') {
								trabajofinal << columna20F->getPos(i);
								trabajofinal << "     \t     ";
							}


						}

						trabajofinal << endl;
					}

					trabajofinal.close();
				}
			}
			if (archivo >= 4)
			{
				cout << "La opcion no existe" << endl;
			}

			_getch();
			break;
		case 8:
			break;
		}

	}



	_getch();
	return 0;
}