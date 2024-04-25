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
Interrupts are essential to how microcontrollers function. They are a mechanism used to temporarily halt the normal flow of program execution in response to an event or condition. These events are often hardware signals, like the completion of a data transfer or the press of a button. When an interrupt occurs, the processor stops whatever it was doing before and switches to an interrupt service routine (ISR), also called an interrupt handler. Once the ISR completes its tasks, the processor resumes whatever it was doing before.

However, because this implementation is being designed for a context in which timing is crucial, we can't afford to have our main event loop being constantly interrupted. We can't avoid them completely due to the hardware of our board, but we are exclusively using the interrupts needed to write data from our EMAC module into main memory.

## Loop Structure
Here, I'll give a rough overview of what our main event loop will look like. This section will be a little more technical by nature of the topic matter.
### Checking the Network
Before we do anything else, we need to check our link state (make sure that our network connection is still up). The actual check will involve communication with our ethernet module via the MDIO bus, and if the link status has changed, we'll update our network interface (netif) struct.
### Checking for Packets
This is something we're still working on. Our EMAC module stores packet buffer descriptors in a circular buffer of length 10. Each descriptor points to the next, and we can follow them until we reach a NULL pointer to form a primitive version of packet detection. However, this approach could result in us being overwhelmed if we are likely to ever receive more than 10 packets in the time between packet checks. This also seems like it would result in a security vulnerability. We're pretty sure there's another approach using particular registers that work, and we're researching that now.
### Callback Functions
See this [short guide to callback functions](https://github.com/jgoldberger26/baressh-rcos-docs/blob/main/implementation-details/callback-functions.md) if you are unfamiliar. We'll eventually add explainations for our callback functions in the same place once we've tested them.
When we detect an incoming packet in the previous step, we will alert lwIP, and lwIP will call our callback functions. These are essentially are replacement for interrupts. These do the work that interrupts would normally do, but we can control when we call them.
### Checking Timeouts
Next, we'll check our assorted timeout timers. This means timers like our connection timeout: if the client doesn't establish the connection during a particular time frame, we close the connection to free ip resources. There's additional timers for authentication, idling, and a session time limit.
### SSH
After all this, we can start actually running our application. Details about our decisions for our implementation of SSH will eventually be added [here](https://github.com/jgoldberger26/baressh-rcos-docs/tree/main/SSH-basics).

## Walking Through the Program
### Packet Arrives
### Processing Packets
### State Machine
