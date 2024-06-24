import os
from dotenv import load_dotenv

load_dotenv()

secret_file = f"""
#pragma once

#include<Arduino.h>

String ssid = "{os.getenv("SSID")}";
String password = "{os.getenv("WLANPW")}";
"""

def run_embed_secret_script():
    with open("include/secret.hpp", "w") as file:
        pass

    file = open("include/secret.hpp", "w")
    file.write(secret_file)

run_embed_secret_script()