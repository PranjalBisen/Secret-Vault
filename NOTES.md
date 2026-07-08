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

