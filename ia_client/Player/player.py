#!/usr/bin/python3
## player.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy/ia_client
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Tue Jun  7 21:57:27 2016 stephane karraz
## Last update Sun Jun 26 23:31:13 2016 stephane karraz
##

from threading import Thread
import sys
import time
import Sockets.Sockets as sock
import importlib

def add_vision_rows(vision):
    for j in range(9):
        vision.append([])
        size = len(vision) - 1
        for i in range(1 + (size * 2)):
            vision[size].append("")
        

class Player(Thread):

    def __init__(self, team_name, ip, port, graphic, freq, role):
        Thread.__init__(self)
        self.freq = freq
        self.max_x = 1
        self.max_y = 1
        self.role = role
        self.connect_nbr = 0
        self.level = 1
        self.name = team_name
        self.vision = []
        add_vision_rows(self.vision)
        self.last_resp = ""
        self.last_broadcast = ""
        self.ressources = {}
        self.ressources["nourriture"] = 0
        self.ressources["linemate"] = 0
        self.ressources["deraumere"] = 0
        self.ressources["sibur"] = 0
        self.ressources["mendiane"] = 0
        self.ressources["phiras"] = 0
        self.ressources["thystame"] = 0
        self.List_lvl = []
        self.cli = sock.client(ip, port)
        self.cli.try_connect()
        try:
            script = "IA." + role
            ia = importlib.import_module(script)
            self.ia = ia
        except:
            sys.stderr.write("Can't load " + role + " script\n")
            sys.exit(1)
        if (graphic == True):
            try:
                import Graphic.graphic as gr
            except:
                sys.stderr.write("Error: Pygame (1.9.2) not found.\n")
                sys.exit(1)
            self.graphic = True
            self.wind = gr.window()
            self.wind.start()
        else:
            self.graphic = False
        self.dead = False
            
    def get_msg(self):
        try:
            with self.cli.mutex:
                self.last_resp = self.cli.msgs.pop(0)
                if (self.last_resp == "elevation en cours\n"):
                    self.lvl = 0
                    self.last_resp = ""
                if (self.last_resp == ""):
                    time.sleep(self.freq)
        except:
            if (self.last_resp != "elevation en cours\n"):
                self.last_resp = ""
        time.sleep(self.freq)
        
        
    def read_dimensions(self, msg):
        j = 0
        self.max_x = -1
        self.max_y = -1
        for i in range(len(msg)):
            if (msg[i] == ' ' or msg[i] == '\n'):
                if (self.max_x == -1):
                    self.max_x = int(msg[j:i])
#                    sys.stderr.write ("max x = " + str(self.max_x) + "\n")
                else:
                    self.max_y = int(msg[j:i])
#                    sys.stderr.write ("max y = " + str(self.max_y) + "\n")
                j = i

    def get_object(self, obj):
        cpt = 0
        self.cli.send_msg("prend " + obj + "\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Fall")

    def drop_object(self, obj):
        cpt = 0
        self.cli.send_msg("pose " + obj + "\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Fall")

    def get_inventory(self):
        self.cli.send_msg("inventaire\n")
        msg = ""
        cpt = 0
        self.get_msg()
        while (msg == "" and cpt < 15):
            if (self.last_resp != "" and self.last_resp[0] == '{'
                and self.last_resp.find("joueur") == -1 and cpt < 15):
                msg = self.last_resp[1:-2]
            self.get_msg()
            cpt+=1
        if (msg == ""):
            return (0)
        if (self.cli.dead == True):
            return (0)
        
        list_obj = msg.split(",")
        for obj in list_obj:
            material = obj.strip().split(" ")[0]
            nb = obj.strip().split(" ")[1]
            try:
                self.ressources[material] = int(nb)
            except:
                self.ressources[material] = 0
        self.set_anim("Idle")
        
    def see_objects(self):
        self.cli.send_msg("voir\n")
        cpt = 0
        msg = ""
        self.get_msg()
        while (msg == "" and cpt < 15):
            if (self.last_resp != "" and self.last_resp[0] == '{'
                and self.last_resp.find("joueur") != -1):
                msg = self.last_resp[1:-2]
            self.get_msg()
            cpt += 1
        if (self.cli.dead == True):
            return (0)
        if (msg == "" or msg.find("joueur") == -1):
            return (0)
        idx = 0
        pos = 0
        
        list_obj = msg.split(",")
        for obj in list_obj:
            self.vision[idx][pos] = obj.strip()
            pos += 1
            if (pos >= (len(self.vision[idx]))):
                pos = 0
                idx += 1            
        self.set_anim("Idle")
        
    def launch_elevation(self):
        cpt = 0
        self.cli.send_msg("incantation\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Jump")
        
    def slot_open(self):
        cpt = 0
        self.cli.send_msg("connect_nbr\n")
        self.get_msg()
        while (self.last_resp != "" and self.cli.dead != True and cpt < 15):
            cpt += 1
            self.get_msg()
            try:
                int(self.last_resp)
                self.connect_nbr = int(self.last_resp)
                return (0)
            except:
                pass
            
    def egg_fork(self):
        cpt = 0
        self.cli.send_msg("fork\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Slide")

    def broadcast(self, text):
        cpt = 0
        self.cli.send_msg("broadcast " + text + "\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Idle")
        
    def expulse_players(self):
        cpt = 0
        self.cli.send_msg("expulse\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Run")
            
    def turn_right(self):
        cpt = 0
        self.cli.send_msg("droite\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Walk")
            
    def turn_left(self):
        cpt = 0
        self.cli.send_msg("gauche\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Idle")
            
    def walk(self):
        cpt = 0
        self.cli.send_msg("avance\n")
        self.get_msg()
        while (self.last_resp == "" and self.cli.dead == False and cpt < 15):
            cpt += 1
            self.get_msg()
        self.set_anim("Walk")
        
    def set_anim(self, anim):
        if self.graphic:
            self.wind.set_anim(anim)

    def run(self):
        self.launch()
        while (self.cli.dead == False and self.dead == False and self.cli.connected == True):
            if (self.cli.lvl == 1):
                self.ia.level1(self)
            elif (self.cli.lvl == 2):
                self.ia.level2(self)
            elif (self.cli.lvl == 3):
                self.ia.level3(self)
            elif (self.cli.lvl == 4):
                self.ia.level4(self)
            elif (self.cli.lvl == 5):
                self.ia.level5(self)
            elif (self.cli.lvl == 6):
                self.ia.level6(self)
            elif (self.cli.lvl == 7):
                self.ia.level7(self)
            elif (self.cli.lvl == 8):
                self.ia.level8(self)
        self.set_anim("Dead")
                
    def launch(self):
        if (self.cli.connected == False):
            sys.stderr.write("Error: Can't connect to server.\n")
            self.cli.dead = True
            self.cli.connected = False
            self.dead = True
            sys.exit(1)
        buff = self.cli.get_msg()
        if (buff != "BIENVENUE\n"):
            self.cli.dead = True
            self.dead = True
            sys.exit(1)
        self.cli.send_msg(self.name + "\n")
        buff = self.cli.get_msg()
        if (buff == "ko\n"):
