# -*- coding: utf-8 -*-
"""
Created on Sat Mar 25 11:58:27 2023
@author: westj
"""

print('Hello World!')
#%% Get Value
    
import requests
url = "http://192.168.0.99/values" # Replace with the actual IP address of your ESP8266 module
response = requests.get(url)

if response.status_code == 200:
   speed = response.json()["speed"]
   goalpos = response.json()["goalpos"]
   print("Current speed: ", speed)
   print("Current goalpos: ", goalpos)
else:
   print("Error: ", response.status_code)
        
#%% Get Value
    
import requests
url = "http://192.168.0.99/values" # Replace with the actual IP address of your ESP8266 module
response = requests.get(url)

if response.status_code == 200:
   PRInt = response.json()["PRInt"]

   print("Int: ", PRInt)
else: 
   print("Error: ", response.status_code)
        
        
#%% Update Value
        
import requests 
import json

url = "http://192.168.0.99/values"# Replace with the actual IP address of your ESP8266 module

payload = {"speed":25,"goalpos":20}
headers = {"Content-Type": "application/json"}

response = requests.patch(url, data=json.dumps(payload), headers=headers)

if response.status_code == 200:
    print("Value updated successfully")
elif response.status_code == 204:
    print("Value updated successfully")
else:
    print("Error: ", response.status_code)
    
    #%% Update LED
            
    import requests 
    import json

    url = "http://192.168.0.99/values"# Replace with the actual IP address of your ESP8266 module

    payload = {"ledStatus": True} #use True or False
    headers = {"Content-Type": "application/json"}

    response = requests.patch(url, data=json.dumps(payload), headers=headers)

    if response.status_code == 200:
        print("Value updated successfully")
    elif response.status_code == 204:
        print("Value updated successfully")
    else:
        print("Error: ", response.status_code)
        
        
    #check
    response = requests.get(url)
    if response.status_code == 200:
       ledStatus = response.json()["ledStatus"]

       print("LED ", ledStatus)
    else:
       print("Error: ", response.status_code)
            
    #%% Zero
            
    import requests 
    import json

    url = "http://192.168.0.99/values"# Replace with the actual IP address of your ESP8266 module

    payload = {"zero": 1} #use True or False
    headers = {"Content-Type": "application/json"}

    response = requests.patch(url, data=json.dumps(payload), headers=headers)

    if response.status_code == 200:
        print("Value updated successfully")
    elif response.status_code == 204:
        print("Value updated successfully")
    else:
        print("Error: ", response.status_code)
        
        
    #check
    response = requests.get(url)
    if response.status_code == 200:
       ledStatus = response.json()["ledStatus"]

       print("LED ", ledStatus)
    else:
       print("Error: ", response.status_code)
            
                       
