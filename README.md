# Modulo de transmisión de datos por frecuencia de radio con Arduino

Este es un pequeño ejemplo de cómo comunicar dos dispositivos Arduino por medio de FR.
Para esto pueden utilizar un módulo como este [http://www.seeedstudio.com/wiki/433Mhz_RF_link_kit] y un microcontrolador Arduino o compatibles.

Implementé un pequeño control remoto que transmite una hilera de caracteres representando el estado de los botones del control. El control tiene una estructura parecida a un control de Play Station en el sentido que tiene botones de movimiento, botones especiales (equis, triangulo, cuadrado, circulo) y un L1 y R1. El transmisor envía una hilera de 8 caracteres donde los primeros 6 corresponden a los estados de los botones de la izquierda y los superiores. En orden: L1, R1, CIRCULO, EQUIS, CUADRADO, TRIANGULO. El 7° caracter es el estado de movimiento, en este caso solo se puede presionar un botón de movimiento a la vez. El estado se representa con los caracteres '0' y '1'. El 8° caracter representa el tipo de movimiento actual, en orden ARRIBA, DERECHA, ABAJO, IZQUIERDA.

Para más información acerca de la construcción del motor visitar [http://probablyageek.com/comuncacion-entre-arduinos-usando-frecuencias-de-radio/]