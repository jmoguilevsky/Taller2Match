#!/usr/bin/python

import json
import requests
import unittest

def signup(email):
	json_signup_data = {"info": 
				{"email" : email,
				"password" : "Test"
				},
			    "user" : 
				{"email": email,
				"name" :"Usuario de Test",
				"alias":"Rancho Aparte",
				"sex": "male",
				"interests":[
					{"category":"sex",
					"value":"female"
					}
				],
				"location": {"latitude":666,
					    "longitude":666
					    }
				}
			   }



	headers = {'content-type': 'application/json'}
	url = 'http://localhost:7000/users/signup'


	response = requests.post(url, data=json.dumps(json_signup_data), headers=headers)

	print response.headers.items()
	print response.text

if __name__ == '__main__':
	signup("Test@Test.com")
