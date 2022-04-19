# Morfologia
/*PL*/
Projekt z kursu "Programowanie2".
Plik Morfologia.cpp dostarcza pochodne klas zdefinoiwanych w pliku Morfologia.h
Zadaniem klas pochodnych jest wykonywanie okreslonych operacji morfologicznych na bitmapach.
/*ENG*/
The file "Morfologia.cpp" provides the representation of 3-Dimensional bitmap, which bits can be white or black.
It also provides following morphological operations: (PL in parentheses)
-Inwersion(Inwersja)- changes color of all bits to oposite
-Erosion(Erozja)- changes black bits, whichs at least one neighbor was white, to white.
-Dilatation(Dylatacja) - oppostie to previous one
-Clearing(Zerowanie) - sets all of bits to white
-Averaging(Usrednianie) - if a bit have more than 3 neighbors in same color, it gets this color.
