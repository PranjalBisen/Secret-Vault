Phase I: Bloom Filter Implementation

Learned a lot about Bloom Filters, their use case, how they are implemented.

Learned and Implemented these 4 beautiful hash function:
    - sum of all ascii chars
    - polynomial rolling hash
    - DJB2 
    - Jenkins-one-at-a-time 

Like a total noob i forgot about negative number while mod and 
later added the (x%n+n)%n to tackle that. 

Also initially i used pow(power,i) in the polynomial hash, but later realised that it return double instead of int so had to manually write power func to correct it.


Phase II: Binary File Handling

Boy was this phase tough, okay not tough but something new and something I haven't touched in a while.

Initially my mindset was, maybe the BST will store stuff or maybe the .dat file stores the actual data.

Learned a lot in this tbh, literally from why we serialize record in .dat
to doing it all by myself, playing around with offset pointers discovering 
records vs offset reading, and just a lot about appending, creating, reading.

Also loved the concept of ios::binary, ios::in, ios::out, ios::app, and 
how storing a fixed size record beautifully optimizes random access of records.


Phase III: Storage Engine Integration

Initially both modules worked independently.

Binary Storage knew nothing about BST.

BST knew nothing about .dat.

The biggest learning in this phase was connecting multiple independent modules
into a complete storage engine.

Now the broken pieces have come together, looking beautiful nonetheless