//Implementação de Union Find, da aula 1

#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 1000;

int pai[MAXN];
//Rank
int R[MAXN];

//Representante
int repr(int x) {
	if (pai[x] == x)
		return x;
	return repr(pai(x));
}

//Liga x e y
void juntar(int x, int y) {
	pai[repr(x)] = repr(y);
}


//Representante com Path Comrpession
int reprPC(int x) {
	if (pai[x] == x)
		return x;
	pai[x] = reprPC(pai[x]);
	return pai[x];
}

//Ligar com x e y com Rank
//(Usa o PC, mas dá no mesmo)
int juntarR(int x, int y) {
	int rx = reprPC(x);
	int ry = reprPC(y);

	if (rank(rx) < rank(ry)) {
		pai[rx] = ry;
	} else if (rank(ry) > rank(rx)) {
		pai[ry] = rx;
	} else {
		pai[rx] = ry;
		rank(ry)++;
	}
}

int main() {

	for (int i = 0; i < MAXN; i++) {
		pai[i] = i;
	}

	return 0;
}
