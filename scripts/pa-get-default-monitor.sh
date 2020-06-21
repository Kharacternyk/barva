#!/bin/sh

pacmd list-sources | \
grep -m 1 '^.name: <.*\.monitor>' | \
sed -E -e 's/^.name: <(.*)>$/\1/'
