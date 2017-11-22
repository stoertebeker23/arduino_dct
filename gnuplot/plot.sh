#!/bin/bash

# DIR: the directory this script lies in
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

gnuplot -persist $DIR/test.plt
