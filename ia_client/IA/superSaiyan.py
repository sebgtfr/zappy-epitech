#!/usr/bin/python3
## superSaiyan.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Sun Jun 26 23:38:10 2016 stephane karraz
## Last update Sun Jun 26 23:38:20 2016 stephane karraz
##


from random import *
import time

def create_list_pierre(List):
        List.append("linemate")
        List.append("deraumere")
        List.append("sibur")
        List.append("mendiane")
        List.append("phiras")
        List.append("thystame")

def clean_case(player):
        List = []
        player.see_objects()
        create_list_pierre(List)

        for obj in List:
                cpt = player.vision[0][0].count(obj)
                while (cpt > 0 and player.dead == False):
                        player.get_object(obj)
                        cpt -= 1
                        

def create_list_level(List_lvl, l, d, s, m, p, t):
        List = []
        List.append(("linemate", l))
        List.append(("deraumere", d))
        List.append(("sibur", s))
        List.append(("mendiane", m))
        List.append(("phiras", p))
        List.append(("thystame", t))
        return (List)
        
def deposit_pierre(player):

        for obj in player.List_lvl:
                if (obj[1] > 0):
                        player.drop_object(obj[0])

def send_elevation_signal(player, level_to_rush, required_player):
        tried = False
        nb = 1
        level = level_to_rush
        if (player.cli.lvl > 1):
                player.broadcast("GENKIDAMA " + str(level_to_rush) + "_" + str(nb))
        while (player.dead == False and player.cli.lvl < level_to_rush
               and tried == False and player.ressources["nourriture"] > 5):
                if (nb == required_player):
                        player.launch_elevation()                                        
                        tried = True
                if (player.dead == False and player.cli.broad["TAKE_MY_ENERGY"] > 0):
                        with player.cli.mutex:
                                parts = player.cli.broadArg["TAKE_MY_ENERGY"].split()
                                if (len(parts) > 1):
                                        args = parts[1].split("_")
                                        if (len(args) > 1):
                                                if (int(args[1]) == level_to_rush):
                                                        nb += 1
                                player.cli.broadArg["TAKE_MY_ENERGY"] = ""
                                player.cli.broad["TAKE_MY_ENERGY"] = -1
                if (player.dead == False):
                        player.broadcast("GENKIDAMA " + str(level_to_rush) + "_" + str(nb))
                player.get_inventory()

def list_pierres_by_level(player):
        if (player.cli.lvl == 1):
                player.List_lvl = create_list_level(player.List_lvl, 1, 0, 0, 0, 0, 0)
        elif (player.cli.lvl == 2):
                player.List_lvl = create_list_level(player.List_lvl, 1, 1, 1, 0, 0, 0)
        elif (player.cli.lvl == 3):
                player.List_lvl = create_list_level(player.List_lvl, 2, 0, 1, 0, 2, 0)
        elif (player.cli.lvl == 4):
                player.List_lvl = create_list_level(player.List_lvl, 1, 1, 2, 1, 0, 0)
        elif (player.cli.lvl == 5):
                player.List_lvl = create_list_level(player.List_lvl, 1, 1, 2, 0, 1, 0)
        elif (player.cli.lvl == 6):
                player.List_lvl = create_list_level(player.List_lvl, 1, 2, 1, 3, 0, 0)
        elif (player.cli.lvl == 7):
                player.List_lvl = create_list_level(player.List_lvl, 2, 2, 2, 2, 2, 1)

                
def run_for_elevation(player, my_level, nb_player_required):

# Deplacement
# Analyser son emplacement
# Si pierres presentes sur case 0, toutes les ramasser
# Sinon poser la pierre requise pour le niveau
# Envoyer un signal avec le niveau a atteindre
# Attendre la reponse d un autre joueur
# Debuter l elevation

        player.walk()
        clean_case(player)
        deposit_pierre(player)
        send_elevation_signal(player, my_level+1, nb_player_required)

def get_pierre(player, obj, nb_res_minim):
        if (player.ressources[obj] < nb_res_minim and player.dead == False):
                player.get_object(obj)
                player.get_inventory()
        
        
