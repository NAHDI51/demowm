#!/bin/sh

echo "=== Total LOC ==="
wc -l $(find src -name '*.c' -o -name '*.h')

echo
echo "=== By File ==="
find src -name '*.c' -o -name '*.h' | xargs wc -l