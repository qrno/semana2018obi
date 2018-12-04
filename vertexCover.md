# Aula 2
## Professor ? - Semana Olímpica
## 4/12/2018 - Manhã # Cobertura por vértices 


## Problema motivador
Vertex Cover: https://en.wikipedia.org/wiki/Vertex_cover

Dado um grafo, devemos escolher vértices de modo que toda aresta do gráfico tenha pelo menos um vértice escolhido.
Além disso, existem algumas arestas especiais, de modo que não podemos escolher os dois vértices delas.
Caso seja impossível, indicar isso.

## Revisão: DFS

Criaremos uma DFS, marcando os tempos de entrada e saída em cada vértice.

```
dfs(x):
	visitado(x) = sim
	entrada(x) = tempo++
	para cada vizinho y de x:
		se y não foi visitado
			dfs(y)
	saida(v) = tempo++	
```

Esse tipo de DFS, caso executado numa árvore, pode nos dizer rapidamente se um vértice está na subárvore de outro.
Por exemplo, v está na subárvore de u se e somente se o intervalo de entrada-saída de v está incluso do de u.
(Vale notar que numa árvore, os intervalos de dois vértices ou são disjuntos ou um está contido no outro.)

## Pontes
https://en.wikipedia.org/wiki/Bridge_(graph_theory)#Tarjan%27s_bridge-finding_algorithm

Este é o algoritmo de Tarjan para encontrar pontes em um grafo.
Pontes são definidas como arestas tais que se elas forem removidas do grafo, ele se torna desconexo.

Vamos analisar um algoritmo que encontra quais arestas de um grafo são pontes.
Para todo vértice, escolhendo um vértice arbitrário como raiz, o valor de v é tal que:
 - O caminhho passa por v.
 - O caminho não passa pela mesma aresta duas vezes.
 - Pode-se descer o quanto quiser mas subir no máximo uma vez. (Naturalmente, ao final)
 - O valor a ser guardado em v é o menor nível que se pode terminar seguindo esse caminho.

Aqui, low(v) é o valor referido acima:

```
dfs(x, pai):
	visitado(x) = sim
	entrada(x) = t++

	low(x) = altura(x)

	para cada vizinho y de x:
		se y não foi visitado:
			altura(y) = altura(x) + 1
			dfs(y, x)
			low(x) = min(low(x), low(y))

		se y != pai e está sendo visitado:
			low(x) = min(low(v), altura(y))

	visitado(v) = acabou
	saida(v) = t++

aresta v-w é ponte se:
	altura(v) < altura(w) (v acima de w)
	e low(v) = altura(w) (w é o vértice mais alto que podemos chegar passando por v e subindo uma vez)
```

O algoritmo abaixo, com altura trocada por entrada, é equivalente para nossas necessidades.

```
dfs(x, pai):
	visitado(x) = sim
	entrada(x) = t++

	low(x) = entrada(x)

	para cada vizinho y de x:
		se y não foi visitado:
			ffs(y, x)
			low(x) = min(low(x), low(y))

		se y != pai e está sendo visitado:
			low(x) = min(low(v), entrada(y))

	visitado(v) = acabou
	saida(v) = t++

aresta v-w é ponte se:
	entrada(v) < entrada(w)
	e low(v) = entrada(w)
```

## Componentes fortemente conexas
https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm
Compontentes fortemente conexas em um grafo direcionado, são tais que dados quaisquer vértices u, v, pode se ir de u para v e de v para u.

Algoritmo de pseudocódigo da Wikipedia.
Note que o algoritmo é muito similar ao que vimos anteriormente.

```
 algorithm tarjan is
  input: graph G = (V, E)
  output: set of strongly connected components (sets of vertices)

  index := 0
  S := empty array
  for each v in V do
    if (v.index is undefined) then
      strongconnect(v)
    end if
  end for

  function strongconnect(v)
    // Set the depth index for v to the smallest unused index
    v.index := index
    v.lowlink := index
    index := index + 1
    S.push(v)
    v.onStack := true

    // Consider successors of v
    for each (v, w) in E do
      if (w.index is undefined) then
        // Successor w has not yet been visited; recurse on it
        strongconnect(w)
        v.lowlink  := min(v.lowlink, w.lowlink)
      else if (w.onStack) then
        // Successor w is in stack S and hence in the current SCC
        // If w is not on stack, then (v, w) is a cross-edge in the DFS tree and must be ignored
        // Note: The next line may look odd - but is correct.
        // It says w.index not w.lowlink; that is deliberate and from the original paper
        v.lowlink  := min(v.lowlink, w.index)
      end if
    end for

    // If v is a root node, pop the stack and generate an SCC
    if (v.lowlink = v.index) then
      start a new strongly connected component
      repeat
        w := S.pop()
        w.onStack := false
        add w to current strongly connected component
      while (w != v)
      output the current strongly connected component
    end if
  end function
```

## SAT - Boolean Satisfiability problem
https://en.wikipedia.org/wiki/Boolean_satisfiability_problem
https://en.wikipedia.org/wiki/2-satisfiability

Dado um conjunto de cláusulas, existem uma combinação de valores para xi (true/false) de modo que todas sejam verdadeiras.

Ex:
c1 = x1  x2
c2 = x1 v ~x2
c3 = ~x1 v ~x2
Queremos saber se existem x tais que c1 ^ c2 ^ c3 = T
Existe, nesse caso, solução x = [T, F]

O problema é NP-Complete, ou seja, não há um algoritmo polinomial para resolvê-lo.
Por outro lado, se cada cláusula tem até 2 literais (xi), então há uma solução linear para ele.
Problema adicional: caso não seja possível que todas sejam verdadeiras, achar o máximo que pode ser.

O problema com no máximo n literais por cláusula é denominado n-SAT, vamos analisar o 2-SAT.

Podemos traduzir cada cláusula em implicações:
Ex:
x1 v ~x2 <-> ~x1 -> ~x2 e x2 -> x1
x1 ^ ~x2 <-> x1 = T e x2 = F

Podemos representar essas implicações como arestas em um grafo direcionado, onde os vértices são os literais (ex: x1, ~x3 etc.)
