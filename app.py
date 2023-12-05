from flask import Flask, render_template, request
#import smbus  # Para la comunicación I2C

app = Flask(__name__)

# Dirección del dispositivo Arduino en el bus I2C
#ARDUINO_ADDRESS = 0x12

# Crear una instancia del bus I2C
#bus = smbus.SMBus(1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/control', methods=['POST'])
def control():
    # Obtener datos del formulario
    fan_power = int(request.form['fan_power'])
    light_power = int(request.form['light_power'])
    min_temp = int(request.form['min_temp']) #Si tem < min se apaga ventilador 
    max_temp = int(request.form['max_temp']) #tem > max se enciende ventilador 
    temp_cycle = int(request.form['temp_cycle'])
    irrigate_cycle = int(request.form['irrigate_cycle'])

    # Enviar datos al Arduino a través de I2C
    data = [fan_power, light_power, min_temp, max_temp, temp_cycle, irrigate_cycle]
    #bus.write_i2c_block_data(ARDUINO_ADDRESS, 0, data)
    print(data)
    return render_template('index.html', message='Datos enviados con éxito.')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
