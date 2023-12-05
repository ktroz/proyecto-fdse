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
    accion = int(request.form['accion'])
    value_ac = float(request.form['value_ac'])
    
    # Enviar datos al Arduino a través de I2C
    data = [accion, value_ac]
    #bus.write_i2c_block_data(ARDUINO_ADDRESS, 0, data)
    print(data)
    return render_template('index.html', message='Datos enviados con éxito.')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
