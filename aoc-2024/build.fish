#!/opt/homebrew/bin/fish
set -g flags "-g -Wall -Wextra"
clang -fsanitize=address $argv[1] $flags
