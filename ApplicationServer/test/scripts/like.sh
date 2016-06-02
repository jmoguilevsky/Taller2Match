#! /bin/bash
echo -n "Token:"
read TOKEN
echo -n "Id:"
read ID

HEADER="Authorization:$TOKEN"
JSON_LIKE={\"id\":\"$ID\"}

echo
echo

curl -iX POST --header $HEADER -d $JSON_LIKE localhost:7000/matches/likes
