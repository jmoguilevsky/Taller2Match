#!/usr/bin/python

import json
import requests
import unittest

def chat(token):
	
	json_data_chat = {"content": "Mensaje de Prueba"}

	headers = {'content-type': 'application/json',
		   'Authorization': token
		  }
	
	url = "http://localhost:7000/chat/me/2" # /me/$ID

	response = requests.post(url, data=json.dumps(json_data_chat), headers=headers)

	print response.headers.items()
	print response.text

if __name__ == '__main__':
	chat(2)
