
# A very simple Flask Hello World app for you to get started with...

from flask import Flask, request, render_template
import json
from datetime import datetime
import csv

app = Flask(__name__,template_folder='templates')


@app.route('/')
def hello_world():
    return "hello"


@app.route('/table',methods = ['GET'])
def genrate_table():
    with open("wlog.csv") as file:
        reader = csv.reader(file)
        return render_template("csv_table.html", csv=reader)

@app.route('/api/send_data',methods = ['POST'])
def get_data():
    try:
        ky= request.headers["X-API-Key"]
    except:
        return "Header Paring Error"
    if ky =='the key':
        if request.is_json:
            data = request.json
            temp = str(data.get("temp"))
            humidity = str(data.get("humidity"))
            with open ('wlog.csv', 'a') as f:
                f.write("%s," % str(datetime.now()))
                f.write("%s," % temp)
                f.write("%s" % humidity)
                f.write("\n")
            return ("Temperature is {0} Centigrade, Humidity is {1} percent".format(temp,humidity))
        else:
            return json.dumps(dict(request.headers))#"Formatting is not application/json"
    else:
        return "API Key is invalid"
