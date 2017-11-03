# co-res

This is a study on co-residency attacks in the cloud.

A complete write up is included in this repository. To get the full account of this project, please review that document.

# Initial Setup

To begin, we setup two Ubuntu VM's, running on VirtualBox, on a single machine in Lehigh University's Sandbox Lab. 
A program that locks the memory bus through atomic operations on unaligned addresses, which access memory spanning 
more than one cache line, is resident on our target VM. The attacker contains another program that attempts to read from memory
and monitors the performance. This is an operation garunteed to lock the memory bus for the Intel x86 architecture.

The intent is to detect coresidency through performance degredation, which also provides proof for QoS attacks.

Steps

1. Measure performance of reads to memory without memory locking
2. Begin locking memory and record performance degredation
