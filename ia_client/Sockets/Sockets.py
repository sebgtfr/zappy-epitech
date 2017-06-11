#!/usr/bin/env python3.3
## Sockets.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy/ia_client
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Tue Jun  7 21:57:34 2016 stephane karraz
## Last update Sun Jun 26 21:36:38 2016 stephane karraz
##

from threading import Thread, Lock
import sys
import socket

class client(Thread):

    def __init__(self, ip, port):
        Thread.__init__(self)
        self.lvl = 1
        self.msg = ""
        self.broadcast = ""
        self.broadPos = -1
        self.broadMsg = ""
        self.port = port
        self.ip = ip
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connected = False
        self.mutex = Lock()
        self.dead = False
        self.broad = {}
        self.broad["GENKIDAMA"] = -1
        self.broad["BIP_BIP"] = -1
        self.broad["TAKE_MY_ENERGY"] = -1
        self.broad["Ennemy"] = -1
        self.broadArg = {}
        self.broadArg["GENKIDAMA"] = ""
        self.broadArg["BIP_BIP"] = ""
        self.broadArg["TAKE_MY_ENERGY"] = ""
        
    def try_connect(self):
        try:
            self.sock.connect((self.ip, self.port))
            self.connected = True
        except Exception as e:
#            sys.stderr.write ("Connexion error: {0}".format(e) + "\n")
            return (False)
        return (True)

    def send_msg(self, message):
        if self.connected == True and self.dead == False:
            try:
                self.sock.sendall(message.encode(encoding='utf-8'))
            except Exception as e:
#                sys.stderr.write ("Message error: {0}".format(e) + "\n")
                self.close_connect()
        else:
            self.close_connect()
                
    def close_connect(self):
        self.connected = False
        self.dead = True
        try:
            self.sock.close()
        except:
            pass
        
    def get_msg(self):
        try:
            buff = ""
            if self.connected == True and self.dead == False:
                buff += self.sock.recv(1).decode("utf-8")
                while (buff[-1] != '\n'):
                    buff += self.sock.recv(1).decode("utf-8")
        except Exception as e:
#            sys.stderr.write ("Recv error: {0}".format(e) + "\n")
            self.close_connect()
        return buff

    def parse_broadcast(self, tmp):
        self.broadcast = tmp
        space = tmp.find(" ") + 1
        self.broadPos = int(tmp[space:(space + 1)])
        self.broadMsg = str(tmp[(space + 2):-1])
        idx = self.broadMsg.find(" ")
        if idx != -1:
            key = self.broadMsg[0:(idx)]
        else:
            key = self.broadMsg
        if (self.broad.get(key, "") != ""):
            self.broad[key] = self.broadPos
            if (idx != -1):
                sp = self.broadMsg.split()
                self.broadArg[key] = sp[1]
        elif (self.broadMsg != "FOOOOOOOOOOOOD" and self.broadMsg != "I M COMIIIING"
              and self.broadMsg != "Kaaaameha MEEEEHAAAAA"):
            self.broad["Ennemy"] = self.broadPos
            
    def run(self):
        try:
            self.broadcast = ""
            tmp = ""
            self.msgs = []
            while (self.dead == False and self.connected == True):
                tmp = self.get_msg()
                with self.mutex:
                    if (tmp.count("message ") > 0):
                        self.parse_broadcast(tmp)
                    elif (tmp[0:7] == "niveau "):
                        nb = tmp[16:-1]
                        self.lvl = int(nb)
                        print ("level : " + str(self.lvl))
                    elif (tmp == "mort\n"):
                        self.dead = True
                    else:
                        self.msgs.append(tmp)
        except:
            self.dead = True

