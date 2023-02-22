#!/bin/bash

# download ip ranges json files
wget -O data/amazon.json "https://ip-ranges.amazonaws.com/ip-ranges.json"
# it's obviously a hassle with microsoft
wget -O data/azure.json `curl -sS https://www.microsoft.com/en-us/download/confirmation.aspx\?id\=56519 | grep -Eo 'https://download\.microsoft\.com/([-_a-zA-Z0-9]*/?)*?\.json' | uniq`
wget -O data/google.json "https://www.gstatic.com/ipranges/cloud.json"

# ipv4 regex
REGEX="([0-9]{1,3}\.){3}[0-9]{1,3}\/[0-9]{1,2}"

# extract ipv4s and create appropriate integer ranges
grep -Eo "$REGEX" "data/amazon.json" | ./venv/bin/python scripts/parse.py \
  > data/amazon_ranges.txt
grep -Eo "$REGEX" "data/azure.json" | ./venv/bin/python scripts/parse.py \
  > data/azure_ranges.txt
grep -Eo "$REGEX" "data/google.json" | ./venv/bin/python scripts/parse.py \
  > data/google_ranges.txt


# populate mongo with ip ranges
./venv/bin/python scripts/update_ranges.py

rm data/*ranges.txt
