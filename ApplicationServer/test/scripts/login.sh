#! /bin/bash

echo -n "Email: "
read EMAIL
echo -n "Password: "
read PASSWORD

JSON_LOGIN={\"password\":\"$PASSWORD\",\"email\":\"$EMAIL\"}

echo
echo

curl -iX POST -d $JSON_LOGIN  localhost:7000/users/login
