#!/usr/bin/python3
## graphic.py for zappy in /home/karraz_s/rendu/PSU_2015_zappy/ia_client
## 
## Made by stephane karraz
## Login   <karraz_s@epitech.net>
## 
## Started on  Mon Jun 20 22:22:13 2016 stephane karraz
## Last update Tue Jun 21 01:06:54 2016 stephane karraz
##

from threading import Thread
import pygame, sys, time

def load_anim(List, name):
    for i in range(1, 9):
        List.append(pygame.image.load("Sprites/" + name + "_(" + str(i) + ").png"))

class window(Thread):
    def __init__(self):
        self.initState = False
        try:
            Thread.__init__(self)
            pygame.init()
        
            self.fond = pygame.transform.flip(pygame.image.load("Wallpaper/fond.png"), 1, 0)
            self.screen = pygame.display.set_mode((250, 250))
            self.dict_anim = {}
            self.dict_anim["Walk"] = []
            self.dict_anim["Idle"] = []
            self.dict_anim["Dead"] = []
            self.dict_anim["Fall"] = []
            self.dict_anim["Jump"] = []
            self.dict_anim["Run"] = []
            self.dict_anim["Slide"] = []
            
            load_anim(self.dict_anim["Walk"], "Walk")
            load_anim(self.dict_anim["Idle"], "Idle")
            load_anim(self.dict_anim["Dead"], "Dead")
            load_anim(self.dict_anim["Fall"], "Fall")
            load_anim(self.dict_anim["Jump"], "Jump")
            load_anim(self.dict_anim["Run"], "Run")
            load_anim(self.dict_anim["Slide"], "Slide")

            self.anim = self.dict_anim["Idle"]
            self.initState = True
        except:
            sys.stderr.write("Can't load pygame\n")

    def set_anim(self, state):
        self.anim = self.dict_anim[state]
            
    def run(self):
        i = 0
        while (self.initState):
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.initState = False
                if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                    self.initState = False
            self.screen.blit(self.fond , (0, 0))
            self.screen.blit(pygame.transform.scale(self.anim[i], (250, 250)), (0,0))
            pygame.display.flip()
            time.sleep(0.07)
            i = (i + 1) % 8
        pygame.display.quit()
        pygame.quit()
