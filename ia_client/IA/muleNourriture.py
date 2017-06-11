#!/usr/bin/python3
## muleNourriture.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Sun Jun 26 23:39:56 2016 stephane karraz
## Last update Sun Jun 26 23:39:59 2016 stephane karraz
##

from random import *
import time

def level1(player):
    player.get_inventory()
    while (player.dead == False and player.cli.dead == False
           and player.cli.connected == True
           and player.ressources["nourriture"] < 50):
        player.see_objects()
        player.get_inventory()
        coor = player.search_object("nourriture")
        if (coor[0] != -1):
            player.walk_to_case(coor[0], coor[1])
            player.get_object("nourriture")
            player.get_inventory()
        else:
            r = randint(0, 1)
            player.walk()
            if (r == 0):
                player.turn_left()
            elif (r == 1):
                player.turn_right()
            player.walk()
            
    if (player.dead == False and player.cli.dead == False
        and player.cli.connected == True and player.cli.broad["BIP_BIP"] != -1):
        if (player.cli.broad["BIP_BIP"] == 0 and player.dead == False):
            while (player.ressources["nourriture"] > 8 and player.dead == False):
                player.get_inventory()
                player.drop_object("nourriture")
                player.get_inventory()
        else:
            player.go_to_broadPos("BIP_BIP")

    player.get_inventory()
    while (player.dead == False and player.cli.dead == False
           and player.cli.connected == True and player.ressources["nourriture"] > 8
           and player.cli.broad["BIP_BIP"] != -1):
        if (player.cli.broad["BIP_BIP"] == 0 and player.dead == False):
            while (player.ressources["nourriture"] > 8 and player.dead == False):
                player.get_inventory()
                player.drop_object("nourriture")
                player.get_inventory()
            else:
                player.go_to_broadPos("BIP_BIP")
                player.get_inventory()
