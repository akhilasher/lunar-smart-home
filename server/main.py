import json
import serial
import logging
import threading
import list_comports
from websocket_server import WebsocketServer, WebSocketHandler


# ----------------
# global variables
# ----------------

arduinos: tuple[serial.Serial] = []
state = {
    "bedroom_temp": 0,
    "bedroom_hum": 0,
    "bedroom_fan": False,
    "kitchen_light": False,
    "kitchen_temp": 0,
    "kitchen_hum": 0,
    "kitchen_gas_level": 0,
    "greenhouse_temp": 0,
    "greenhouse_hum": 0,
    "greenhouse_soil_hum": 0,
    "airlock_in": False,
    "airlock_out": False,
    "settings": json.load(open("settings.json", "r")),
}


server = WebsocketServer(host="127.0.0.1", port=12345, loglevel=logging.INFO)

# -------------
# arduino stuff
# -------------


def arduino_worker(arduino: serial.Serial):
    while True:
        data = arduino.readline().decode("utf-8").strip()
        print(data)

        try:
            for prop in data.split(","):
                # split p at = into key and value
                key, value = prop.split("=")
                if key in state:
                    state[key] = json.loads(value)

        except Exception as e:
            print("error:", data, e)

        run_logic_stuff()
        server.send_message_to_all(json.dumps(state).encode("utf-8"))


listy = list_comports.get_comports()
for porty in listy:
    arduino = serial.Serial(port=porty, baudrate=9600)
    print("found arduino on " + porty)
    arduinos.append(arduino)
    tthread = threading.Thread(target=arduino_worker, args=[arduino])
    tthread.start()

# ----------------
# websocket server
# ----------------


def run_logic_stuff():
    required_temp = state["settings"]["required_bedroom_temp"]
    print(
        state["bedroom_fan"],
        state["settings"]["bedroom_fan_auto"],
        state["bedroom_temp"],
        required_temp,
    )
    if (
        state["bedroom_fan"] == False
        and state["settings"]["bedroom_fan_auto"] == True
        and state["bedroom_temp"] - required_temp > 1
    ):
        print("turning on fan")
        for ard in arduinos:
            ard.write("bedroom_fan_on\n".encode("ascii"))
    elif (
        state["bedroom_fan"] == True
        and state["settings"]["bedroom_fan_auto"] == True
        and state["bedroom_temp"] - required_temp < 1
    ):
        for ard in arduinos:
            ard.write("bedroom_fan_off\n".encode("ascii"))


def message_received(client: WebSocketHandler, server: WebsocketServer, message: str):
    # if message.startswith("1"):
    #     print("identify")
    # elif message.startswith("2"):
    #     print("dispatch")
    # server.send_message_to_all(message)
    if message.startswith("settings,"):
        for prop in message[9:].split(","):
            # split p at = into key and value
            key, value = prop.split("=")
            if key in state["settings"]:
                state["settings"][key] = json.loads(value)
                run_logic_stuff()

        json.dump(state["settings"], open("settings.json", "w"))
    else:
        print(message)
        for ard in arduinos:
            ard.write((message.strip() + "\n").encode("ascii"))


def new_client(client: WebSocketHandler, server: WebsocketServer):
    client["handler"].send_message(json.dumps(state).encode("utf-8"))


server.set_fn_new_client(new_client)
server.set_fn_message_received(message_received)
server.run_forever()
