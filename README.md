# InertChamberSystem

En soldadura eléctrica y de arco se usan tradicionalmente gases inertes para mejorar los resultados. El cometido de estos gases es proteger la zona de soldadura de la oxidación a altas temperaturas eliminando el oxigeno y el vapor de agua.

El proceso de impresión 3d mediante fusión selectiva por láser es una forma de soldadura. Realizar el proceso de impresión en una atmósfera inerte no solo mejora el resultado final sino que posible trabajar con materiales como el titanio o el aluminio que en forma de polvo son explosivos.

## Componentes del sistema

### Sistema mecánico

el sistema mecánico de recirculación se compone de los siguientes elementos:

- Válvula de la entrada de gas inerte
- Válvula de expulsión de gas
- Válvula de entrada de aire.
- Válvula de seguridad ante sobrepresión.
- bomba de aire.
- filtro.

### Sensores

los parámetros a controlar en la cámara inerte son:

- Humedad ambiente.
- Temperatura.
- Presión.
- nivel de oxigeno.

### Software de control

## Ciclo de trabajo del sistema

El comportamiento de una cámara de control de atmósfera puede modelarse como una máquina de estados. Los estados encontrados son:

- Reposo
- Llenado
- Estabilización
- Trabajo
- Parada

### Reposo

Antes de activar la cámara inerte la presión en ella es de 1Atm y la presencia de oxígeno es de un 20% la humedad es variable. Todo el sistema se encuentra desactivado. 

En este estado se puede mantener la puerta abierta y operar dentro de la cámara.

### Llenado

En la fase de llenado se mantiene abierta la válvula de expulsión de gas y la entrada de gas inerte.
Se mantiene este estado hasta que los niveles de humedad y oxigeno bajan a los umbrales requeridos <5%

### Estabilización

En la fase de estabilización, se cierra la salida de aire, se enciende la bomba de recirculación y
se mantiene abierta la entrada de gas inerte hasta lograr una ligera sobrepresión (+20 milibares). En ese momento se vuelve al estado de llenado y se repite el proceso hasta lograr los umbrales de oxigeno y humedad de trabajo <1%

### Trabajo

En este estado se realiza el proceso de impresión. Durante el ciclo de trabajo el motor de recirculación está encendido y la válvula de argón se abre para compensar las perdidas de presión debidas a falta de estanqueidad de la máquina.

En caso de que el sensor de oxígeno o el de humedad sobrepasen los umbrales, se interrumpe la impresión y se regresa al estado de estabilización.

### Parada

Cuando se termina la impresión, se espera un tiempo determinado para igualar presiones y temperaturas con el motor de recirculación encendido y el resto de válvulas cerrado.
Transcurrido este tiempo se abre las válvulas de salida de gases y se permite la apertura de puertas.


### Software

El software de control de la cámara está realizado para la plataforma de microcontroladores Arduino. De esta forma se puede seleccionar entre una gran variedad de hardware final. Los requerimientos de este sistema de control no son muy elevados, pudiendo cubrirse perfectamente con un 
Arduino Uno.