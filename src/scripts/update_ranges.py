import os

from dotenv import load_dotenv
from pymongo import MongoClient, ASCENDING


load_dotenv()
MONGO_HOST = os.getenv('MONGO_HOST')
MONGO_PORT = int(os.getenv('MONGO_PORT', ''))

session = MongoClient(MONGO_HOST, MONGO_PORT)

services = {
    'azure': 'Azure',
    'amazon': 'Amazon Web Services',
    'google': 'Google Cloud Platform',
}

for service in services:
    with open(f'./data/{service}_ranges.txt', 'r') as f:

        session.bit.ip_ranges.create_index([
            ('lower_bound', ASCENDING),
            ('upper_bound', ASCENDING)],
            unique=True)

        lines = f.readlines()
        for line in lines:
            lower_bound, upper_bound = tuple(int(x) \
                    for x in line.strip().split())

            ip_range = session.bit.ip_ranges.find_one({
                'lower_bound': lower_bound,
                'upper_bound': upper_bound,
            })

            if not ip_range or ip_range.get('service') != services[service]:
                session.bit.ip_ranges.update_one({
                    'lower_bound': lower_bound,
                    'upper_bound': upper_bound,
                }, { '$set': {'service': services[service]} }, upsert=True)

    print(f'service {service} done')

session.close()
