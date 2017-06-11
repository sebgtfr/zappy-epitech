#!/usr/bin/python3
## pilierRadar.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Sun Jun 26 23:40:09 2016 stephane karraz
## Last update Sun Jun 26 23:40:12 2016 stephane karraz
##

from random import *
import time

def level1(player):
    while (player.dead == False and player.cli.dead == False
           and player.cli.connected == True):
        player.broadcast("BIP_BIP")
        player.get_inventory()
        if (player.ressources["nourriture"] < 10):
            player.get_object("nourriture")
            player.broadcast("BIP_BIP")
            player.egg_fork()
        player.see_objects()
        player.broadcast("BIP_BIP")
