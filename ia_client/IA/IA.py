#!/usr/bin/python3
## IA.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Sun Jun 26 23:39:34 2016 stephane karraz
## Last update Sun Jun 26 23:39:39 2016 stephane karraz
##


from random import *
import time

def level1(player):
    if (player.last_resp == "elevation en cours\n"):
        player.set_anim("Jump")
    else:
        player.launch_elevation()
        if (player.last_resp == "elevation en cours\n"):
            player.set_anim("Jump")
        else:
            player.walk()
            player.see_objects()
            coor = player.search_object("linemate")
            if (coor[0] != -1):
                player.walk_to_case(coor[0], coor[1])
                player.get_object("linemate")
                player.get_inventory()
            while (player.ressources["nourriture"] < 20 and player.dead == False):
                player.see_objects()
                coor = player.search_object("nourriture")
                if (coor[0] != -1):
                        player.walk_to_case(coor[0], coor[1])
                        player.get_object("nourriture")
                        player.get_inventory()
                else:
                        r = randint(0, 1)
                        if (r == 0):
                                player.turn_left()
                        if (r == 1):
                                player.turn_right()
                        player.walk()
            player.drop_object("linemate")

def find_smaller(List):
        res = ("", -1, -1)
        for coor in List:
                if (coor[0] != -1):
                    if (res == ("", -1, -1)):
                        res = coor
                    elif (compare(res, coor) == True):
                        res = coor
                    return (res)

def level2(player):
    if (player.last_resp == "elevation en cours\n"):
        player.set_anim("Jump")
        print ("test")
    else:
        player.launch_elevation()
        if (player.last_resp == "elevation en cours\n"):
            player.set_anim("Jump")
        else:
            print (player.last_resp)
            player.walk()
            player.see_objects()

            List = []
            # Element[0] = nom_ressource
            # Element[1] = coor[0], coor[1]
            List.append(("linemate", player.search_object("linemate")))
            List.append(("deraumere", player.search_object("deraumere")))
            List.append(("sibur", player.search_object("sibur")))
            res = find_smaller(List)

            player.walk_to_case(res[1][0], res[1][1])
            player.get_object(res[0])
            print (player.ressources["linemate"])
            print (player.ressources["deraumere"])
            print (player.ressources["sibur"])


            # else:
            #     search_object(player, "nourriture")                

            # food = player.ressources([nourriture])
            # msg = "OK "
            # print (msg)
            # print (food)
            
            player.search_object("nourriture")
            player.search_object("deraumere")
            player.search_object("sibur")
            
            # if (player.ressources("linemere") == 1 && player.ressources("sibur") == 1 && player.ressources("deraumere") == 1):
            #     food = player.ressources("nourriture")
            #     msg = "OK " + food
            #     print (msg)
            #     player.send_msg("broadcast " + msg + "\n")
                
