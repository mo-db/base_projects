#!/opt/homebrew/bin/fish
set -g flags "-g"
cc -S -fsanitize=address $argv[1] -L./../base/lib/ -lbase -Wall $flags
