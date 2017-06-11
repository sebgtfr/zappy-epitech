#!/usr/bin/python3
## guerrier.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Sun Jun 26 23:40:25 2016 stephane karraz
## Last update Sun Jun 26 23:40:30 2016 stephane karraz
##

from random import *
import time

def level1(player):
    player.get_inventory()
    player.broadcast("FOOOOOOOOOOOOD")
    
    while (player.ressources["nourriture"] < 15 and player.cli.dead == False
           and player.cli.connected == True and player.dead == False):
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
        if (player.cli.broad["Ennemy"] == 0):
            player.expulse_players()
        player.get_inventory()

    player.broadcast("I M COMIIIING")
    while (player.ressources["nourriture"] > 5 and player.cli.dead == False
           and player.cli.connected == True and player.dead == False):
        if (player.cli.broad["Ennemy"] == 0):
            player.expulse_players()
            with self.cli.mutex:
                player.cli.broad["Ennemy"] = -1
            player.broadcast("Kaaaameha MEEEEHAAAAA")
            print ("Kaaaameha MEEEEHAAAAA")
        elif (player.cli.broad["Ennemy"] > 0):
            player.go_to_broadPos("Ennemy")
        else:
            r = randint(0, 1)
            if (r == 0):
                player.turn_left()
            if (r == 1):
                player.turn_right()
            player.walk()
            
        player.get_inventory()
                
