# Aula 1
## Professor Arthur - Semana Olímpica
## 3/12/2018 - Manhã

# Conectividade Dinâmica

### Problema 1.1

Temos um vetor cíclico de lâmpadas, todas inicialmente desligadas.
Uma operação consiste em acender uma das lâmpadas.
Após cada operação devemos imprimir o maior valor de distância entre lâmpadas.

#### Solução

Para cada operação, que liga a vela n, temos dois casos:
 - A máxima distância continua a mesma
 - A máxima distância envolve n

Podemos assim manter um set com as lâmpadas acesas, e a cada operação, checamos qual é a vela mais distante da que acendemos.
Fazemos isso vendo qual é a acesa mais próxima da oposta à que acendemos.

### Problema 1.2
Temos agora a mesma situação do problema 1, mas temos também a operação de apagar uma lâmpada.

#### Solução

Para cada lâmpada acesa, marque com vermelho a lâmapda oposta a ela.
Se A está muito longe de B, A está muito perto do oposto de B.
Podemos assim reduzir o problema a encontrar dois lâmpadas de cores diferentes de distância mínima.

### Union Find
Queremos saber, em um grafo, se dados dois vértices estão na mesma componente conexa.
Vamos fazer isso escolhendo um vértice "representante" para cada componente.
Assim, dois vértices estarão na mesma componente se e somente se eles tem o mesmo representante.

Inicialmente cada vértice é seu próprio pai.
Um vértice é um representante de componente se ele é seu próprio pai.
Se há uma aresta entre u e v, podemos dizer que o pai de um deles é o outro.
Assim, há caminho entre u e v se eles tem o mesmo representante.

Defina rank(x) a quantidade de níveis de nós abaixo de um certo x.

Assim temos o seguinte:
```
representante(x):
	se x é seu pai -> x
	senão -> representante(pai(x))

juntar(x, y):
	pai(representante(x)) = representante(y)
```

### Otimização Union Find:

#### Union by Rank
Na função juntax(x, y), juntamos sempre a componente de rank menor na de maior.
Assim em juntar(x, y):

```
juntar(x, y):
	px = representante(x)
	py = representante(y)

	se rank(px) < rank(py):
		pai(px) = py
	senão se rank(px) > rank(py):
		pai(py) = px
	se rank(px) == rank(py):
		pai(px) = py
		rank(px) += 1
```

#### Path compression
Sempre que chamamos a função representante de x, definimos seu pai como seu representante.
Temos assim em representante(x):

```
	...
	senão:
		pai(x) = representante(pai(x))
		-> pai(x)
```

### Problema 2.1
Temos um grafo com 3 operações:
 - *+ a b*: cria uma aresta entre a e b.
 - *-*: retira a última aresta criada.
 - *p a b*: pergunta se a e b estão conectados.

### Solução
Union find, com uma alteração em juntar(x, y):
Sempre que fazemos pai(px) = py em juntar(x, y), devemos adicionar px numa stack.
Assim, caso - seja acionado, podemos apenas fazer pai(px) = px, desfazendo a ligação.
OBS: Assumimos que o path compression não está sendo usado.

### Problema 2.2
Mesma coisa, mas a operação *-* é trocada por *- a b*, deletando uma aresta qualquer entre a e b.

### Solução
Inicialmente, vamos listar as perguntas.
Para cada aresta, vemos em qual intervalo de perguntas ela existe.
Assim, podemos criar uma segment tree, onde os nós são as perguntas.
Assim, fazemos updates em intervalos da segment tree, adicionando as arestas (Adicionamos como na Lazy Propagation valores aos nós).
Assim, podemos fazer isso de modo que nós reduzimos nosso problema ao anterior (2.1)

(OBS: Farei update com uma explicação melhor para o P2.2)
(OBS: No P2.1 e P2.2 pode-se implementar o Path Compression, com algumas modificações no código)
