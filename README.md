# Simulador de Escalonador

Este programa é um simulador de um escalonador - um dos principais componentes de um sistema operacional. Ele possui dois algoritmos implementados: SJF (Shortest Job First) e GJF (Greatest Job First). Para usá-lo, é preciso fornecer como entrada o arquivo contendo as tarefas para ele escalonar, o número de cores do processador da simulação e a política de escalonamento:

```simulador-so <arquivo_com_tarefas.txt> <nro_de_cores> [OPCIONAL]<politica: s(padrao) | g>```

Onde: 
- \<arquivo_com_tarefas.txt> é o caminho do arquivo contendo as tarefas para o escalonador. A forma que esse arquivo deve ser estruturado é explicado mais abaixo
- \<nro_de_cores> é o número de cores do processador da simulação
- \<politica> [OPCIONAL] é a política de escalonamento usada para selecionar as tarefas. Como dito anteriormente, há duas políticas implementadas:
  - s -> Shortest Job First, nessa política as tarefas **menores** são executadas primeiro
  - g -> Greatest Job First, tarefas **maiores** são executadas primeiro  

  Se o parâmetro `<política>` não for fornecido, o simulador executa usando SJF.