#            sys.stderr.write("Error: No slot avaible or bad team name.\n")
            self.cli.dead = True
            self.dead = True
            sys.exit(1)
        self.read_dimensions(self.cli.get_msg())
        self.cli.start()
        self.dead = False

    def walk_to_case(self, i, j):
        if (self.dead == True):
            return (0)
        mid = i
        while (i > 0):
            self.walk()
            i -= 1
        if (j > mid):
            self.turn_left()
            while (j >= mid):
                self.walk()
                j -= 1
        else:
            self.turn_right()
            while (j <= mid):
                self.walk()
                j += 1


    def search_object(self, obj):
        for i in range(0, len(self.vision)):
            j = 0
            while ((i - j) >= 0 and (i + j) < len(self.vision[i])):
                if (self.vision[i][i + j].count(obj) > 0):
                    return ((i, i + j))
                if (self.vision[i][i - j].count(obj) > 0):
                    return ((i, i - j))
                j += 1
                
        return ((-1, -1))

    def compare(self, res, coor):
        if (res[1][0] < coor[1][0]):
            return (False)
        elif (res[1][0] > coor[1][0]):
            return (True)
        elif (res[1][0] == coor[1][0]):
            if ((abs(res[1][0] - res[1][1])) < (abs(coor[1][0] - coor[1][1]))):
                return (False)
            else:
                return (True)
            
    def find_smaller(self, List):
        res = ("", (-1, -1))
        for coor in List:
            if (coor[1][0] != -1):
                if (res[1][0] == -1):
                    res = coor
                elif (self.compare(res, coor) == True):
                    res = coor
        return (res)

    def get_nb_pierres_inv(self):
        return (self.ressources["linemate"] + 
                self.ressources["deraumere"] + 
                self.ressources["sibur"] +
                self.ressources["mendiane"] +
                self.ressources["phiras"] +
                self.ressources["thystame"])
    
    def get_nb_pierres_sol(self):
        return (1 + self.vision[0][0].count(" ") - (self.vision[0][0].count("joueur") + self.vision[0][0].count("nourriture")))
    
    def go_to_broadPos(self, key):
        if (self.dead == False):
            if (key == ""):
                dest = self.cli.broadPos
                with self.cli.mutex:
                    self.cli.broadPos = -1
            else:
                dest = self.cli.broad[key]
                with self.cli.mutex:
                    self.cli.broad[key] = -1
            if (dest > 0):
                if (dest == 1):
                    self.walk()
                elif (dest == 2):
                    self.walk()
                    self.turn_left()
                    self.walk()
                elif (dest == 3):
                    self.turn_left()
                    self.walk()
                elif (dest == 4):
                    self.turn_left()
                    self.walk()
                    self.turn_left()
                    self.walk()
                elif (dest == 5):
                    self.turn_left()
                    self.turn_left()
                    self.walk()
                elif (dest == 6):
                    self.turn_right()
                    self.walk()
                    self.turn_right()
                    self.walk()
                elif (dest == 7):
                    self.turn_right()
                    self.walk()
                elif (dest == 8):
                    self.walk()
                    self.turn_right()
                    self.walk()
                    
            # elif (dest == 5):
            #     self.turn_right()
            #     self.turn_right()
            #     self.walk()
