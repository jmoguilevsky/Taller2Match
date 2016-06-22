#!/usr/bin/python

import json
import unittest
import requests


def logout(token):

	headers = {'content-type': 'application/json',
		   'Authorization': token
		  }
	url = 'http://localhost:7000/users/logout'


	response = requests.post(url, headers=headers)

	print response.headers.items()
	print response.text

if __name__ == '__main__':
	logout(2)
