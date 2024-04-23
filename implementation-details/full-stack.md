# Overview
## Introduction
The goal of this section is eventually explain exactly how our project works from a high level. This document should be readable to someone without extensive technical experience.
### Our Objective
We want to create a SSH server that will function on a microcontroller with only one CPU thread (no operating system!) and not much memory. The single thread CPU is the main challenge. We'll go into more depth about why that is in the "Loop Structure" section. The gist is that because other applications have to run in a timely manner, we can't lock up the CPU with our own calculations for more than single-digit milliseconds at a time. Our memory limitations were determined by the microcontroller we're working with, which has about 200 KB of RAM and 1.25 MB of flash memory.
### What Makes This Project Unique?
OpenSSH, the most common choice for implementing SSH, has a lot of bloat and would use too much memory. We don't need all of the features it provides, and we don't need to support a myriad of protocols and encryption algorithms. We need bare-bones SSH functionality and nothing else.
Lightweight SSH libraries like Dropbear exist, but they can't run on a microcontroller with no operating system. This project will draw heavily from Dropbear's implementation (a lot of the internals will almost certainly be from Dropbear), but we'll be adapting the networking sections to work with lwIP (our IP/TCP stack). We'll also probably have to change the server into a sort of state machine, where we do little chunks of work at a time to not lock up the CPU.
## Microcontroller Basics
### What is EMAC?
EMAC stands for **Ethernet Media Access Controller**. It is a hardware component responsible for handling the physical layer (PHY) and data link layer (MAC) of Ethernet communication. The physical layer means it handles the "physical" aspects of communication, like converting data into signals that can travel through an Ethernet cable. Since we're using TCP/IP, the data link layer is essentially contained within the physical layer. It checks for errors and handles tasks like addressing and collision avoidance.

Our microcontroller has an EMAC module which allows it to connect to an Ethernet network.
### What are Interrupts?
(Go over basic definition and why we're avoiding them)

## Loop Structure
### Checking the Network
### Checking for Packets
### Callback Functions
### Checking Timeouts
### SSH

## Walking Through the Program
### Packet Arrives
### Processing Packets
### State Machine
