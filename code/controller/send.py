#!coding=utf-8
 
import socket
import os
import sys
import struct

def socket_client():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(('127.0.0.1', 9001))
    except socket.error as msg:
        print (msg)
        sys.exit(1)
    print (s.recv(1024))

    # ��Ҫ������ļ�·��
    # filepath = 'map/test.png'
    
    filepath = sys.argv[1]
    # �ж��Ƿ�Ϊ�ļ�
    if os.path.isfile(filepath):
        # ���嶨���ļ���Ϣ��128s��ʾ�ļ���Ϊ128bytes����l��ʾһ��int��log�ļ����ͣ��ڴ�Ϊ�ļ���С
        fileinfo_size = struct.calcsize('128sl')
        # �����ļ�ͷ��Ϣ�������ļ������ļ���С
        fhead = struct.pack('128sl', os.path.basename(filepath).encode('utf-8'), os.stat(filepath).st_size)
        # �����ļ��������ļ���С
        s.send(fhead)
        
        # �������ļ��Զ����Ƶ���ʽ�ֶ���ϴ���������
        fp = open(filepath, 'rb')
        while 1:
            data = fp.read(1024)
            if not data:
                print ('{0} file send over...'.format(os.path.basename(filepath)))
                break
            s.send(data)
        # �رյ��ڵ��׽��ֶ���
        s.close()
        
if __name__ == '__main__':
    socket_client()
