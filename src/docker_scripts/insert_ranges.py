import os

from dotenv import load_dotenv
from pymongo import MongoClient


load_dotenv()
MONGO_HOST = os.getenv('MONGO_HOST')
MONGO_PORT = int(os.getenv('MONGO_PORT', ''))

session = MongoClient(MONGO_HOST, MONGO_PORT)

if session.bit.ip_ranges.count_documents({}) > 0:
    print('Ip ranges collection already populated')
    exit(0)

services = {
    'azure': 'Azure',
    'amazon': 'Amazon Web Services',
    'google': 'Google Cloud Platform',
}

for service in services:
    with open(f'./data/{service}_ranges.txt', 'r') as f:
        lines = f.readlines()
        for line in lines:
            lower_bound, upper_bound = tuple(int(x) \
                    for x in line.strip().split())
            session.bit.ip_ranges.insert_one({
                'service': services[service],
                'lower_bound': lower_bound,
                'upper_bound': upper_bound,
            })

session.close()
