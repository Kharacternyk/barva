#!/bin/sh

pacmd list-sources | \
grep '^.name: <.*\.monitor>' | \
sed -E -e 's/^.name: <(.*)>$/\1/' | \
head -n1
