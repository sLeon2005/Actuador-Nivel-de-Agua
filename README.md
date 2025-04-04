
# Documentación

En este repositorio se mostrarán todos los documentos de fabricación, BOM, código y manuales relacionados con el dispositivo.

![Render 3D](https://github.com/sLeon2005/Actuador-Nivel-de-Agua/blob/main/render.png?raw=true)

## BOM (Bill of Materials)

#### ¿Qué es esta BOM?
La **BOM (Bill of Materials)** o **Lista de Materiales** es un documento esencial para la fabricación y ensamble de la tarjeta electrónica de este proyecto. Aquí se detallan todos los componentes necesarios, incluyendo su valor, tipo de empaquetado y la cantidad requerida.

| Referencia       | Valor                  | Empaquetado         | Cantidad |
|------------------|------------------------|----------------------|----------|
| C1, C2           | 100uF                  | 6.3mm P2.50mm        | 2        |
| C3, C4, C6, C10  | 100nF                  | SMD 1206             | 4        |
| C7               | 10uF                   | SMD 1206             | 1        |
| C8, C9           | 22pF                   | SMD 1206             | 2        |
| D1, ON1, RX1, TX1| Led red                | SMD 1206             | 4        |
| D2               | WS2812B                | Neopixel             | 1        |
| D3               | 1N5819                 | SOD-123              | 1        |
| D4               | 1N4007                 | DO-41                | 1        |
| F1               | Fuse                   | SMD 1206             | 1        |
| J1, J3           | Screw Terminal 2 pines | 5.08mm Pitch         | 2        |
| J2               | Pin Header 3x2         | 2.54mm               | 1        |
| J6               | USB Type-B             | Through-hole         | 1        |
| J8               | Pin Socket 1x4         | 2.54mm               | 1        |
| Q1               | NMOS                   | TO-220-3             | 1        |
| R1, R2, R3, R4, R8| 1K                    | SMD 1206             | 5        |
| R5               | 5.1K                   | SMD 1206             | 1        |
| R6, R9           | 10K                    | SMD 1206             | 2        |
| SW1, SW2         | Botón push open dual   | 6x6mm THT            | 2        |
| U1               | AMS1117-5.0            | SOT-223              | 1        |
| U3               | CH340C                 | SOIC-16              | 1        |
| U4               | ATmega328-P            | DIP-28               | 1        |
| Y1               | Cristal 16 MHz         | HC49-4H              | 1        |

Aparte de estads piezas, también será necesario conseguir una fuente de alimentación de entre 7 a 12 Volts, una válvula solenoide y un sensor ultrasónico de distancia HC-SR04.

## Funcionamiento

El primer paso para empezar a usar este actuador es cablear el circuito. Empezando con la válvula solenoide, esta tiene dos terminales, y conectaremos cada una a la bornera que se encuentra en la parte inferior derecha del circuito.
En cuanto a la alimentación, una vez que se halla encontrado una fuente con un voltaje dentro del rango adecuado (7 a 12 Volts), pele sus cables y conecte el negativo a la bornera marcada con "-" y el positivo a la bornera marcada con "+", estas dos están en la parte inferior izquierda.
Finalmente, habrá que conectar el sensor HC-SR04, este se conectará al puerto de cuatro pines ubicado en la parte inferior central de la pantalla. El pin superior de la placa irá conectado a VCC del sensor, el 2do pin irá conectado a Trigger, el tercero a Echo, y finalmente el último pin se conecta con GND.
El siguiente diagrama explica estas mismas conexiones:

![Diagrama de cableado](https://github.com/sLeon2005/Actuador-Nivel-de-Agua/blob/main/recursos/conexiones.png?raw=true)

Una vez que ya esté cableado y montado el circuito en donde se va a usar, conéctelo a la corriente para que empiece a funcionar. Asegúrse de haber montado el sensor ultrasónico en el lugar adecuado para leer la distancia hacia el agua. El botón de "SET" será su única forma de ingresar datos a la memoria, para hacer esto, espere a que el nivel de agua llegue a la altura que se considera como lleno e inmediatamente después presione el botón "SET", el led indicador se iluminará color verde por unos pocos segundos para confirmar que se guardó la distancia. Este valor de distancia se almacenará dentro de la memoria no-volátil, por lo que aún si se desconecta el dispositivo o si se va la luz, el dato no se borrará.
En cuanto el nivel del agua baje y sea menor que la altura guardada, la válvula solenoide se activará, es decir, permitirá pasar el flujo del agua.
Mientras el nivel de agua sea mayor o igual al nivel guardado, la válvula no dejará fluir agua.
