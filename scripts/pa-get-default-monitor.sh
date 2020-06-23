#!/bin/sh

pacmd list-sources | \
grep -B1 '^.name: <.*\.monitor>' | \
awk '/\* index/{getline;monitor=$0;print monitor} /[^\*] index/{getline;fallback=$0;if(monitor==""){print fallback}}' | \
head -n1 | \
sed -E -e 's/^.name: <(.*)>$/\1/'
