#!/usr/bin/python

import unittest
import json
import requests
from jsonschema import validate

from scripts import login
from scripts import logout


class TestSmoke(unittest.TestCase):
	
	def setUp(self):
		
		# Ejemplo de schema
		self.userSchema = { 
			"type" : "object",
			"properties": { 
				"id" : {"type" : "number"},
				"name" : {"type" : "string"},
				"alias" : {"type" : "string"},
				"email" : {"type" : "string"},
				"photo_profile" : {"type" : "string"},
				"interests" : {
					"type" : "array",
					"items" : {"type" : "object"}
				},
				"location" : {"type" : "object"}
			}
		}
				
				

	def test_validate_user_schema(self):
		"""This test is going to proof that the API is working."""
		
		response = requests.get("https://enigmatic-depths-58073.herokuapp.com/users/1")
		
		json_body = json.loads(response.text)
		user_data = json_body["user"]
		validate(user_data, self.userSchema)

		self.assertTrue(True)

	def test_smoke(self):
		"""This test is going to proof nothing"""
		login.login("Test@Test.com")
		logout.logout(2)


if __name__ == '__main__':
	unittest.main()



