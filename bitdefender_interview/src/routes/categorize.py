from flask import Blueprint, request
from db.mongo import Mongo
from utils.helpers import is_ipv4, parse_ip, format_response


categorize = Blueprint('categorize_api', __name__)

mongo = Mongo()

# get ip details
@categorize.route('/', methods=['GET'])
def get_service_provider():
    ip = request.args.get('ip')

    if not ip:
        return format_response(
            ok=False,
            message='`ip` param mandatory')

    if not is_ipv4(ip):
        return format_response(
            ok=False,
            message='Ip incorrectly formatted')

    details = mongo.get_ip_details(ip)
    if details == {}:
        details = { 'ip': ip, 'provider': 'UNKNOWN', }

    return format_response(
        ok=True,
        data={
            'ip': details.get('ip'),
            'company': details.get('provider'),
        })

# insert and ip to be tracked
@categorize.route('/', methods=['POST'])
def insert_ip():
    data = request.get_json()
    ip = data.get('ip')

    if not ip:
        return format_response(
            ok=False,
            message='`ip` param mandatory')

    if not is_ipv4(ip):
        return format_response(
            ok=False,
            message='Ip incorrectly formatted')


    parsed = parse_ip(ip)
    provider = mongo.get_provider(parsed)
    print(ip, provider)
    mongo.add_ip(ip, provider)

    return format_response(
        ok=True,
        message='IP inserted successfully.')


# update an ip's details if those were changed remotely
@categorize.route('/', methods=['PUT'])
def update_ip():
    data = request.get_json()
    ip = data.get('ip')

    if not ip:
        return format_response(
            ok=False,
            message='`ip` param mandatory')

    if not is_ipv4(ip):
        return format_response(
            ok=False,
            message='Ip incorrectly formatted')

    previous_provider = mongo.get_ip_details(ip) \
        .get('provider', 'UNKNOWN')

    parsed = parse_ip(ip)
    new_provider = mongo.get_provider(parsed)

    if previous_provider == new_provider:
        return format_response(
            ok=True,
            message='No changes')

    mongo.edit_ip(ip, new_provider)

    return format_response(
        ok=True,
        message='IP updated successfully.')


# delete an ip
@categorize.route('/', methods=['DELETE'])
def delete_ip():
    ip = request.args.get('ip')

    if not ip:
        return format_response(
            ok=False,
            message='`ip` param mandatory')

    if not is_ipv4(ip):
        return format_response(
            ok=False,
            message='Ip incorrectly formatted')

    mongo.delete_ip(ip)

    return format_response(
        ok=True,
        message='IP deleted successfully.')
