from flask import Flask
from routes.categorize import categorize


app = Flask(__name__)
app.register_blueprint(categorize, url_prefix='/api/v1/categorize')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
