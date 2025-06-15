import pytest
import time
import logging

from conftest import send_command
from header_handler import Header


def wait_for_data(ser, timeout=5):
    start_time = time.time()
    while time.time() - start_time < timeout:
        if ser.in_waiting > 0:
            return
        time.sleep(0.01)  # short sleep to prevent busy waiting
    else:
        raise Exception("wait_for_data Timeout")


class TestDeviceSunShineScenarios:

    # -------------------------------------- Sunshine scenarios --------------------------------------
    def test_help(self, serial_ports):
        for ser in serial_ports.sers:
            response = send_command(ser, 'help')
            expected_response = (
                "Commands:\n"
                "  help - This message\n"
                "  get <param>\n"
                "  set <param> <value>\n"
                "  send <message>\n"
                "  test <on/off>\n"
                "  version\n"
                "Params: frequency (hz), data_rate, tx_power, mac_address, flash\n"
                "Done\x00"
            )
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_get_frequency(self, serial_ports):
        for ser in serial_ports.sers:
            response = send_command(ser, 'get frequency')
            expected_response = "Frequency: 868.00 MHz\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_set_frequency(self, serial_ports):
        for ser in serial_ports.sers:
            send_command(ser, 'set frequency 868000000')
            response = send_command(ser, 'get frequency')
            expected_response = "Frequency: 868.00 MHz\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_get_data_rate(self, serial_ports):
        for ser in serial_ports.sers:
            response = send_command(ser, 'get data_rate')
            expected_response = "Data Rate: 7\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_set_data_rate(self, serial_ports):
        for ser in serial_ports.sers:
            send_command(ser, 'set data_rate 7')
            response = send_command(ser, 'get data_rate')
            expected_response = "Data Rate: 7\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_get_tx_power(self, serial_ports):
        for ser in serial_ports.sers:
            response = send_command(ser, 'get tx_power')
            expected_response = "TX Power: 14\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_set_tx_power(self, serial_ports):
        for ser in serial_ports.sers:
            send_command(ser, 'set tx_power 14')
            response = send_command(ser, 'get tx_power')
            expected_response = "TX Power: 14\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_set_mac_address(self, serial_ports):
        for ser in serial_ports.sers:
            send_command(ser, 'set mac_address 13')
            response = send_command(ser, 'get mac_address')
            expected_response = "MAC Address: 13\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_send_message(self, serial_ports):
        for ser in serial_ports.sers:
            response = send_command(ser, 'send Hello, world!')
            expected_response = "Done\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    def test_version(self, serial_ports):
        for ser in serial_ports.sers:
            response = send_command(ser, 'version')
            expected_response = "LF_LORA_V1\n\x00"
            logging.info(f"\nExpected {expected_response}Response {response}")
            assert response == expected_response

    # -------------------------------------- Rainy day scenarios --------------------------------------


class TestDeviceRainyDayScenarios:

    # Invalid command
    def test_invalid_command(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'invalid_command')

    # Set frequency with invalid value
    def test_set_invalid_frequency(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set frequency invalid_frequency')

    def test_set_out_of_range_frequency_445mhz(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set frequency 445000000')

    def test_set_out_of_range_frequency_920mhz(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set frequency 920000000')

    # Set data_rate with invalid value
    def test_set_invalid_data_rate(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set data_rate invalid_data_rate')

    def test_set_out_of_range_data_rate_dr13(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set data_rate 13')

    def test_set_out_of_range_data_rate_dr0(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set data_rate 0')

    # Set tx_power with invalid value
    def test_set_invalid_tx_power(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set tx_power invalid_tx_power')

    def test_set_out_of_range_tx_power_0(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set tx_power 0')

    def test_set_out_of_range_tx_power_15(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set tx_power 15')

    # Set mac_address with invalid value
    def test_set_invalid_mac_address(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="Send command returned Error"):
                send_command(ser, 'set mac_address invalid_mac_address')

    # Device not responding
    def test_device_not_responding(self, serial_ports):
        for ser in serial_ports.sers:
            with pytest.raises(Exception, match="send_command Timeout"):
                send_command(ser, 'help', timeout=0.1)


class TestDeviceCommunicationSunShineScenarios:

    def test_send_receive_message(self, serial_ports):
        ser1 = serial_ports.sers[0]
        ser2 = serial_ports.sers[1]

        expected_message = "Hello, world!"
        send_command(ser1, f"send {expected_message}")

        wait_for_data(ser2)  # wait until the data is available
        response = ser2.read(ser2.in_waiting).decode()
        response = response.split("|")[1]  # we are interested in the 2nd part after split
        # clean up the response
        response = response.replace('00', '').replace('0d', '').replace('\n', '').replace('\x00', '').strip()
        logging.info(f"\n Expected {expected_message}Response  {response}")
        assert expected_message == response

    def test_change_mac_addr_send_receive_message_expected_message(self, serial_ports):
        ser1 = serial_ports.sers[0]
        ser2 = serial_ports.sers[1]

        expected_message = "Hello, world!"
        expected_mac_addr = 54

        send_command(ser1, f'set mac_address {expected_mac_addr}')

        send_command(ser1, f"send {expected_message}")

        wait_for_data(ser2)  # wait until the data is available
        response = ser2.read(ser2.in_waiting).decode()

        response_header = response.split("|")[0]
        response_message = response.split("|")[1]
        # clean up the response
        response_message = response_message.replace('00', '').\
            replace('0d', '').replace('\n', '').replace('\x00', '').strip()

        values = tuple(int(value) for value in response_header.split())
        header = Header(*values)

        logging.info(f"\n Expected {expected_message}Response hdr {response_header} Response msg {response_message}")
        assert expected_message == response_message
        assert expected_mac_addr == header.source_adr

    def test_send_multiple_packets_neck_to_neck_and_receive(self, serial_ports):
        ser1 = serial_ports.sers[0]
        ser2 = serial_ports.sers[1]

        transmissions = 10

        for tx in range(transmissions):
            expected_message = f"Hello, world!#{tx}"
            send_command(ser1, f"send Hello, world!#{tx}")

            wait_for_data(ser2)  # wait until the data is available
            response = ser2.read(ser2.in_waiting).decode()
            response_header = response.split("|")[0]
            response_message = response.split("|")[1]
            # clean up the response
            response_message = response_message.replace('00', ''). \
                replace('0d', '').replace('\n', '').replace('\x00', '').strip()

            values = tuple(int(value) for value in response_header.split())
            header = Header(*values)
            logging.info(
                f"\n Message Seq number {header.sequence_num}")
            assert expected_message == response_message
            time.sleep(1)

