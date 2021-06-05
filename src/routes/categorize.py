from flask import Blueprint, request
from db.mongo import Mongo
from utils.helpers import is_ipv4, parse_ip, format_response


categorize = Blueprint('categorize_api', __name__)

mongo = Mongo()

# get ip details
@categorize.route('/', methods=['GET'])
def get_service_provider():
    print('whyyyyyyyyyy')
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
        message='IP details retrieved successfully.',
        data={
            'ip': details.get('ip'),
            'company': details.get('provider'),
        })


@categorize.route('/', methods=['POST'])
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


@categorize.route('/', methods=['DELETE'])
def delete_ip():
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

    return format_response(
        ok=True,
        message='IP inserted successfully.')
