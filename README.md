This project embodies a wireless communication system, meticulously crafted in C, envisioned to facilitate seamless communication between nodes in a mesh network. Rooted in a layered architectural paradigm, the system seamlessly integrates the hardware layer, the MAC (Media Access Control) layer, and the network layer to achieve its objectives.

Buffer-Based Communication Flow in the System

Central to the system's design is the innovative buffer-based approach, chosen over traditional direct function calls or interactions. This strategic choice paves the way for asynchronous processing, fostering a decoupled environment between layers and ensuring agile handling of data packets.

1. SX1278 Driver:
At the foundation lies the SX1278 driver, the sentinel of interactions with the physical hardware. When the airwaves carry a packet to the driver, it diligently processes and entrusts it to the receive buffer (pktRxBuf). In the realm of transmissions, the driver scouts the transmit buffer (pktTxBuf), dispatching queued packets. Upon successful transmission, the buffer bids farewell to the packet.

2. MAC Layer:
Ascending the hierarchy, the MAC layer, in its routine vigil, inspects the pktRxBuf for incoming packets. Discovering one triggers a series of MAC-specific rituals, from address verification to acknowledgment management. Post-processing, if the packet's destiny lies upwards, it finds refuge in a dedicated transmit buffer, awaiting the Network layer's attention. Outgoing packets, however, are bequeathed to the pktTxBuf, awaiting the SX1278 driver's transmission rites.

3. Network Layer:
The Network layer, mirroring its predecessor's modus operandi, scouts for packets in the MAC layer's transmit buffer. Such packets, marked for higher realms, undergo procedures like address management or routing. Once refined, they're relegated to a buffer for the Application layer. Conversely, descending packets from the Application realm are ushered into the MAC layer's buffer.

4. Application (Main) Layer:
At the zenith sits the Application or Main layer, the custodian of end applications or tasks. It gleans packets from the Network layer's buffer, subjects them to application-centric rites, and orchestrates appropriate responses. Outbound data or commands embark on a journey, first to the Network layer's buffer and then cascading down the stack.

Task Scheduling in main:
The heart of the system, the main function, orchestrates these buffer verifications and packet rituals. Through meticulous scheduling, it ensures that each stratum gets its due, preventing any one layer from monopolizing the limelight, thus maintaining equilibrium.


The chosen buffer-centric approach stands as a testament to robust and forward-thinking design, tailor-made for systems with resource constraints or where asynchrony is the golden standard. It champions independent layer operations, ensuring data is processed judiciously, and crystallizes a transparent mechanism for inter-layer data migration.