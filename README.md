![Logo Institucional](https://github.com/JonatanBogadoUNLZ/PPS-Jonatan-Bogado/blob/9952aac097aca83a1aadfc26679fc7ec57369d82/LOGO%20AZUL%20HORIZONTAL%20-%20fondo%20transparente.png)

# VALIDACIÓN FUNCIONAL Y CONTROL DE MOVIMIENTO PARA MANIPULADOR ROBÓTICO DE 5 DOF (APLICACIÓN: ENSAMBLE DE RODILLOS DE PINTURA)

## Índice
- [Introducción / Objetivo](#introducción--objetivo)
- [Descripción técnica y Hardware](#descripción-técnica-y-hardware)
- [Desafíos técnicos: Sincronización y Operación Armónica](#desafíos-técnicos-sincronización-y-operación-armónica)
- [Esquemático de Conexiones](#esquemático-de-conexiones)
- [Instrucciones de uso](#instrucciones-de-uso)
- [Tecnologías utilizadas](#tecnologías-utilizadas)


## Introducción / Objetivo

Este repositorio documenta el desarrollo y la implementación de la programación funcional básica para un brazo robótico de 5 grados de libertad (DOF) impreso en 3D. 

El objetivo principal de esta etapa es realizar las pruebas operativas iniciales del sistema para asegurar que la estructura mecánica, las transmisiones y los actuadores respondan correctamente a los requerimientos cinemáticos y de carga necesarios para la tarea específica de ensamble de rodillos de pintura.

---

## Descripción técnica y Hardware

El sistema de control y potencia está diseñado para gobernar un total de 5 ejes mediante motores paso a paso de alta precisión, gestionados a través de una arquitectura centralizada basada en hardware libre.

### Componentes Principales:
1. **Unidad de Control:** Arduino Mega 2560.
2. **Drivers de Potencia:** Drivers TB6600 para el control de los motores paso a paso.
3. **Configuración de Actuadores (Ejes):**
   - **Eje 1 (Base / Cintura):** Giro horizontal accionado por motor **NEMA 23**.
   - **Eje 2 (Hombro):** Pitch / Inclinación principal accionado por **dos motores NEMA 23** trabajando en conjunto para mayor torque.
   - **Eje 3 (Codo):** Pitch / Inclinación del segundo tramo accionado por motor **NEMA 17**.
   - **Eje 4 (Muñeca - Inclinación / Pitch):** Cabeceo del tramo final accionado por motor **NEMA 17**.
   - **Eje 5 (Muñeca - Rotación / Roll):** Giro axial de la punta accionado por motor **NEMA 17**.

---

## Desafíos técnicos: Sincronización y Operación Armónica

Uno de los principales retos en la puesta en marcha de sistemas mecatrónicos complejos radica en lograr una sincronización precisa entre cada uno de los eslabones y los mecanismos asociados. El objetivo fundamental es asegurar una transición fluida que permita un ciclo de trabajo rítmico, coordinado y de carácter plenamente rutinario. 
Si bien el objetivo de la intervención en la programación del projecto es la validación de los componentes y que a posteriori, el software de programación para el robot será optimizado, era imprescindible que se pueda orquestar todos los movimiento de forma optima.

Como se puede apreciar en la ejecución del sistema, la coordinación temporal y espacial entre las trayectorias del manipulador robótico y los dispositivos auxiliares de la celda resulta indispensable para evitar interferencias mecánicas, optimizar los tiempos de ciclo y garantizar una operación continua, fluida y confiable en la línea de ensamble[cite: 2].

[▶ Ver video de validación dinámica](https://raw.githubusercontent.com/amandrini/2026_2C_PPS_PROGRAMACION_FUNCIONAL-CONTROL_MANIPULADOR_ROB-TICO/main/Multimedia/VID-20260824-WA0010.mp4)

<div align="center">
  <small><small>video 1: Intento de calibración y sincronización de ciclos en la celda de trabajo[cite: 2]</small></small>
</div><br>

---

## Esquemático de Conexiones

A continuación se detalla el diagrama de cableado y conexiones eléctricas entre la placa Arduino Mega 2560, los drivers TB6600 y los motores paso a paso del manipulador:

[Ver Diagrama de Conexiones - TB6600 (PDF)](https://github.com/amandrini/2026_2C_PPS_PROGRAMACION_FUNCIONAL-CONTROL_MANIPULADOR_ROB-TICO/blob/main/Multimedia/Robot_5GDL.pdf)
  <small><small>Ilustración 3 Diagrama de conexiones del sistema de control y potencia</small></small>
</div><br>

---

## Instrucciones de uso

1. **Configuración del sistema y envío de comandos:**
   - Cargar el código correspondiente en la placa Arduino Mega 2560 utilizando el Arduino IDE.
   - Abrir el Monitor Serie configurado a una velocidad de 115200 baudios.
     
   **Carga los movimientos paso a paso:**
- Para armar un grupo de movimiento simultáneo, ingresa los datos de cada eje con el formato [Eje],[Pasos],[Velocidad] y presiona Enter.

- Una vez que hayas definido los ejes que deseas que se muevan al mismo tiempo en ese paso, escribe la palabra GUARDAR y presiona Enter para registrarlo en la memoria del Arduino.

 - Repite este proceso para agregar más pasos a tu rutina.

- Inicia la secuencia:
Cuando ya hayas guardado todos los pasos que necesitas, escribe la palabra INICIO y presiona Enter. El robot comenzará a ejecutar la rutina de forma ordenada, esperando a que cada grupo de motores termine su recorrido y frene por completo antes de pasar al siguiente movimiento.

2. **Consideración crítica para el Eje 2 (Hombro - Doble NEMA 23):**
   - Dado que el hombro utiliza **dos motores NEMA 23** acoplados mecánicamente para traccionar en conjunto y soportar el esfuerzo de carga, es indispensable asegurar físicamente que ambos giren en **sentidos opuestos** (contrarios). 
   - Debido a la disposición simétrica o de espejo en la que se montan mecánicamente ambos motores en la estructura, **se debe invertir físicamente la conexión de una de las fases (por ejemplo, intercambiando los cables A+ y A-) en los bornes del driver TB6560 de uno de los motores**. De esta manera, al recibir la misma señal de giro, los ejes mecánicos traccionarán de forma simétrica y colaborativa sin forzar ni bloquear la estructura.

## Tecnologías utilizadas
- **Hardware:** Arduino Mega 2560, Drivers TB6600, Motores NEMA 23 y NEMA 17.
- **Software:** Arduino IDE (C/C++).
- **Librerías:** `AccelStepper`.

