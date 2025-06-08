#! /bin/bash

gcc pilgrims.c  -o bin/pilgrims 

echo "./bin/pilgrims" > pilgrims.sh

chmod +x pilgrims.sh

echo Completed!
