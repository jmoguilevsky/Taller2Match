#! /bin/bash
echo -n "Token:"
read TOKEN

HEADER="Authorization:$TOKEN"

echo
echo

curl -iX POST --header $HEADER -d '' localhost:7000/users/logout
