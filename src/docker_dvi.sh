#!/bin/bash
texi2dvi readme.tex
pdflatex readme.tex
sleep 3
exit