## Лабораторная работа №2
# Создание контейнерного класса

### Условие:
Спроектировать библиотечный контейнерный класс, реализовать его интерфейс и обеспечить механизмы работы с объектами контейнерного класса.


#### Должно быть:
* шаблон;
* накладывание ограничений;
* избыточный интерфейс;
* перегрузка оперторов;
* обработка исключительных ситуаций;
* реализация итераторов.


#### Варинты:
* **матрица** (мой вариант)
* список
* вектор
* множество
* дерево (на 3 дополнительных балла)

Способ определения варианта: **(Номер по журналу - 1) % 4 + 1**.

A flexible matrix class should support a wide variety of mathematical operations in order to reduce the need for the client to write excess code. In particular, the basic binary operators should be supported for various matrix interactions. We would like to be able to add, subtract and multiply matrices, take their transpose, multiply a matrix and vector as well as add, subtract, multiply or divide all elements by a scalar value. We will need to access elements individually by their row and column index.