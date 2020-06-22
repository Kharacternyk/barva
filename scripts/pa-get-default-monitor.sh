#!/bin/sh

pacmd list-sources | \
awk '/\* index/{getline; print}' | \
grep -m 1 '^.name: <.*\.monitor>' | \
sed -E -e 's/^.name: <(.*)>$/\1/'
