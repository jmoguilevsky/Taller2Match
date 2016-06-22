#!/usr/bin/python

import json
import requests
import unittest

def candidates(token):
	

	headers = {'content-type': 'application/json',
		   'Authorization': token
		  }
	
	url = 'http://localhost:7000/matches/candidates'

	response = requests.get(url, headers=headers)

	print response.headers.items()
	print response.text

if __name__ == '__main__':
	candidates(2)
