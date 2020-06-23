#!/bin/sh

pacmd list-sources | \
grep -B1 '^.name: <.*\.monitor>' | \
awk '/\* index/{getline;monitor=$0} /[^\*] index: [01]/{getline;fallback=$0} END {print (monitor=="") ? fallback : monitor}' | \
head -n1 | \
sed -E -e 's/^.name: <(.*)>$/\1/'
