import binascii
import serial
import time
ser = serial.Serial(
	port = "/dev/tty.usbmodemFD123",
	baudrate = 115200,
	bytesize = serial.EIGHTBITS,
	parity = serial.PARITY_NONE,
	stopbits = serial.STOPBITS_ONE,
	timeout = None
)
ser.flushInput()
ser.flushOutput()
try:
	ser.open()
except Exception, e:
	print "could not open serial port" + str(e)
else:
	pass
finally:
	pass
#Read whole file into data
#nf = open("newImage.jpg","wb")
#nf = open("newImage.jpg","wb")
opened = False
done = False
ready = False
start = False

while done == False:
    c = ser.readline()
    d = c.strip()
    #print(".")
    if d == "START":
    	print("found START\n")
    	timestr = time.strftime("%Y-%m-%d-%H_%M_%S")
        nf = open(timestr+".jpg","wb")
        start = True
        opened = True
    else:
    	if opened:
    		if d == "END":
    			print("found END\n")
    			nf.close()
    			opened = False
    			print("finished writing to file\n")
    if opened:
    	#print(start)
    	#print(d)
    	#print(binascii.a2b_hex)
    	if start:
    		start = False
    	else:
    		nf.write(binascii.a2b_hex(d))

# Close the file
nf.close()