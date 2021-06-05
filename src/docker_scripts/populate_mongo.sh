#!/bin/bash

# ipv4 regex
REGEX="([0-9]{1,3}\.){3}[0-9]{1,3}\/[0-9]{1,2}"

# extract ipv4s and create appropriate integer ranges
grep -Eo "$REGEX" "data/amazon.json" | ./venv/bin/python docker_scripts/parse.py \
  > data/amazon_ranges.txt
grep -Eo "$REGEX" "data/azure.json" | ./venv/bin/python docker_scripts/parse.py \
  > data/azure_ranges.txt
grep -Eo "$REGEX" "data/google.json" | ./venv/bin/python docker_scripts/parse.py \
  > data/google_ranges.txt


# populate mongo with ip ranges
./venv/bin/python docker_scripts/insert_ranges.py

exec "$@"
