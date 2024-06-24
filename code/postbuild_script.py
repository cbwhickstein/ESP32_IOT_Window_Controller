import os
import subprocess

secret_file = """
#pragma once

#include<Arduino.h>

String ssid = "";
String password = "";
"""

def run_restore_secret_script():
    with open("include/secret.hpp", "w") as file:
        pass

    file = open("include/secret.hpp", "w")
    file.write(secret_file)

run_restore_secret_script()