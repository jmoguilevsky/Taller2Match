#! /bin/bash
echo -n "Token:"
read TOKEN
echo -n "Id:"
read ID
echo -n "Content:"
read CONTENT

HEADER=Authorization:$TOKEN
JSON_CHAT={"content":\"$CONTENT\"}

echo
echo

curl -iX POST --header "$HEADER" -d "$JSON_CHAT" "localhost:7000/chat/me/$ID"
