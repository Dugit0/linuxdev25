#!/usr/bin/env bash

x=0
y=0
last_y=0
chars=""
while IFS= read -r line; do
    for (( i=0; i<${#line}; i++ )); do
        char=${line:i:1}
        # echo $x $y $char
        chars="${x},${y},${char} ${chars}"
        x=$((x+1))
    done
    x=0
    y=$((y+1))
    last_y=$y
done


chars=$(echo $chars | xargs shuf -e)
echo $chars
tput clear
for i in $chars; do
    IFS=',' read y x char <<< $i
    tput cup $x $y
    echo -n $char
    if test $1; then
        sleep $1
    fi
done
tput cup $last_y 0
