import serial
import sys

port = sys.argv[1:][0]
baudrate = int(sys.argv[1:][1])
file = sys.argv[1:][2]

PROGRESS_BAR_WIDTH = 50


ser = serial.Serial(port, baudrate, parity = serial.PARITY_NONE, bytesize = 8, stopbits=1)

num_lines = 0
with open(file, 'r') as f:
    num_lines = sum(1 for line in f)


print("Sending Hex file...")
hexFile = open(file, 'r')

i = 0
response = b'ok\r'
line = ""
while i < num_lines:
    #if prev respons is "ok" send the next hex line
    if response == b'ok\r':
        #send next line if previous response is "ok"
        line = hexFile.readline()
        if(line == ''):
            print("Finished writing HEX file.")
            break
        line = line[:len(line)-1] #remove '\n' at end of line 
        line = line + '\r' #add '\r'
        ser.write(line.encode())

        
    #get response of the bootloader
    response = ser.read_until(b'\r')

    #decode response
    if response[:3] == b'ERR':
        print("at line [" + str(i+1) + "] [" + line[:len(line)-1] + "]==> "  + response.decode())
        break
    elif response[:3] == b'LOG':
        print(response.decode())
    elif response == b'ok\r':
        print("line[" + str(i+1) + "] wrote to flash: [" + line[:len(line)-1] + "]")
        i += 1    
    elif response == b'':
        #if MCU failed to respond exit
        print("No rsponse from bootloader.")
        break;

hexFile.close()
ser.close()


