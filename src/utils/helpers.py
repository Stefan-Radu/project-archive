import re
from flask import jsonify

def is_ipv4(ip):
    pattern = r'([0-9]{1,3}\.){3}[0-9]{1,3}'
    result = re.search(pattern, ip)
    if result:
        return result.group() == ip
    return False


def parse_ip(ip):
    address = ip.strip()

    value = 0
    for i, byte in enumerate(address.split('.')[::-1]):
        value |= (int(byte) << (8 * i))

    return value


def format_response(ok=True, data={}, message=''):
    if message:
        data.update({
            'message': message
        })

    return jsonify({
        'ok': ok,
        'data': data
    })
