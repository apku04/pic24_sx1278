import simpy
import random
import networkx as nx
import matplotlib.pyplot as plt

# Define a class for routing entries
class RoutingEntry:
    def __init__(self, destination, next_hop, hop_count, sequence_number):
        self.destination = destination
        self.next_hop = next_hop
        self.hop_count = hop_count
        self.sequence_number = sequence_number

# Define a class for beacon packets
class Beacon:
    def __init__(self, source_address, sequence_number, routing_table):
        self.source_address = source_address
        self.sequence_number = sequence_number
        self.routing_table = routing_table

    # Calculate the size of the beacon packet in bytes
    @property
    def size_in_bytes(self):
        routing_entry_size = 4  # 4 uint8_t fields
        num_entries = len(self.routing_table)
        beacon_packet_size = 3 + routing_entry_size * num_entries
        return beacon_packet_size

# Define a class for the routing table
class RoutingTable:
    def __init__(self, max_size=255):
        self.entries = []
        self.max_size = max_size

    # Update an existing entry or add a new one
    def update_or_add(self, entry):
        for e in self.entries:
            if e.destination == entry.destination:
                e.next_hop = entry.next_hop
                e.hop_count = entry.hop_count
                e.sequence_number = entry.sequence_number
                return
        if len(self.entries) < self.max_size:
            self.entries.append(entry)

    # Get the next hop for a given destination
    def get_next_hop(self, destination):
        for entry in self.entries:
            if entry.destination == destination:
                return entry.next_hop
        return None

# Define a class for network nodes
class Node:
    def __init__(self, env, node_id):
        self.env = env
        self.node_id = node_id
        self.routing_table = RoutingTable()
        self.sequence_number = 0
        self.neighbors = []

    # Plot the entire network topology
    def plot_entire_topology(self):
        G = nx.Graph()
        for node in self.nodes.values():
            for dest, info in node.routing_table.entries.items():
                G.add_edge(node.node_id, info['next_hop'])
        plt.figure(figsize=(12, 12))
        node_sizes = [G.degree(node) * 500 for node in G.nodes()]
        pos = nx.kamada_kawai_layout(G)
        nx.draw(G, pos, with_labels=True, node_size=node_sizes, node_color="lightcoral", font_size=15, width=3,
                edge_color="gray", font_color="black")
        plt.title("Entire Network Topology")
        plt.show()

    # Display the routing table for the node
    def display_routing_table(self):
        print(f"Routing Table for {self.node_id}:")
        for entry in self.routing_table.entries:
            print(
                f"Destination: {entry.destination}, Next Hop: {entry.next_hop}, Hop Count: {entry.hop_count}, Sequence Number: {entry.sequence_number}")
        print("\n")

    # Send a beacon packet at regular intervals
    def send_beacon(self, interval):
        while True:
            yield self.env.timeout(interval)
            beacon = Beacon(self.node_id, self.sequence_number, self.routing_table.entries)
            self.sequence_number += 1
            for neighbor in self.neighbors:
                neighbor.receive_beacon(beacon)

    # Receive a beacon packet and process it
    def receive_beacon(self, beacon):
        print(f"Beacon received by {self.node_id} from {beacon.source_address} has size: {beacon.size_in_bytes} bytes")
        rssi = random.randint(1, 100)  # Simulating RSSI as a random value for now
        if rssi < 50:  # Assuming 50 as the threshold for good quality link
            return

        # Direct neighbor update
        found = False
        for entry in self.routing_table.entries:
            if entry.destination == beacon.source_address:
                entry.next_hop = beacon.source_address
                entry.hop_count = 1
                entry.sequence_number = beacon.sequence_number
                found = True
                break

        if not found:
            new_entry = RoutingEntry(beacon.source_address, beacon.source_address, 1, beacon.sequence_number)
            self.routing_table.update_or_add(new_entry)

        # Update based on beacon's routing table
        for info in beacon.routing_table:
            if info.destination == self.node_id:
                continue

            found = False
            for entry in self.routing_table.entries:
                if entry.destination == info.destination:
                    if entry.hop_count > info.hop_count + 1:
                        entry.hop_count = info.hop_count + 1
                        entry.next_hop = beacon.source_address
                        entry.sequence_number = info.sequence_number
                    found = True
                    break

            if not found:
                new_entry = RoutingEntry(info.destination, beacon.source_address, info.hop_count + 1,
                                         info.sequence_number)
                self.routing_table.update_or_add(new_entry)

