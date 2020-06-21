#!/bin/sh

while read COLOR; do
    bspc config normal_border_color "$COLOR"
done
