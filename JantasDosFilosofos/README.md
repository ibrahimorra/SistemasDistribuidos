# Jantar dos Filósofos

# Trabalho de Sistemas Distribuidos

__Para que o problema do jantar dos filósofos seja solucionado como solicitado foram desenvolvidas novas funções como__:

- __pegarGarfoEsquerda (int filosofo)__:
Nessa função o filosofo vai entrar no estado de Fome e chamar a função testarEsquerda(int filosofo).
Se o filosofo entrar na condição com fome e o filosofo na posição Esquerda-1 não estiver com o garfo direito, então o filosofo pegará o garfo em sua esquerda.

- pegarGarfoDireita (int filosofo):
Nessa função o filosofo vai entrar no estado de Fome e chamar a função testarDireita(int filosofo).
Se o filosofo entrar na condição com fome e o filosofo na posição Direita+1 não estiver com o garfo esquerdo, então o filosofo pegará o garfo em sua direita.
- tentarComer (int filosofo):

Essa função checará se o filosofo está com os 2 garfos, caso estiver, seu Estado mudará para Comendo. Nessa mesma função temos uma chamada de sleep(int) para controlar o tempo que o filosofo leva para comer.

- devolverGarfoDireita(int filosofo):
Se o filosofo já comeu, então, ele devolverá o garfo direito.

- devolver GarfoEsquerda(int filosofo):
Se o filosofo já comeu, então, ele devolverá o garfo direito.

- pensar (int filosofo):
Se o filosofo já comeu e devolveu o seu garfo direito e garfo esquerda então o filósofo passará a estar no Estado Pensando. Nessa mesma função temos uma chamada de sleep(int) para controlar o tempo que o filosofo leva para pensar.
