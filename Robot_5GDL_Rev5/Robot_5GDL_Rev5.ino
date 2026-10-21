#include <AccelStepper.h>

const int E1_STEP = 2;  const int E1_DIR = 3;
const int E2A_STEP = 4; const int E2A_DIR = 5;
const int E2B_STEP = 6; const int E2B_DIR = 7;
const int E3_STEP = 8;  const int E3_DIR = 9;
const int E4_STEP = 10; const int E4_DIR = 11;
const int E5_STEP = 12; const int E5_DIR = 13;


AccelStepper stepper1(AccelStepper::DRIVER, E1_STEP, E1_DIR);
AccelStepper stepper2A(AccelStepper::DRIVER, E2A_STEP, E2A_DIR);
AccelStepper stepper2B(AccelStepper::DRIVER, E2B_STEP, E2B_DIR); // Espejo del hombro
AccelStepper stepper3(AccelStepper::DRIVER, E3_STEP, E3_DIR);
AccelStepper stepper4(AccelStepper::DRIVER, E4_STEP, E4_DIR);
AccelStepper stepper5(AccelStepper::DRIVER, E5_STEP, E5_DIR);


struct PasoSecuencia {
  long p1;
  long p2;
  long p3;
  long p4;
  long p5;
  float velocidad;
};


const int MAX_PASOS = 20; 
PasoSecuencia secuencia[MAX_PASOS];
int totalPasosSecuencia = 0;
int indiceActual = 0;
bool secuenciaActiva = false;

// Variables temporales para acumular los movimientos de un mismo paso
long tempP1 = 0, tempP2 = 0, tempP3 = 0, tempP4 = 0, tempP5 = 0;
float tempVel = 500;

void setup() {
  Serial.begin(115200);
  
  // Configurar el motor espejo del hombro (Eje 2B) en sentido inverso
  stepper2B.setPinsInverted(true, false, false); 

  // Configurar velocidades máximas y aceleraciones por defecto
  stepper1.setMaxSpeed(1000);  stepper1.setAcceleration(500);
  stepper2A.setMaxSpeed(800);   stepper2A.setAcceleration(400);
  stepper2B.setMaxSpeed(800);   stepper2B.setAcceleration(400);
  stepper3.setMaxSpeed(1000);  stepper3.setAcceleration(500);
  stepper4.setMaxSpeed(1000);  stepper4.setAcceleration(500);
  stepper5.setMaxSpeed(1000);  stepper5.setAcceleration(500);

  mostrarAyuda();
}

