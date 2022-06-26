import socket
import serial

sock=socket.socket()
sock.bind(('input your IP adress'), #input port 1023-65535
          )
sock.listen(1)
while True:
    conn,addr=sock.accept()
    data=conn.recv(1024)
    if not data:
        break
    ser=serial.Serial('input your COM port', 9600, timeout=1)
    ser.flush()
    ser.write(data)
    temp=""
    while temp=="":
        if ser.in_waiting > 0:
            temp=ser.readline()
            conn.send(temp)
