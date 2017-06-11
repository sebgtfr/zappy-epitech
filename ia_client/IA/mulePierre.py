#!/usr/bin/python3
## mulePierre.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Sun Jun 26 23:39:16 2016 stephane karraz
## Last update Sun Jun 26 23:39:23 2016 stephane karraz
##


from random import *
import time

def init_list(player, List):
        List.append(("linemate", player.search_object("linemate")))
        List.append(("deraumere", player.search_object("deraumere")))
        List.append(("sibur", player.search_object("sibur")))
        List.append(("mendiane", player.search_object("mendiane")))
        List.append(("phiras", player.search_object("phiras")))
        List.append(("thystame", player.search_object("thystame")))

def level1(player):
        List = []
        player.see_objects()
        init_list(player, List)

        while (player.ressources["nourriture"] < 15 and player.dead == False):
                player.see_objects()
                coor = player.search_object("nourriture")
                if (coor[0] != -1):
                        player.walk_to_case(coor[0], coor[1])
                        player.get_object("nourriture")
                else:
                        r = randint(0, 1)
                        if (r == 0):
                                player.turn_left()
                        if (r == 1):
                                player.turn_right()
                        player.walk()
                player.get_inventory()

        player.get_inventory()
        while (player.ressources["nourriture"] > 10 and player.get_nb_pierres_inv() < 3 and player.dead == False):
                player.see_objects()
                newList = []
                for maillon in List:
                        tmp = maillon
                        newList.append((tmp[0], player.search_object(tmp[0])))
                List = newList
                res = player.find_smaller(List)
                if (res[1][0] != -1):
                        player.walk_to_case(res[1][0], res[1][1])
                        if (player.cli.broad["BIP_BIP"] != 0 and player.cli.broad["GENKIDAMA"] != 0
                            and player.cli.broad["TAKE_MY_ENERGY"] != 0):
                                player.get_object(res[0])
                        else:
                                player.walk()

                else:
                        r = randint(0, 1)
                        if (r == 0):
                                player.turn_left()
                                player.walk()
                        if (r == 1):
                                player.turn_right()
                                player.walk()
                        player.walk()
                player.get_inventory()
                
        player.get_inventory()
        player.see_objects()
        while (player.ressources["nourriture"] > 2 and player.get_nb_pierres_inv() > 0
               and player.dead == False):
                if (player.cli.broad["BIP_BIP"] > 0):
                        player.go_to_broadPos("BIP_BIP")
                if (player.cli.broad["BIP_BIP"] == 0):
                        for obj in List:
                                player.get_inventory()
                                while (player.ressources[obj[0]] > 0 and player.dead == False):
                                        player.drop_object(str(obj[0]))
                                        player.get_inventory()
                        player.get_inventory()
                player.get_inventory()
