#! /bin/bash
echo -n "Id:"
read ID
curl -iX DELETE "http://enigmatic-depths-58073.herokuapp.com/users/$ID"
