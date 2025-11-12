# Justification.

# SFML
La razón de la implementacón fue facilitar la expericia a la hora de jugar damas chinas en este proyecto. Ya que el sistema en la terminal es un poco dificil de interactuar ya que solo se mueve por medio de cordenadas. Al integrarlo permite la persona utlizar el mouse para mayor eficiencia.

La necesidad radica en hacer un proyecto un poco mas completo, con dinámicas y herramientas más customer-friendly, también nos ayuda a expandir a otras areas del conociento.

Por medio de varios videos donde nos explican como funciona SFML y que hace cada una de las fucniones que podemos utlizar, juntos con la ayuda de busqueda en la web puedimos instalar SFML, utlizamos Visual Studio 2022, ya que el proceso de instalacion de las librerias SFML es mucho mas facil en comparacion a los demas ambientes de programacion.

# Interface grafica interactiva
La razón de esta innovación fue darle al judador unos colores estandares para saber en donde esta dando click, también que tipo de ficha tiene (Normal o Rey)

Fue necesario ya que al principio no se sabe que jugador es el que tiene el turno, o que ficha en especifico es el Rey o las Damas, Y junto con el terminal le da mas informacion al usuario sobre cúal es el tipo de movimiento que debe hacer, o que no puede hacer en, su defecto.

Dentro de las funciones integradas de SFML podemos escoger el ancho y color de las fugura y a tambien el color del relleno. Para en proyecto en especifico solo utlizamos una libreria perteneciente a SFML "SFML/Graphics.hpp" para realizar las graficas de la interface.

# Intergracion de el archivo "Linux.h"
Necesitamos portabilidad al sistema operativo de Linux, ya que se sabe que el profesor tiene Linux.

La necesidad se debe a que al tratar de correr el codigo desde el GitHub en un codespace, el sistema nos avisaba que el codigo tiene la libreria <conio.h> las cual solo esta disponible en Windows, lo cual impideria la copilacion del codigo en ese sistema operativo, al investigar tuvimos que utlizar AI para que nos puediera generar una extructura que fuera compatible con Lunix, solo para esa carpeta, ya que necesitabamos la funcion getch, que nos permite, o le permite al programa mostrar los props a serguir sin necesidad de precionar "Enter" y asi darle tiempo al usuario de ver el prop a seguir.



