from smbus2 import SMBus, i2c_msg
import struct
import time
import traceback

SLAVE_ADDR = 0x0A

i2c = SMBus(1)

def readMsg():
	try:
		# Creates a message object to read 4 bytes from SLAVE_ADDR
		msg = i2c_msg.read(SLAVE_ADDR, 4)
		i2c.i2c_rdwr(msg)  # Performs write
		data = list(msg)   # Converts stream to list
		# list to array of bytes (required to decode)
		ba = bytearray(data[0:4])
		temp = struct.unpack('<f', ba)
		return temp
	except:
		traceback.print_exc()
		return None

def writeMsg(cmd,data):
	try:
		opcode = struct.pack('<c <f',cmd,data) # Packs number as char and float
		# Creates a message object to write 4 bytes from SLAVE_ADDR
		msg = i2c_msg.write(SLAVE_ADDR, opcode)
		i2c.i2c_rdwr(msg)  # Performs write
	except:
		pass
def main():
    while True:
        try:
            cmd = input("Cmd to execute:")
            cmd = chr(cmd)
            data = input("Data:")
            data = float(data)
            writeMsg(cmd,data)
            print("El mesaje es:")
            print(readMsg())
        except KeyboardInterrupt:
        	print("program was stopped manually")
		except:
            traceback.print_exc()		
main()