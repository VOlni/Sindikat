import datetime
import logging

import flask.globals
import requests
import speech_recognition as srec
import yagmail
from flask import Flask, redirect, render_template, request, session, url_for

from raspberry import log_handler

# Logging
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
logger.addHandler(log_handler)

# Flask settings
app = Flask(__name__)
app.config["SECRET_KEY"] = "***"

# Mail settings
email = "***@gmail.com"
mail_pass = "password"

# UI variables
VMSG = False
voice = None


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        session["Status"] = str(VMSG)
    return render_template("index.html")


@app.route("/voice", methods=["GET"])
def voice():
    global VMSG
    session = requests.Session()
    recognizer = srec.Recognizer()
    mic = srec.Microphone()
    result = recognize_speech(recognizer, mic)
    logger.info(f"Server - result of recognition : {result}")
    if result == "Tes One":
        VMSG = False
    elif result == "Test Two":
        VMSG = True
    session.post(f"http://127.0.0.1:3001/", data={'voice_message': VMSG})
    flask.globals.session["Voice"] = result
    flask.globals.session["Date"] = datetime.datetime.now()
    logger.info(f"Server - status: {str(VMSG)}")
    return redirect(url_for("index"))


def recognize_speech(rec, mic):
    with mic as source:
        rec.adjust_for_ambient_noise(source)
        audio = rec.listen(source)
    try:
        res = rec.recognize_google(audio, show_all=False, language="en-en")
    except:
        res = None
    return res


if __name__ == "__main__":
    app.run(debug=True, port=3000, host="127.0.0.1")
