/*
  Titre      : Projet Final - réalisation d'une boussole à partir des données du capteur GY-521 et affichage web
  Auteur     : KOUBELAN RICHARD AKPAGNI
  Date       : 09/04/2023
  Description: Ce code nous permet de faire une mise à jour de changer la couleur d'arrière plan de 
               de notre page web grâce à OTA
  Version    : 2.1.3
*/

// Insertion des librairies
#include <Arduino.h>
#include <Wire.h>                 // Librairie de communication I2C
#include <MPU6050.h>             // Librairie du capteur GY-521




// Création d'un objet du capteur MPU-6050 à partir de la classe
  MPU6050 mpu;



// Variables pour stocker les données d'inclinaison et d'orientation
  int inclinaison_x = 0;
  int inclinaison_y = 0;
  int inclinaison_z = 0;
  int orientation = 0;
  



void setup() {

// Initialisation de la communication du moniteur sérial
  Serial.begin(9600);

// Initialisation du capteur MPU-6050
  Wire.begin();
  mpu.initialize();


 
}

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

// Calcule des angles de tangage et de roulis à partir des données d'accéléromètre
  float accel_magnitude = sqrt(ax * ax + ay * ay + az * az);
  inclinaison_x = (int)(atan2(ay, sqrt(ax * ax + az * az)) * 180 / PI);
  inclinaison_y = (int)(atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI);
  inclinaison_z = (int)(atan2(sqrt(ax * ax + ay * ay), az) * 180 / PI);

// Calcule de l'orientation à partir des données du capteur 
  orientation = (int)(atan2(gy, gz) * 180 / PI);
  
// Ajout d'un délai pour éviter de surcharger le capteur
  delay(1000);
}