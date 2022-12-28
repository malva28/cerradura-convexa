# cerradura-convexa
Este repositorio es parte de una tarea realizada en el curso de Geometría Computacional (CC5502), Universidad de Chile.

Programa construído sobre la librería de [Elementos geométricos](https://github.com/malva28/elementos-geometricos). Implementa distintos métodos para calcular cerraduras convexas.

Los algoritmos de cerradura convexa son los de Gift Wrapping y Graham Scan, que
están programados en la carpeta `src`.

Los tests de validez están en la carpeta `test`. `testConvexHull.cpp` verifica que el 
algoritmo entregue resultados correctos para pequeños datasets.

Los tests de performance están en la carpeta `test/timePerformance`. 
`testPerformanceCH.cpp` mide el tiempo tomado por los algoritmos en dos escenarios:

 - con un tamaño de nube de puntos variables, tomando 27 tamaños del 1000 al 900000
 
 - con un tamaño fijo de nube, pero número creciente de vértices sobre la cerradura
     convexa, tamaño fijo de 100000 puntos y 21 vértices que van de 3 a 100000

Este archivo puede ejecutarse para exportar los resultados de tiempo medido en
archivos csv. Notar sin embargo que éstos resultados se guardan en la carpeta
de build!

El programa para generar gráficos está integrado en código Python, usando 
`matplotlib`, en la misma carpeta `test/timePerformance`: se denomina `plotter.py`.
Para mostrar los dos gráficos de los escenarios mencionados anteriormente, se 
agregan los siguientes como parámetros a la llamada en consola:

```
python plotter.py [--chInc] [--chVert]
```

También se pueden agregar las opciones `[--log10]`, `[--xlog10]` e `[--ylog10]` para 
mostrar los datos en algún eje en escala logarítmica 10.