void loop() {
  // Procesar comandos recibidos por el Monitor Serie
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    // Comando para iniciar la ejecución
    if (input.equalsIgnoreCase("INICIO")) {
      if (totalPasosSecuencia > 0) {
        indiceActual = 0;
        secuenciaActiva = true;
        Serial.println(">>> ¡Iniciando secuencia grabada!");
        cargarPasoSecuencia(indiceActual);
      } else {
        Serial.println("⚠️ La secuencia está vacía. Agrega pasos primero.");
      }
      return;
    }
    
    // Comando para limpiar o reiniciar la memoria
    if (input.equalsIgnoreCase("RESET")) {
      secuenciaActiva = false;
      totalPasosSecuencia = 0;
      indiceActual = 0;
      reiniciarTemporales();
      Serial.println("🗑️ Secuencia borrada. Puedes programar nuevos pasos.");
      return;
    }

    // Comando para confirmar y guardar el paso actual
    if (input.equalsIgnoreCase("GUARDAR")) {
      if (totalPasosSecuencia < MAX_PASOS) {
        secuencia[totalPasosSecuencia] = {tempP1, tempP2, tempP3, tempP4, tempP5, tempVel};
        Serial.print("✅ Paso "); Serial.print(totalPasosSecuencia); 
        Serial.println(" guardado en la memoria.");
        totalPasosSecuencia++;
        reiniciarTemporales();
        Serial.println("Ingresa los datos para el siguiente paso (o escribe INICIO):");
      } else {
        Serial.println("⚠️ Memoria de secuencia llena.");
      }
      return;
    }

    // Procesar entrada de motores: [Eje],[Pasos],[Velocidad]
    int firstComma = input.indexOf(',');
    int secondComma = input.indexOf(',', firstComma + 1);
    
    if (firstComma > 0 && secondComma > firstComma) {
      int eje = input.substring(0, firstComma).toInt();
      long pasos = input.substring(firstComma + 1, secondComma).toInt();
      float velocidad = input.substring(secondComma + 1).toFloat();
      
      switch (eje) {
        case 1: tempP1 = pasos; break;
        case 2: tempP2 = pasos; break;
        case 3: tempP3 = pasos; break;
        case 4: tempP4 = pasos; break;
        case 5: tempP5 = pasos; break;
        default: Serial.println("Eje no válido (use 1 a 5)."); break;
      }
      if (velocidad > 0) tempVel = velocidad;
      
      Serial.print("-> Acumulado para este paso [Eje "); Serial.print(eje); 
      Serial.print(": "); Serial.print(pasos); Serial.print(" pasos]. ");
      Serial.println("Escribe otro eje, 'GUARDAR' para cerrar el paso, o 'INICIO'.");
    } else {
      Serial.println("❌ Formato incorrecto. Use: Eje,Pasos,Velocidad (ej: 1,400,600) o comandos GUARDAR/INICIO/RESET");
    }
  }

  // Ejecución de la máquina de estados no bloqueante cuando la secuencia está activa
  if (secuenciaActiva) {
    if (stepper1.distanceToGo() == 0 && 
        stepper2A.distanceToGo() == 0 && 
        stepper2B.distanceToGo() == 0 && 
        stepper3.distanceToGo() == 0 && 
        stepper4.distanceToGo() == 0 && 
        stepper5.distanceToGo() == 0) {
        
      Serial.print("Paso "); Serial.print(indiceActual); Serial.println(" completado.");
      indiceActual++;
      
      if (indiceActual >= totalPasosSecuencia) {
        secuenciaActiva = false;
        Serial.println(">>> 🎉 ¡Secuencia completa finalizada con éxito!");
      } else {
        cargarPasoSecuencia(indiceActual);
      }
    }
  }

  // Mantener los pulsos constantes de todos los motores
  stepper1.run();
  stepper2A.run();
  stepper2B.run();
  stepper3.run();
  stepper4.run();
  stepper5.run();
}

void reiniciarTemporales() {
  tempP1 = 0; tempP2 = 0; tempP3 = 0; tempP4 = 0; tempP5 = 0;
  tempVel = 500;
}

void cargarPasoSecuencia(int idx) {
  stepper1.setMaxSpeed(secuencia[idx].velocidad);
  stepper2A.setMaxSpeed(secuencia[idx].velocidad);
  stepper2B.setMaxSpeed(secuencia[idx].velocidad);
  stepper3.setMaxSpeed(secuencia[idx].velocidad);
  stepper4.setMaxSpeed(secuencia[idx].velocidad);
  stepper5.setMaxSpeed(secuencia[idx].velocidad);

  stepper1.move(secuencia[idx].p1);
  stepper2A.move(secuencia[idx].p2);
  stepper2B.move(secuencia[idx].p2); // Espejo automático del hombro
  stepper3.move(secuencia[idx].p3);
  stepper4.move(secuencia[idx].p4);
  stepper5.move(secuencia[idx].p5);

  Serial.print("Ejecutando Paso ["); Serial.print(idx); Serial.println("]...");
}

void mostrarAyuda() {
  Serial.println("--- CREADOR DE SECUENCIAS DESDE CONSOLA ---");
  Serial.println("1. Envía motores independientes para armar un paso (Ej: 1,400,600)");
  Serial.println("2. Envía 'GUARDAR' para registrar el paso actual en la memoria.");
  Serial.println("3. Envía 'INICIO' para ejecutar toda la secuencia grabada.");
  Serial.println("4. Envía 'RESET' para borrar todo y empezar de nuevo.");
  Serial.println("---------------------------------------------");
}