from pymongo import MongoClient
from config import MONGO_HOST, MONGO_PORT


class Mongo:

  def __init__(self):
    try:
      self.session = MongoClient(MONGO_HOST, MONGO_PORT)
    except Exception as e:
      print('error starting mongo', e)


  def get_ip_details(self, ip):
    try:
      db = self.session.bit
      ret = db.ips.find_one({"ip": ip})
      return ret if ret else {}
    except Exception as e:
      print('error on get', e)


  def add_ip(self, ip, provider):
    try:
      db = self.session.bit
      ret = db.ips.insert_one({
        "ip": ip,
        "provider": provider
      })
      print(ret)
    except Exception as e:
      print('error on add', e)


  def edit_ip(self, ip, provider):
    try:
      db = self.session.bit
      ret = db.ips.update_one({
        "ip": ip
      }, {'$set': {"provider": provider}})
      print(ret)
    except Exception as e:
      print('error on edit', e)


  def delete_ip(self, ip):
    try:
      db = self.session.bit
      ret = db.ips.delete_one({
        "ip": ip
      })
      print(ret)
    except Exception as e:
      print('error on delete', e)


  def get_provider(self, value):
    try:
      db = self.session.bit
      ret = db.ip_ranges.find({
        'lower_bound': {'$lte': value},
        'upper_bound': {'$gte': value},
      })

      ret = [x for x in ret]
      if len(ret) > 1:
        raise Exception('more than one entry')

      return ret[-1].get('service') if ret else 'UNKNOWN'
    except Exception as e:
      print('error on provider query', e)
