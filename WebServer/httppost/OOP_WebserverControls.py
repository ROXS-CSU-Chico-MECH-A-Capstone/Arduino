# -*- coding: utf-8 -*-
"""
Created on Tue Mar 28 14:55:59 2023

@author: westj
"""
from robodk.robolink import *       # import the robolink library (bridge with RoboDK)
RDK = Robolink()   
from robodk.robomath import *   
import math
import numpy as np
import matplotlib.pyplot as plt 
import array
import pandas as pd
import requests
import re
from scipy.signal import find_peaks, peak_prominences, savgol_filter
from scipy.stats import linregress    
import requests 
import json



class Spiral:
    def __init__(self,x0:float,y0:float,points:float) -> None:
        self.x0=x0 #x offset
        self.y0=y0 #y offset
        self.points=points
        
    def build(self, radius:float, spacing:float):
        revs=radius/spacing            #calc number of revolutions
        k=spacing/(2*np.pi)                       
        theta=np.array(np.linspace(0,revs*2*np.pi,self.points)) #how many points and angle coord
        r=k * theta                       #radius coord
        x=(r*np.cos(theta)+self.x0)       #convert to x cartesian
        y=(r*np.sin(theta)+self.y0)       #convert to y cartesian
        return x, y 
    
    
class Webserver:
#webserver returns json string that looks like {"speed":25,"goalpos":140,"zCurrent":140.09935,"PRInt":4,"ledStatus":false,"zero":1}
    def __init__(self,IP,extenstion)->None:
        self.IP=IP #x offset
        self.ex=extenstion #y offset
        
        
    def patch(self, obj, value):
        url = "http://" + self.IP + "/" +self.ex #address of server
        obj=str(obj)
        
        payload = {obj: value} #rewrite the obj to value
        headers = {"Content-Type": "application/json"} #formatting the message as a json string don't change this

        response = requests.patch(url, data=json.dumps(payload), headers=headers) #patch in or change the value

        if response.status_code == 200: #if 204 which is http good patch
            print(obj + " Updated successfully")
        else:
            print(obj + " Error: ", response.status_code)
        return 
            
    def get(self, obj):
        url = "http://" + self.IP + "/" +self.ex #address of server
        obj=str(obj)
        
        response = requests.get(url)
        if response.status_code == 200:
            value=response.json()[obj]
            print(obj, value)
        elif response.status_code == 204:
            value=response.json()[obj]
            print(obj, value)
        else:
           print("Error: ", response.status_code)
        
        return value

IP="192.168.0.99"
ext="values"
ESP=Webserver(IP,ext)
#%%
ESP.get("zCurrent")
#%%
ESP.patch("speed","100")

z=ESP.get("zCurrent")
ESP.patch("goalpos",100)
#%%
ESP.get("PRInt")  
#%%
ESP.patch("ledStatus",True)
#%%
ESP.patch("ledStatus",False)
#%%
ESP.patch("zero",1) 
#%%
ESP.get("zCurrent")