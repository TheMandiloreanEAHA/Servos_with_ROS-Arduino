# Servos_with_ROS-Arduino
 El siguiente código es utilizado para mover un servomotor con respecto a los datos publicados en un tópico de tipo "jointState",
Este pograma se suscribe al tópico y esta en constante escucha de los datos publicados del tópico. Los datos recibidos están en
radianes, por lo que estos datos de conviertes a grados ya que así es como funciona el servomotor. También cuenta con una función
que puede mapear un rango de valores dados a otro que sea deseado (De preferencia un rango de grados entre 0-180)

# ¿Cómo usarlo?
1. Primero se tienen que conectar los servomotores a los pines correspondientes en la Arduino.
2. Una vez hecho esto y cargado el programa, debemos levantar el master en ROS
´´´bash
roscore
´´´
3. Ahora debemos abrir el puerto donde se comunicará ROS con arduino (serialnode)
´´´bash
#Completar
´´´
4. Ahora debemos publicar en el tópico al que estamos sucritos. Publicar un Joint State de manera manual puede ser bastante tedioso, por lo que yo
recominedo hacer un launcher que inicalice Rviz con un modelo URDF cargado y que abra una interfaz Joint State Publisher GUI, el cual contenga 2 joints que hagan referencia a los servos que intentas mover.
En mi caso, utilicé el modelo de una unidad PantTilt
