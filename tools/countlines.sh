#!/bin/bash

wc `find src -regex '.*.cpp'` `find src -regex '.*.hpp'` `find src -regex '.*.tpp'`