def case_du_radar(player):

        x = 2
        y = 7

        # Nombre requis pour passer tous les niveaux
        nb_linemate = 9
        nb_sibur = 10
        nb_deraumere = 8
        nb_mendiane = 5
        nb_phiras = 6
        nb_thystame = 1   

        my_level = player.cli.lvl
        if (my_level == 1):
                nb_player_required = 1
        elif (my_level == 2 or my_level == 3):
                nb_player_required = 2
        elif (my_level == 4 or my_level == 5):
                nb_player_required = 4
        elif (my_level == 6 or my_level == 7):
                nb_player_required = 6

        nb_player = 0
        player.see_objects()
        case_0 = player.vision[0][0]
        nb_player = case_0.count("joueur")
        
        player.get_inventory()
        cpt = 0
        while (player.ressources["nourriture"] < y * 2 and cpt < y  and player.dead == False
               and player.cli.dead == False
               and player.cli.connected == True):
                player.get_object("nourriture")
                player.get_inventory()
                cpt += 1
        player.get_inventory()
        for obj in player.List_lvl:
                cpt = player.ressources[obj[0]]
                while (cpt > obj[1]):
                        player.drop_object(obj[0])
                        cpt-=1
        player.get_inventory()
        while (player.ressources["nourriture"] > y and player.dead == False):
                player.see_objects()
                if (player.ressources["linemate"] >= player.List_lvl[0][1]
                    and player.ressources["sibur"] >= player.List_lvl[1][1]
                    and player.ressources["deraumere"] >= player.List_lvl[2][1]
                    and player.ressources["mendiane"] >= player.List_lvl[3][1]
                    and player.ressources["phiras"] >= player.List_lvl[4][1]
                    and player.ressources["thystame"] >= player.List_lvl[5][1]
                    and player.dead == False):
                        if (player.cli.broad["GENKIDAMA"] > -1 and player.dead == False):
                                sent_msg = False
                                while (player.cli.broad["GENKIDAMA"] == 0 and player.dead == False):
                                        if (int(player.cli.broadArg["GENKIDAMA"].split("_")[0]) != player.cli.lvl + 1
                                            and int(player.cli.broadArg["GENKIDAMA"].split("_")[1]) < nb_player_required):
                                                if (sent_msg == False):
                                                        player.broadcast("TAKE_MY_ENERGY " + str(my_level + 1) + "_" + str(nb_player))
                                                        sent_msg = True
                                                if (int(player.cli.broadArg["GENKIDAMA"].split("_")[1]) >= nb_player_required):
                                                        player.launch_elevation()
                                else:
                                        if (player.dead == False):
                                                player.go_to_broadPos("GENKIDAMA")
                                                with player.cli.mutex:
                                                        player.cli.broad["GENKIDAMA"] = -1
                                                
                        elif (player.dead == False):
                                run_for_elevation(player, my_level+1, nb_player_required)
                                
                elif (player.dead == False):
                        player.get_inventory()
                        if (player.vision[0][0].count("linemate") > 0 and player.ressources["linemate"] < player.List_lvl[0][1]):
                                get_pierre(player, "linemate", nb_linemate)
                        if (player.vision[0][0].count("sibur") > 0 and player.ressources["sibur"] < player.List_lvl[1][1]):
                                get_pierre(player, "sibur", nb_sibur)
                        if (player.vision[0][0].count("deraumere") > 0 and player.ressources["deraumere"] < player.List_lvl[2][1]):
                                get_pierre(player, "deraumere", nb_deraumere)
                        if (player.vision[0][0].count("mendiane") > 0 and player.ressources["mendiane"] < player.List_lvl[3][1]):
                                get_pierre(player, "mendiane", nb_mendiane)
                        if (player.vision[0][0].count("phiras") > 0 and player.ressources["phiras"] < player.List_lvl[4][1]):
                                get_pierre(player, "phiras", nb_phiras)
                        if (player.vision[0][0].count("thysame") > 0 and player.ressources["thysame"] < player.List_lvl[5][1]):
                                get_pierre(player, "thysame", nb_thystame)
                player.get_inventory()
        

def level1(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 1):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                                
def level2(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 2):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                        
def level3(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 3):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                        
def level4(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 4):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                        
def level5(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 5):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                        
def level6(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 6):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                        
def level7(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 7):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")
                        
def level8(player):
        list_pierres_by_level(player)
        while (player.dead == False and player.cli.dead == False
               and player.cli.connected == True and player.cli.lvl == 8):
                if (player.dead == False and player.cli.broad["BIP_BIP"] != -1):
                        if (player.cli.broad["BIP_BIP"] == 0):
                                case_du_radar(player)
                else:
                        player.go_to_broadPos("BIP_BIP")

