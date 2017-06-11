#!/usr/bin/python3

from random import *
import time

def level1(player):
    while (player.dead == False):
        player.send_msg("broadcast " + "BIP BIP" + "\n")
        if (player.ressources["nourriture"] < 5)
                player.get_object("nourriture")
