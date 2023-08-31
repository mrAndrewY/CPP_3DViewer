#!/bin/bash

ID="$(docker ps -q)"
docker cp $ID:/project/readme.pdf .
docker stop $ID
