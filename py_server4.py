import socket
import time
import cv2
import numpy


def ReceiveData():
    address = ('0.0.0.0', 7676)
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(address)
   
    s.listen(1)

    def recvall(sock, count):
        buf = b''  
        while count:
 
            newbuf = sock.recv(count)
            if not newbuf: return None
            buf += newbuf
            count -= len(newbuf)
        return buf

    conn, addr = s.accept()
    while 1:
        start = time.time()  
        b_length=recvall(conn,4)
        
        if b_length is not None:
            length=int.from_bytes(b_length,byteorder='little',signed=False)
            print(length)
            stringData = recvall(conn,length)  
            recv_time = time.time()
            with open("%s.jpg" % recv_time, "wb") as f:
                f.write(stringData)
 
    
    s.close()

if __name__ == '__main__':
    ReceiveData()
