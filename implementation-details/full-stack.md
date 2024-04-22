# Overview
## Introduction
The goal of this section is eventually explain exactly how our project works from a high level. This document should be readable to someone with very little technical experience.
## Our Objective
We want to create a SSH server that will function on a microcontroller with only one CPU thread and not much memory. 
## Microcontroller Basics
### What is EMAC?
EMAC stands for **Ethernet Media Access Controller**. It is a hardware component responsible for handling the physical layer (PHY) and data link layer (MAC) of Ethernet communication. The physical layer means it handles the "physical" aspects of communication, like converting data into signals that can travel through an Ethernet cable. Since we're using TCP/IP, the data link layer is essentially contained within the physical layer. It checks for errors and handles tasks like addressing and collision avoidance.

Our microcontroller has an EMAC module which allows it to connect to an Ethernet network.
### What are Interrupts?
