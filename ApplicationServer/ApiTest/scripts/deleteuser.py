#!/usr/bin/python

import json
import requests
import unittest

def delete(user_id):
	url = "http://enigmatic-depths-58073.herokuapp.com/users/" + str(user_id)

	response = requests.delete(url)

	print response.headers.keys()
	print response.text

if __name__ == '__main__':
	delete(2)