# Define a class for the entire network
class Network:
    def __init__(self, env, topology):
        self.env = env
        self.nodes = {node_id: Node(env, node_id) for node_id in topology.keys()}
        for node_id, neighbors in topology.items():
            self.nodes[node_id].neighbors = [self.nodes[n] for n in neighbors]

    # Run the simulation for a given time
    def run(self, simulation_time):
        for node in self.nodes.values():
            self.env.process(node.send_beacon(1))  # Sending beacon every 1 time unit
        self.env.run(until=simulation_time)

    # Plot the entire network topology
    def plot_entire_topology(self):
        G = nx.Graph()
        for node in self.nodes.values():
            for entry in node.routing_table.entries:
                G.add_edge(node.node_id, entry.next_hop)

        pos = nx.kamada_kawai_layout(G)
        nx.draw(G, pos, with_labels=True, node_size=2000, node_color="skyblue", font_size=15, width=3,
                edge_color="gray")
        plt.title("Entire Network Topology")
        plt.show()

# Main execution
if __name__ == "__main__":
    env = simpy.Environment()

    # Define the network topology

    topology = {
        'node#1': ['node#2', 'node#3', 'node#4', 'node#5'],
        'node#2': ['node#1', 'node#6', 'node#7'],
        'node#3': ['node#1', 'node#8'],
        'node#4': ['node#1', 'node#9'],
        'node#5': ['node#1', 'node#10'],
        'node#6': ['node#2'],
        'node#7': ['node#2'],
        'node#8': ['node#3'],
        'node#9': ['node#4'],
        'node#10': ['node#5']
    }

    # topology = {
    #     'node_1': ['node_2', 'node_4', 'node_13'],
    #     'node_2': ['node_1', 'node_3', 'node_5', 'node_13'],
    #     'node_3': ['node_2', 'node_6', 'node_14'],
    #     'node_4': ['node_1', 'node_5', 'node_7', 'node_13'],
    #     'node_5': ['node_2', 'node_4', 'node_8', 'node_14'],
    #     'node_6': ['node_3', 'node_9', 'node_14'],
    #     'node_7': ['node_4', 'node_8', 'node_10', 'node_15'],
    #     'node_8': ['node_5', 'node_7', 'node_11', 'node_15'],
    #     'node_9': ['node_6', 'node_12', 'node_16'],
    #     'node_10': ['node_7', 'node_15'],
    #     'node_11': ['node_8', 'node_16'],
    #     'node_12': ['node_9', 'node_16'],
    #     'node_13': ['node_1', 'node_2', 'node_4'],
    #     'node_14': ['node_3', 'node_5', 'node_6'],
    #     'node_15': ['node_7', 'node_8', 'node_10'],
    #     'node_16': ['node_9', 'node_11', 'node_12']
    # }

    # Create a network instance and run the simulation
    network = Network(env, topology)
    network.run(1440)  # Simulating for 24 hours, with each iteration being a minute

    # Display the routing table for each node
    for node in network.nodes.values():
        node.display_routing_table()

    # Plot the entire network topology
    network.plot_entire_topology()

    # topology = {
    #     'node_1': ['node_2', 'node_4'],
    #     'node_2': ['node_1', 'node_3', 'node_5'],
    #     'node_3': ['node_2', 'node_6'],
    #     'node_4': ['node_1', 'node_5', 'node_7'],
    #     'node_5': ['node_2', 'node_4', 'node_8'],
    #     'node_6': ['node_3', 'node_9'],
    #     'node_7': ['node_4', 'node_8', 'node_10'],
    #     'node_8': ['node_5', 'node_7', 'node_11'],
    #     'node_9': ['node_6', 'node_12'],
    #     'node_10': ['node_7'],
    #     'node_11': ['node_8'],
    #     'node_12': ['node_9']
    # }