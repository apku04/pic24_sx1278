import pytest
import serial
import logging
import time

COM_PORTS = ['COM10', 'COM11']


def send_command(ser, command, timeout: float = 5):
    ser.write((command + ' \r\n').encode())
    start_time = time.time()
    response = b''
    logging.info(f"\nSending over USB #{ser.name}: {command}")

    if command == "reset":
        return

    while time.time() - start_time < timeout:
        response += ser.read(ser.in_waiting)
        if b'Error' in response:
            logging.info(f" \n\t Error Response \n {response}")
            raise Exception("Send command returned Error")
        if b'Done' in response or b'\n' in response:
            break
        time.sleep(1)
    else:
        raise Exception("send_command Timeout")
    logging.info(f"\nResponse from DUT: {response.decode()}")
    return response.decode()


class SerialPorts:
    def __init__(self):
        self.sers = [serial.Serial(port) for port in COM_PORTS]


@pytest.fixture(scope='class')
def serial_ports():
    ports = SerialPorts()
    for ser in ports.sers:
        send_command(ser, "set beacon 0")
    yield ports
    for ser in ports.sers:
        ser.close()


@pytest.fixture(scope='class', autouse=True)
def reset_and_reopen_serial_ports(serial_ports):
    for ser in serial_ports.sers:
        send_command(ser, "reset")
    time.sleep(2)

    for ser in serial_ports.sers:
        ser.close()
    time.sleep(2)

    serial_ports.sers = [serial.Serial(port) for port in COM_PORTS]  # Reopen connection

    yield

    # Close connections at the end of the test module
    for ser in serial_ports.sers:
        ser.close()
