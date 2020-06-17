#!/bin/sh

barva |
while read COLOR; do
    bspc config normal_border_color $COLOR
done

bspc config normal_border_color $BARVA_BG
