- Relatório do Trabalho 2 - Tabela Hash.

Introdução:
    O objetivo é a implementação de uma tabela hash com hash estático, sem 
    duplicadas e com chaves inteiras. Colisões são resolvidas com lista duplamente
    encadeada.

Processo:

1. Como foi estruturado?
    A tabela consiste em uma struct hashTable que contém um vetor de ponteiros 
    com tamanho definido pelo usuário para struct nodoHash, a qual vai guardar a
    chave, um ponteiro para o próximo elemento e um ponteiro para o anterior.

2. Função hash:
    A função hash usada foi h(k) = k mod m, onde k é a chave e m o tamanho da 
    tabela. Como em C o módulo feito não é o modo matemático, foi necessário uma
    condição dentro da função para números negativos. Tal condição converte o 
    tamanho da tabela (size_t) para um long, assim evitando a promoção automática
    para size_t que aconteceria na operação e somando o tamanho da tabela ao
    resultado, o que garante o funcionamento correto do módulo matemático.

3. Busca:
    Para buscar uma chave, obtém-se o índice do slot da mesma através da 
    função hash. Se o slot conter NULL, então o elemento não existe na tabela,
    caso exista um ou mais elementos no slot, é necessário iterar pela lista 
    comparando as chaves dos nodos com a chave, o que pode custar no pior caso
    o número de nodos da tabela.

4. Inserção:
    Para inserir uma chave k, obtém-se o índice do slot da mesma através da 
    função hash. Se o slot conter NULL, então atribui para o ponteiro do slot
    um nodo com a chave k, caso existam elementos no slot é preciso iterar pela 
    lista comparando as chaves dos nodos com a chave k, se alguma chave for igual,
    a inserção não acontecerá, pois não podem ter duplicadas na tabela, se não,
    basta inserir um nodo contendo a chave no final da lista, já que a verificação
    até o final da lista para garantir a não existência de duplicadas foi feita
    (poderia ser inserido no início, porém, mais atribuições de ponteiros seriam 
    necessárias). Essa verificação, acaba transformando o custo da inserção no
    pior caso a quantidade de elementos na tabela.

5. Exclusão:
    Existem 4 casos:

    Primeiro: O elemento está sozinho no slot. Basta liberar o nodo e atribuir
        NULL para o slot.
    Segundo: O elemento é o primeiro da lista no slot. Resolve ao colocar o
        ponteiro para o nodo anterior do segundo elemento como NULL, atribuir o
        endereço do segundo para o ponteiro do slot (o que o transforma no primeiro)
        e liberar a memória do nodo a ser excluído.
    Terceiro: O elemento está entre dois nodos. Suponha que o nodo a ser removido
        y está entre os nodos x e z (x<-->y<-->z), então deve-se atribuir o endereço 
        de x ao nodo anterior de z e o endereço de z ao próximo nodo de x. Após 
        isso, liberar y.
    Quarto: O elemento está no final da lista. Atribui NULL para o ponteiro de 
        próximo nodo do nodo anterior ao alvo e libera o alvo.
