import os

from dotenv import load_dotenv
load_dotenv()


MONGO_HOST = os.getenv('MONGO_HOST')
MONGO_PORT = int(os.getenv('MONGO_PORT', 27017))

print(MONGO_PORT, MONGO_HOST)
