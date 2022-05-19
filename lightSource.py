"""Lightsource Class
251049748
Jacob Yoon
CS3388 Assignment 3
"""

import numpy as np
from matrix import matrix

class lightSource:
    def __init__(self, position =matrix(np.zeros((4, 1))), color =(0, 0, 0), intensity =(1.0, 1.0, 1.0)):
        self.__position =position
        self.__color =color
        self.__intensity =intensity
        
    def getPosition(self): #This is a getter function for the position of the light source
        return self.__position
    
    def getColor(self): #This is a getter function for the color of the loght source as an RGB value
        return self.__color
    
    def getIntensity(self): #This is getter function for the intensity of the given light source
        return self.__intensity
    
    def setIntensity(self, intensity):  #this is a setter function for the intensity
        self.__intensity =intensity
        
    def setColor(self, color):  #this is a setter function for the color in RGB values
        self.__color =color
        
    def setPosition(self, position):    #This is a setter for the position of the light source
        self.__position =position
        