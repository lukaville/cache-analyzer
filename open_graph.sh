#!/bin/sh
cd www || exit
open "http://localhost:8000"
/usr/bin/python -m SimpleHTTPServer 8000 www