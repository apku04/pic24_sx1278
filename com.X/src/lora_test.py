import random
import string
import time
import threading
import uuid
import serial
import matplotlib.pyplot as plt
from binascii import unhexlify
from threading import Thread, Event

# Shared data
sent_data = []
matched_count = 0
received_lines = []

# Thread-safe lock for the received_lines list
received_lines_lock = threading.Lock()


def read_from_transceiver(ser, stop_event):
    global received_lines
    while not stop_event.is_set():
        try:
            if ser.in_waiting > 0:
                line = ser.readline()
                if line:
                    received_lines.append(line)
        except serial.SerialException as e:
            print(f"SerialException: {e}")
            break
        except Exception as e:
            print(f"Exception: {e}")
            break


def get_received_line():
    global received_lines

    with received_lines_lock:
        if received_lines:
            return received_lines.pop(0)
        else:
            return None


# Sender functions
def generate_random_string(length):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))


def wait_for_transmission_completed(ser):
    received_data = b''
    while b'Transmission completed' not in received_data:
        received_data += ser.read(ser.in_waiting)
        time.sleep(0.1)


def parse_data(data):
    global matched_count

    sliced_data = data[:48].decode('latin-1')
    clean_sliced_data = ''.join(c for c in sliced_data if c in string.printable)

    for sent_datum in sent_data:
        clean_sent_datum = ''.join(c for c in sent_datum[:48] if c in string.printable)
        if clean_sliced_data == clean_sent_datum:
            print(f'Match  : \t {clean_sliced_data}')
            matched_count += 1
            break
    else:
        print(f'No Match: \t {clean_sliced_data}')

    return int(data[0]), int(data[1])


def plot_rssi_data(p, r, run):
    # Create a new figure and axis object
    fig, ax = plt.subplots()

    # Plot the rssi data as a blue line
    ax.plot(range(len(r)), r, color='blue', label='rssi')

    # Plot the prssi data as a red line
    ax.plot(range(len(p)), p, color='red', label='p-rssi')

    # Set the x-axis label and limits
    ax.set_xlabel('Sample Number')
    ax.set_xlim(0, max(len(p), len(r))-1)

    # Set the y-axis label and limits
    ax.set_ylabel('RSSI Value')
    #ax.set_ylim(min(p+r), max(p+r))

    # Add a legend and title
    ax.legend()
    ax.set_title('RSSI Data')

    ax.grid()

    # Generate a random string for the filename
    rand_str = ''.join(random.choices('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890', k=8))

    # Construct the filename with the random string and the run argument
    filename = f'lora_test_{run}_{rand_str}.png'

    # Save the figure to a file
    fig.savefig(filename)


def configure_transceiver(name, ser, frequency, timeout=5):
    command = f'set frequency {frequency} '

    print(f"Configure {name} transceiver with {frequency} hz")

    ser.write(command.encode())
    ser.write(b'\r\n')

    start_time = time.time()
    response = b''

    while time.time() - start_time < timeout:
        response += ser.read(ser.in_waiting)
        if b'Done' in response:
            break
        if b'Error' in response:
            return False
        time.sleep(1)
    else:
        raise Exception("configure_transceiver Timeout")

    start_time = time.time()

    # Verify the frequency
    ser.write(b'get frequency \r\n')
    expected_response = f"Frequency: {frequency / 1e6:.2f} MHz".encode()

    while time.time() - start_time < timeout:
        ser.write(b'get frequency \r\n')
        response = ser.read(ser.in_waiting)
        if expected_response in response:
            print(f"Done Configure {name} transceiver with {frequency} hz")
            return True
        time.sleep(1)
    else:
        raise Exception("configure_transceiver Timeout")


def reset_ser_buffer(ser):
    ser.reset_input_buffer()
    ser.reset_output_buffer()


def run_test(sender_ser, receiver_ser, num_strings_to_send=1):
    rssi = []
    prssi = []

    print("\t -------- Start Test ---------\n")

    for _ in range(num_strings_to_send):
        random_string = generate_random_string(48)
        message = f'send {random_string}'
        print(f'Sending: \t {random_string}')

        # Append sent string to the shared list
        sent_data.append(random_string)

        sender_ser.write(message.encode())
        sender_ser.write(b'\r\n')

        wait_for_transmission_completed(sender_ser)

        # Reading the received data
        skip_line = False
        while True:
            line = get_received_line()
            if line:
                line_str = line.decode('latin-1').strip()
                printable_line_str = ''.join(filter(lambda x: x in string.printable, line_str))
                if printable_line_str.startswith("----- <RX> ----"):
                    skip_line = True
                elif skip_line:
                    hex_string = printable_line_str.replace(" ", "").replace("ffff", "ff")
                    if len(hex_string) % 2 != 0:
                        hex_string = "0" + hex_string
                    data = unhexlify(hex_string)
                    r, p = parse_data(data)
                    rssi.append(r)
                    prssi.append(p)
                    break
            else:
                time.sleep(0.1)  # Sleep for a short time to allow more data to be read

    reset_ser_buffer(sender_ser)
    reset_ser_buffer(receiver_ser)

    plot_rssi_data(prssi, rssi, num_strings_to_send)

    # Display the success rate
    success_rate = (matched_count / len(sent_data)) * 100
    print(f"Success rate: {success_rate:.2f}%")

    return rssi, prssi


def create_boxplot(data1, data2):
    fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(10, 5))

    # Create boxplot for data1
    axes[0].boxplot(data1)
    axes[0].set_title('Data1')
    axes[0].set_xticks(range(1, len(data1) + 1))
    axes[0].set_xticklabels([f'Group {i}' for i in range(1, len(data1) + 1)])

    # Create boxplot for data2
    axes[1].boxplot(data2)
    axes[1].set_title('Data2')
    axes[1].set_xticks(range(1, len(data2) + 1))
    axes[1].set_xticklabels([f'Group {i}' for i in range(1, len(data2) + 1)])

    plt.tight_layout()
    plt.savefig(f"boxplot_loratest_{str(uuid.uuid4())[:8]}.png")


def main(sender_port, receiver_port, baudrate):
    global sent_data, matched_count

    sender_ser = serial.Serial(sender_port, baudrate)
    reset_ser_buffer(sender_ser)

    receiver_ser = serial.Serial(receiver_port, baudrate)
    reset_ser_buffer(receiver_ser)

    configure_transceiver("Sender", sender_ser, 870000000)
    configure_transceiver("receiver", receiver_ser, 870000000)

    reset_ser_buffer(sender_ser)
    reset_ser_buffer(receiver_ser)

    # Start the receiving thread
    stop_event = Event()
    read_thread = Thread(target=read_from_transceiver, args=(receiver_ser, stop_event))
    read_thread.daemon = True
    read_thread.start()

    test_r = []
    test_p = []

    for run in range(5):
        sent_data = []
        matched_count = 0

        r, p = run_test(sender_ser, receiver_ser, 10)
        test_r.append(r)
        test_p.append(p)

    create_boxplot(test_r, test_p)

    stop_event.set()
    read_thread.join()
    sender_ser.close()
    receiver_ser.close()


if __name__ == "__main__":
    senderport = "COM35"  # Sender serial port
    receiverport = "COM30"  # Receiver serial port
    baud_rate = 115200

    main(senderport, receiverport, baud_rate)
