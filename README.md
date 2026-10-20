![Logo Institucional](https://github.com/JonatanBogadoUNLZ/PPS-Jonatan-Bogado/blob/9952aac097aca83a1aadfc26679fc7ec57369d82/LOGO%20AZUL%20HORIZONTAL%20-%20fondo%20transparente.png)

# VALIDACIÓN FUNCIONAL Y CONTROL DE MOVIMIENTO PARA MANIPULADOR ROBÓTICO DE 5 DOF (APLICACIÓN: ENSAMBLE DE RODILLOS DE PINTURA)

## Introducción / Objetivo

Este repositorio documenta el desarrollo y la implementación de la programación funcional básica para un brazo robótico de 5 grados de libertad (DOF) impreso en 3D. 

El objetivo principal de esta etapa es realizar las pruebas operativas iniciales del sistema para asegurar que la estructura mecánica, las transmisiones y los actuadores respondan correctamente a los requerimientos cinemáticos y de carga necesarios para la tarea específica de ensamble de rodillos de pintura.

## Índice
- [Introducción / Objetivo](#introducción--objetivo)
- [Descripción técnica y Hardware](#descripción-técnica-y-hardware)
- [Desafíos técnicos: Sincronización y Operación Armónica](#desafíos-técnicos-sincronización-y-operación-armónica)
- [Esquemático de Conexiones](#esquemático-de-conexiones)
- [Instrucciones de uso](#instrucciones-de-uso)
- [Tecnologías utilizadas](#tecnologías-utilizadas)
- [Autor](#autor)

---

## Descripción técnica y Hardware

El sistema de control y potencia está diseñado para gobernar un total de 5 ejes mediante motores paso a paso de alta precisión, gestionados a través de una arquitectura centralizada basada en hardware libre.

### Componentes Principales:
1. **Unidad de Control:** Arduino Mega 2560.
2. **Drivers de Potencia:** Drivers TB6560 para el control de los motores paso a paso.
3. **Configuración de Actuadores (Ejes):**
   - **Eje 1 (Base / Cintura):** Giro horizontal accionado por motor **NEMA 23**.
   - **Eje 2 (Hombro):** Pitch / Inclinación principal accionado por **dos motores NEMA 23** trabajando en conjunto para mayor torque.
   - **Eje 3 (Codo):** Pitch / Inclinación del segundo tramo accionado por motor **NEMA 17**.
   - **Eje 4 (Muñeca - Inclinación / Pitch):** Cabeceo del tramo final accionado por motor **NEMA 17**.
   - **Eje 5 (Muñeca - Rotación / Roll):** Giro axial de la punta accionado por motor **NEMA 17**.

---

## Desafíos técnicos: Sincronización y Operación Armónica

Uno de los principales retos en la puesta en marcha de sistemas mecatrónicos complejos radica en lograr una sincronización precisa entre cada uno de los eslabones y los mecanismos asociados. El objetivo fundamental es asegurar una transición fluida que permita un ciclo de trabajo rítmico, coordinado y de carácter plenamente rutinario. 

Como se puede apreciar en la ejecución del sistema, la coordinación temporal y espacial entre las trayectorias del manipulador robótico y los dispositivos auxiliares de la celda resulta indispensable para evitar interferencias mecánicas, optimizar los tiempos de ciclo y garantizar una operación continua, fluida y confiable en la línea de ensamble[cite: 2].

<video src="assets/VID-20260824-WA0010.mp4" controls width="100%"></video>
<div align="center">
  <small><small>Ilustración 2 Validación dinámica y sincronización de ciclos en la celda de trabajo</small></small>
</div><br>

---

## Esquemático de Conexiones

A continuación se detalla el diagrama de cableado y conexiones eléctricas entre la placa Arduino Mega 2560, los drivers TB6560 y los motores paso a paso del manipulador:

![Diagrama de Conexiones Arduino Mega y TB6560](https://github.com/user-attachments/assets/17008646115676987123)
<div align="center">
  <small><small>Ilustración 3 Diagrama de conexiones del sistema de control y potencia</small></small>
</div><br>

---

## Instrucciones de uso

1. **Requisitos previos:**
   - Tener instalado **Arduino IDE**.
   - Instalar la librería **AccelStepper** desde el gestor de librerías (`Sketch > Incluir librería > Administrar bibliotecas...`).
2. **Conexiones:**
   - Conectar los drivers **TB6560** a la placa **Arduino Mega 2560** respetando los pines definidos en el código (Step y Direction para cada eje) según el esquemático.
   - Asegurar la alimentación externa adecuada para los motores NEMA 23 y NEMA 17.
3. **Ejecución:**
   - Cargar el sketch correspondiente en el Arduino Mega.
   - Abrir el **Monitor Serie** configurado a **115200 baudios**.
   - Enviar comandos mediante el cuadro de texto utilizando el formato `[Motor],[Pasos],[Velocidad]` (por ejemplo: `1,200,500`).

## Tecnologías utilizadas
- **Hardware:** Arduino Mega 2560, Drivers TB6560, Motores NEMA 23 y NEMA 17.
- **Software:** Arduino IDE (C/C++).
- **Librerías:** `AccelStepper`.

## Autor
* **Alberto Mandrini**
