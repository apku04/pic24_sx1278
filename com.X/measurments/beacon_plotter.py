import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Serial port configuration
ser = serial.Serial('COM9', 57600)  # replace with your serial port and baud rate

# Set up the figure and the subplot
fig, ax = plt.subplots()

# Define color cycle for different source_adr
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
color_dict = {}
node_dict = {}

node_gw = 1

def update(i):
    # Read a line from the serial port

    try:
        line = ser.readline().decode('utf-8').strip()
        # Remove the trailing "|"
        line = line.rstrip('|')

        print(line)

        # Split the line into columns
        cols = line.split()

        # Extract source_adr and prssi
        source_adr = int(cols[4])  # source_adr is in decimal now
        prssi = int(cols[1])

        # If the source_adr does not have an assigned color, assign one
        if source_adr not in color_dict:
            color_dict[source_adr] = colors[len(color_dict) % len(colors)]

        # Update the node_dict with the new prssi value
        node_dict[source_adr] = prssi

        # Clear the current plot
        ax.clear()

        # Set plot limits
        ax.set_xlim(1, 5)  # For ID's from 5 to 15
        ax.set_ylim(-120, 0)  # Assuming prssi values are negative and lie between -120 and 0

        # Plot the GW-node at the center (for visualization purpose, placing GW at ID 10)
        # ax.scatter(node_gw, -75, color='red', s=100)  # Centering GW node around -75 assuming prssi range from -120 to 0

        # Plot all the source nodes
        for adr, prssi in node_dict.items():
            ax.scatter(adr, prssi, color=color_dict[adr])
            ax.text(adr, prssi, str(adr))

        # Set plot labels
        ax.set_xlabel('Node ID')
        ax.set_ylabel('prssi')
        ax.set_title('GW Node and Source Nodes')
    except:
        pass



# Run the animation
ani = animation.FuncAnimation(fig, update, interval=1000)

# Show the plot
plt.show()
