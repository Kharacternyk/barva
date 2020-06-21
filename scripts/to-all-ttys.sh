#!/bin/sh

while read COLOR; do
    for TTY in /dev/pts/*; do
        [ -w $TTY ] && printf '\033]11;%s\007' "$COLOR" > $TTY
    done
done
