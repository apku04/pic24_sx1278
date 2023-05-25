This project is a wireless communication system implemented in C, designed to facilitate communication between nodes in a mesh network. The system is based on a layered architecture, consisting of a hardware layer, a MAC (Media Access Control) layer, and a network layer.

Hardware Layer:
The hardware layer is responsible for handling the low-level communication with the physical radio hardware. It provides an interface for the upper layers to interact with the radio hardware, enabling functionalities such as sending and receiving packets, setting up the radio frequency, and controlling the radio's power state.

MAC Layer:
The MAC layer is responsible for coordinating access to the communication medium. It implements the Distributed Coordination Function (DCF) to manage contention between nodes, ensuring that each node has a fair chance to transmit data. The MAC layer also handles the creation and processing of MAC frames, adding or parsing headers as necessary. It communicates with the network layer through a MAC interface, passing data between the two layers.

Network Layer:
The network layer is responsible for managing the routing of packets within the mesh network. It determines the best path for a packet to reach its destination and handles the creation and processing of network frames, adding or parsing headers as necessary. It communicates with the MAC layer through a network interface, passing data between the two layers.

The project provides a modular structure, allowing for easy maintenance and updates. It uses global structures to maintain important configuration parameters and state information for each layer, enabling seamless interaction between different layers.

To interact with this system, a user can create packets containing data to be transmitted within the mesh network. The user passes these packets to the network layer, which handles routing and communication with the MAC layer. The MAC layer then communicates with the hardware layer to transmit the packet over the wireless medium. Similarly, when a packet is received, the system processes it through the hardware, MAC, and network layers before making it available to the user.

Overall, this project aims to provide a flexible and efficient wireless communication system for mesh networks. It offers a layered architecture, facilitating easy integration with various hardware platforms and network topologies.