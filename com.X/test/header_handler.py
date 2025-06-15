from dataclasses import dataclass


@dataclass
class Header:
    rssi: int
    prssi: int
    rxCnt: int
    destination_adr: int
    source_adr: int
    sequence_num: int
    control_mac: int
    protocol_Ver: int
    TTL: int
    mesh_dest: int
    mesh_control: int
    reserved: int
    control_app: int
    length: int
