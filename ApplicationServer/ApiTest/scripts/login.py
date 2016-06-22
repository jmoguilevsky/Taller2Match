#!/usr/bin/python

import json
import unittest
import requests


def login(email):
	json_data_login = {"email" : email,
			  "password" : "Test"
			  }

	url = "http://localhost:7000/users/login"

	headers = {'content-type': 'application/json'}

	response = requests.post(url, data=json.dumps(json_data_login), headers=headers)

	print response.headers.items()
	print response.text

if __name__ == '__main__':
	login("Test@Test.com")
