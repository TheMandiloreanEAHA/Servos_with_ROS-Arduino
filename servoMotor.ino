/*
 ##--------------------------------Mover un servomotor con los valores recibidos de un tópico--------------------------------##
  El siguiente código es utilizado para mover un servomotor con respecto a los datos publicados en un tópic de tipo "jointState",
  Este pograma se suscribe al tópico y esta en constante escucha de los datos publicados del tópico. Los datos recibidos están en
  radianes, por lo que estos datos de conviertes a grados ya que así es como funciona el servomotor. También cuenta con una función
  que puede mapear un rango de valores dados a otro que sea deseado (De preferencia un rango de grados entre 0-180)

 NOTA:El contenido de este archivo debe ser un archivo de tipo arduino (.ino).
 */
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <sensor_msgs/JointState.h>

ros::NodeHandle  nh;

Servo servoPan;
Servo servoTilt;

// Función para mapear un rango de valores a otro. 
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Función convertir radianes a grados. 
float radianesAGrados(float rad) {
  return rad * (180.0 / PI);
}


//Función que se ejecutará una vez suscrito en el tópico
void servo_cb( const sensor_msgs::JointState& msg){
  //msg es el mensaje recibido en el tópico, los datos quye nos insterean, son position 0 y 1
  //Para ver esta info, escribir rostopic info "nombreDelTopico". Con este comando podremos ver la información necesaria para
  //poder manejarla.
  float pan_joint= msg.position[0];
  float tilt_joint = msg.position[1];
  float pan_angle;
  float tilt_angle;

  //Funciones de mapeo 
  // Mapeo de los valores de pan_joint del rango entregado(1.60 a 4.86) al rango de 0 a 180 grados para el servomotor
  //pan_angle = mapFloat(pan_joint, 1.60, 4.86, 0, 180);
  // Mapeo de los valores de tilt_joint del rango entregado(1.60 a 4.86) al rango de 0 a 180 grados para el servomotor
  //tilt_angle = mapFloat(tilt_joint, 0, 1.57, 0, 180);

  //Si ya estan establecidos los rangos de manera correcta en el URDF, lo que hay que hacer en convertir los valores
  // del JointState a grados (lo que se reciben son radianes)
  pan_angle = radianesAGrados(pan_joint);
  tilt_angle = radianesAGrados(tilt_joint);

  // Mapear tilt_angle al rango invertido 180-0 para corregir el movimiento invertido
  tilt_angle = mapFloat(tilt_angle, 25, 120, 140, 25);

  //Asignamos el resultado del mapeo al valor de la posicón del servo
  servoPan.write(pan_angle);
  servoTilt.write(tilt_angle);  
  digitalWrite(13, HIGH-digitalRead(13));  //Led de confirmación 
}

//NOs suscribimos al tópico
ros::Subscriber<sensor_msgs::JointState> sub("/joint_states", servo_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
  //Los servos están conectados en el pin 7 y 8
  servoPan.attach(7);
  servoTilt.attach(8);
}

void loop(){
  nh.spinOnce();
  delay(1);
}
