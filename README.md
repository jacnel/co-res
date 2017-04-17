# co-res

This is a study on co-residency attacks in the cloud and the ability for Bracketized VM image to detect these exploits.
Our goal is three fold:

1. Establish that memory bus locking while co-resident degrades performance
2. Discover ability of "Bracketed" VM diskimage to detect QoS attack through membus locking
3. Provide potential strategies to mitigate exploit

# Initial Setup

To begin, we setup two Ubuntu VM's, running on VirtualBox, on a single machine in Lehigh University's Sandbox Lab. 
A program that locks the memory bus through atomic operations on unaligned addresses, which access memory spanning 
more than one cache line, is resident on our target VM. The attacker contains another program that attempts to read from memory
and monitors the performance. This is an operation garunteed to lock the memory bus for the Intel x86 architecture.

The intent is to detect coresidency through performance degredation, which also provides proof for QoS attacks.

Steps

1. Measure performance of reads to memory without memory locking
2. Begin locking memory and record performance degredation

# Bracketized Images

The next iteration will follow the same procedure, but using a Bracketized VM instead of default images. This step
aims to understand, if and how QoS attacks are monitored and recorded in a Bracketized instance. The expectation is
that there will be some view of the repeated memory reads. If Bracket is able to detect this anomylous behavior, then
it is possible to raise some warning when it is happening.

# Suggested Recourse

In the current stage of this project we have not seen how Bracket can detect QoS attacks, so there is little to suggest.
However, intuition guides us to blieve that through careful monitoring and evaluation of memory accesses, Bracket
would be capable of raising some kind of warning. Although the overhead is high, there is research being done to reduce
the cost of live migration, which would be a suitable response to such an attack.