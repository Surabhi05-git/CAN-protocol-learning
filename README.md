# CAN Protocol – Learning Repository

This repository contains a collection of learning materials created to
understand **Controller Area Network (CAN)** protocol concepts from an
automotive embedded systems perspective.

It includes presentation slides (converted to PDF) along with a simple
C++ program demonstrating CAN signal reading and unpacking so we can use it in a SOA
---

## Topics Covered

- CAN protocol fundamentals and standard CAN frame structure
- Difference between CAN messages and CAN signals
- Data Length Code (DLC) and CAN data bytes
- DBC (Database CAN) files and signal definitions
- Signal attributes: start bit, length, endianness, scaling, offset, and units
- CAN signal packing and unpacking
- Sender-side and receiver-side signal handling
- Continuous (blocking) CAN listening
- Event-based CAN listening using `select()`
- Practical automotive ECU use cases

---

## Repository Contents

### Presentations (PDF)
- CAN Message and Signal Extraction Using DBC
- CAN Signal Packing and Unpacking
- Continuous vs Event-Based CAN Listening

### Code Example
- A C++ program demonstrating:
  - Reading incoming CAN signal which is in Packed format (speed) and unpack it using auto generated .c and .h files from CANTOOLS
  - Unpacking CAN data bytes to reconstruct original signal values
  - Printing packed CAN bytes and unpacked signal values OR storing unpack data so we can use it in SOA

---

## Code Description

The auto generated C program performs the following operations:
- Defines speed 16-bit signals
- Packs these signals into CAN data bytes using bitwise operations
- Stores the packed data in an 8-byte CAN data array
- Unpacks the received bytes to reconstruct the original values

This logic is commonly used in real automotive software before transmitting
signals over CAN and after receiving CAN frames.

---

## Tools and Concepts Referenced

- Classical CAN protocol
- DBC files
- Bitwise operations in C
- Linux CAN concepts
- ECU-to-ECU communication
- CANTOOLS

---

## Purpose

This repository was created to:
- Build a strong conceptual and practical understanding of CAN communication
- Demonstrate bit-level signal handling using C
- Support learning of automotive middleware, AUTOSAR,
  and SOA/SOME-IP based systems

---

## Note

The original presentations were created in PPT format and later converted
to PDF for improved viewing support on GitHub.
The code is written for learning and demonstration purposes.
