import sys
import socket

HOST = "127.0.0.1"
PORT = 7979

message = "0,0,0"   # default
if len(sys.argv) == 2: message = sys.argv[1] # 1 is the first, 0 is app itself

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(message, (HOST, PORT))
print "UDP message (" + message + ") sent to " + HOST + ":" + str(PORT)
sock.close()

