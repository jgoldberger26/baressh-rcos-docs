# Callback Functions
Because we are trying to avoid using system-wide interrupts (besides the ones necessary for the EMAC module to function) we’re using lwIP’s raw API. The raw API requires us to write callback functions. Callback functions are functions passed as an argument to another function so that they can be called later. In our case, we use callback functions to tell lwIP what to do whenever an event occurs. For example, we have functions that specify what to do when a new connection arrives, when new data arrives over the tcp connection, and when we send a packet. Whenever we detect an incoming packet, we notify lwIP, and lwIP will call the appropriate callback function based on the contents of the packet and the current state of our protocol control block.

The following link is an example of callback functions that result in the server echoing any packet it gets sent, except with the header modified. We will change this to our specific callback functions once we've tested them.

[Echo Server](https://git.savannah.nongnu.org/cgit/lwip/lwip-contrib.git/tree/apps/tcpecho_raw)

[lwIP Raw API Documentation](https://lwip.fandom.com/wiki/Raw/TCP)
