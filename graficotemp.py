SLAVE_ADDR = 0x0A # I2C Address of Arduino 1
# Name of the file in which the log is kept
LOG_FILE = './temp.log'
from smbus2 import SMBus, i2c_msg
import time
import traceback
import struct
import matplotlib.pyplot as plt
import os
import numpy as np
# Initialize the I2C bus;
# RPI version 1 requires smbus.SMBus(0)
i2c = SMBus(1)
def readTemperature():
	try:
		msg = i2c_msg.read(SLAVE_ADDR, 4)
		i2c.i2c_rdwr(msg)
		data = list(msg)
		ba = bytearray(data[0:4])
		temp = struct.unpack('<f', ba)
		print('Received temp: {} = {}'.format(data,temp))
		return temp
	except:
		traceback.print_exc()
		return None

def log_temp(temperature):
	try:
		with open(LOG_FILE, 'w+') as fp:
			fp.write('{} {} C\n'.format(
			time.time(),
			temperature
		))
	except:
		return

def plot(times,temps, line,ax):
	with open(LOG_FILE, 'r') as f:
		for l in f:
			l = l.strip()
			if l:
				time_value, temp_value,T = l.split()
				time = float(time_value)
				temp = float(temp_value.strip('(),'))
				times.append(time)
				temps.append(temp)
				line.set_xdata(times)
				line.set_ydata(temps)
				#Racalcula la información debido a actualizaciones
				ax.relim()
				#Genera un autoescalamiento el primer valor es para un valor de límite en su expansión, el segundo y tercero escala X y Y respectivamente
				ax.autoscale_view(True,True,True)
				#plt.draw()
				plt.savefig("./static/graficotemp.jpg")
				plt.pause(0.1)	
	plt.xlabel('Tiempo')
	plt.ylabel('Temperatura °C')
	plt.title('Historico Temperatura')
	
	
def main():
	#Encendemos el modo interactivo para que no sea bloqueante el proceso
	plt.ion()
	#plt.draw()
	times = []
	temps = []
	#Obtenemos los ejes del objeto plot
	ax = plt.gca()
	ax.set_autoscale_on(True)
	#Obtenemos el objeto de linea que nos permite dibujar de nuevo
	line, = ax.plot(times,temps)
	while True:
		try:
			cTemp = readTemperature()
			log_temp(cTemp)
			plot(times,temps,line,ax)
			plt.show()
			time.sleep(1)
			
		except KeyboardInterrupt:
			return

if __name__ == '__main__':
	main()
