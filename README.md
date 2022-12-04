# ft_traceroute
Aims to reproduce `traceroute`'s Linux binary (on his most part). This is for educational purposes.

## Mandatory part

- Handles IPv4 addresses only.
- We do not need to manage D.N.S. resolution for probes' results printing.
- Manage the main loop with `select` function so don't even think about `poll`/`ppoll` or `fcntl` functions!

## Listed traceroute's internal operation

- Only one mandatory agrument : **hostname**/**IP address** of the host.

- Launch probes over IP network by using TTL.

- Begin with probe of 1 to 30 "hops" (by default).

- Send three probes per TTL value (by default).

- Listening on ICMP responds.

### Concerning protocol

Traceroute wants to avoid host packet processing. For that part it means :
- UDP : set destionation port as `unlikely`.
- TCP : half-open technique.
> Based on [TCP connexion establishement](https://en.wikipedia.org/wiki/Transmission_Control_Protocol#Connection_establishment). Send a `SYN` request then wait the `SYN ACK`
> return for the receiver but do not send the usual reply to terminate the handshake (`ACK`). This technique is not recommended for port scanning as it could be easy blocked. Check [here](https://nmap.org/book/port-scanning.html) for more informations.


### Stopping conditions :
- Receiving an ICMP "port unreachable" (type 3/code 3)
- No response for a period of time as 5.0 seconds (by default)
- If _"almost"_ all probes is unreachable-like.

### Printing :
If a response is provided:
    - TTL
    - Gateway's address
        - Print all responding addresses even if the response come from a different one.
        - Additionnal informations (_Optionnal_)
    - RTT
    - Details' annotations (_When needed_). List:
        - **!H** : _host unreachable_
        - **!N** : _network unreachable_
        - **!P** : _port unreachable_
        - **!S** : _source route failed_
        - **!F** : _fragmentation needed_
        - **!X** : _communication administratively prohibited_
        - **!V** : _host precedence violation_
        - **!C** : _precedence cutoff in effect_
        - **!`<num>`** : _ICMP unreachable code `<num>`_

If not:
    - `*` only.

## Lexicon

IP  : Internet Protocol
ICMP: Internet Control Message Protocol
TCP : Transmission Control Protocol, also referred as TCP over IP (`TCP/IP`) or _"connection oriented"_ protocol.
UDP : User Datagramm Protocol, also referenced as _"connectionless oriented"_ protocol.
TTL : Time To Live
RTT : Round Trip Time


