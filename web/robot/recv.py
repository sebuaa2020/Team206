#!coding=utf-8

import threading
import socket
import struct

def socket_service():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # �󶨶˿�Ϊ9001
        s.bind(('127.0.0.1', 9001))
        # ���ü�����
        s.listen(10)
    except socket.error as msg:
        print (msg)
        sys.exit(1)
    print ('Waiting connection...')
 
    # �ȴ����󲢽���(�����ͣ������һ���յ��������󼴿����������ݵ��߳�)
    conn, addr = s.accept()
    # ��������
    t = threading.Thread(target=deal_data, args=(conn, addr))
    t.start()
 
def deal_data(conn, addr):
    print ('Accept new connection from {0}'.format(addr))
    # conn.settimeout(500)
    # �յ������Ļظ�
    conn.send('Hi, Welcome to the server!'.encode('utf-8'))
 
    # ������ͬ��С�Ŀռ��ŷ��͹������ļ������ļ���С��Ϣ
    fileinfo_size = struct.calcsize('128sl')
    # �����ļ������ļ���С��Ϣ
    buf = conn.recv(fileinfo_size)
    # �ж��Ƿ���յ��ļ�ͷ��Ϣ
    if buf:
        # ��ȡ�ļ������ļ���С
        filename, filesize = struct.unpack('128sl', buf)
        fn = filename.strip(b'\00')
        fn = fn.decode()
        print ('file new name is {0}, filesize is {1}'.format(str(fn),filesize))

        recvd_size = 0  # �����ѽ����ļ��Ĵ�С
        # �洢�ڸýű�����Ŀ¼����
        fp = open('map/' + str(fn), 'wb')
        print ('start receiving...')
        
        # �������δ���Ķ�����������д�뵽�ļ�
        while not recvd_size == filesize:
            if filesize - recvd_size > 1024:
                data = conn.recv(1024)
                recvd_size += len(data)
            else:
                data = conn.recv(filesize - recvd_size)
                recvd_size = filesize
            fp.write(data)
        fp.close()
        print ('end receive...')
    # ��������Ͽ�����
    conn.close()
        
if __name__ == "__main__":
    socket_service()
