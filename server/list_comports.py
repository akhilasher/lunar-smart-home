import serial.tools.list_ports


def get_comports():
    listy = []
    for com_dev in serial.tools.list_ports.comports():
        listy.append(com_dev.device)
    return listy

# print(get_comports())
