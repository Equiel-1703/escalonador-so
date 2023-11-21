# Simulador de Escalonador

Este programa é um simulador de um escalonador - um dos principais componentes de um sistema operacional. Ele possui dois algoritmos implementados: SJF (Shortest Job First) e GJF (Greatest Job First). Para usá-lo, é preciso fornecer como entrada o arquivo contendo as tarefas para ele escalonar, o número de cores do processador da simulação e a política de escalonamento:

```simulador-so <arquivo_com_tarefas.txt> <nro_de_cores> <politica>```

Onde: 
- \<arquivo_com_tarefas.txt> é o caminho do arquivo contendo as tarefas para o escalonador. A forma que esse arquivo deve ser estruturado é explicado mais abaixo
- \<nro_de_cores> é o número de cores do processador da simulação
- \<politica> [OPCIONAL] é a política de escalonamento usada para selecionar as tarefas. Como dito anteriormente, há duas políticas implementadas:
  - s -> Shortest Job First, nessa política as tarefas **menores** são executadas primeiro
  - g -> Greatest Job First, tarefas **maiores** são executadas primeiro  

  Se o parâmetro `<política>` não for fornecido, o simulador executa usando SJF.

## Arquivo com tarefas

O arquivo de texto contendo as tarefas para a simulação deve ser estruturado da seguinte forma:
```
<id_tarefa_1> <tempo_1>
<id_tarefa_2> <tempo_2>
<id_tarefa_3> <tempo_3>
...
```
Como eu ainda estava a aprendendo a utilizar Regex em C++ quando escrevi esse código, o algoritmo que seleciona os dados da linha possui algumas limitações:
  - O id de cada tarefa só pode possuir uma combinação de letras maiúsculas/minúsculas e números. Caracteres como underline (_) e travessão (-) não são aceitos
  - O tempo de duração da tarefa deve ser um número inteiro (essa nem é uma limitação do algoritmo de Regex, mas o programa em si foi projetado para usar um contador inteiro)
  - Se houver mais de um caractere de espaço entre o id e o tempo, a linha toda é ignorada

Em uma atualização futura do programa eu pretendo melhorar isso.

## UML e um pouco sobre o código

Nesse projeto tive a oportunidade de aprender e praticar técnicas muito legais de C++, como ponteiros inteligentes, templates de classes, tratamento de exceções na linguagem e *move semantics* - um conceito que eu nem fazia ideia que existia e é muito útil.

Quando eu fiz o diagrama de classes desse projeto eu não só tive em mente as boas práticas de programação orientada a objetos (*single responsibility*, *open-closed principle* etc) mas também levei em consideração de como deveria ser a estrutura de um escalonador dentro de um sistema operacional. Por isso existem as classes Core, Task e Scheduler:

![escalonador-os-UML](https://github.com/Equiel-1703/escalonador-so/assets/96885946/5161a53a-9978-4dad-bd2e-3df42c014ab8)

Uma outra coisa que fiz nesse projeto foi tentar seguir à risca o ![Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). Esse guia contém uma série de regras e convenções usadas pela Google para desenvolvimento de código em C++. Algumas regras eu realmente gostei e vou levar pra vida, mas outras nem tanto.

Uma das coisas desse guia que eu realmente gostei foi a norma de nomear variáveis de classe usando *snake_case* seguido de um underline (_). Dessa forma, sabemos no código interno que isso é uma variável da classe que estamos trabalhando:
```
class SimulationResults
{
  private:
    int total_time_;
  ...
}
```
Mas uma regra que eu simplesmente não consegui seguir foi a de nomear métodos de uma classe usando *PascalCase*. Isso pra mim é muito contraintuitivo, principalmente por eu ter acostumado com Java. Em Java, tradicionalmente se nomeia classes em *PascalCase* e métodos em *camelCase*, assim no código temos uma diferença visível entre métodos e classes. Como eu não gostei dessa norma eu não segui ela no desenvolvimento desse código - como todo bom programador teimoso.

