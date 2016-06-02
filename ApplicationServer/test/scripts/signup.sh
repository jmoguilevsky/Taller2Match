#! /bin/bash
echo -n "Name:"
read NAME
echo -n "Email:"
read EMAIL
echo -n "Password:"
read PASSWORD

JSON_SIGNUP={\"info\":{\"email\":\"$EMAIL\",\"password\":\"$PASSWORD\"},\"user\":{\"email\":\"$EMAIL\",\"name\":\"$NAME\",\"alias\":\"$NAME\",\"interests\":\[{\"category\":\"category1\",\"value\":\"value1\"}\],\"location\":{\"latitude\":121,\"longitude\":121}}}

echo 
echo 

curl -iX POST -d "$JSON_SIGNUP"  localhost:7000/users/signup

