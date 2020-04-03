#!/bin/bash

pandoc -s --toc -c pandoc.css README -o doc/html/readme.html 
pandoc -s --toc README -o doc/pdf/readme.tex
pdflatex doc/pdf/readme.tex -output-directory=doc/pdf/

