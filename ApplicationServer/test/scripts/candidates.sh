#! /bin/bash
RED='\033[1;31m'
CYAN='\033[1;36m'
GREEN='\033[1;32m'
NC='\033[0m'

echo -n "Token:"
read TOKEN

HEADER="Authorization:$TOKEN"

echo
echo

curl -iX GET --header $HEADER localhost:7000/matches/candidates
