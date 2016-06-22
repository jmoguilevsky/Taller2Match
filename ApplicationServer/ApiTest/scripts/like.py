#!/usr/bin/python

import json
import unittest
import requests

def like(token):
	
	json_data_like = {"id": 1}

	headers = {'content-type': 'application/json',
		   'Authorization': token
		  }
	url = 'http://localhost:7000/matches/likes'


	response = requests.post(url, data=json.dumps(json_data_like), headers=headers)

	print response.headers.items()
	print response.text

if __name__ == '__main__':
	like(2)
