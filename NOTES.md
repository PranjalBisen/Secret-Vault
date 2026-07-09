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

Phase IV: Vault Persistence

This one felt like a real milestone honestly.

Before this phase, every time I closed the program, everything was gone.
The .dat file had the data but the BST was built fresh every time.
Kinda defeated the whole purpose of a vault.

So now the program checks if a vault already exists before blindly creating one.
If it finds the .dat file, it reads every record one by one, skips the deleted ones,
and rebuilds the entire BST from scratch.

The beautiful part is how simple read_next_record() turned out to be,
literally a one liner that just does file.read() and returns.
No printing, no seeking, nothing extra. Just read and return.

Now I can insert stuff, close the program, come back, and search works.
That felt really really good.


Phase V: Soft Delete

This was actually smaller than Phase IV but something about it felt important.

The idea is simple, don't physically remove records from the .dat file.
Just mark them as deleted. The record stays, is_deleted becomes true.

Wrote soft_delete_record() which opens the file, seeks to the offset,
reads the record, flips is_deleted to true, seeks back, writes it back.
Returning bool from it was a nice touch, keeps the vault layer clean
with success/failure messages.

The sneaky part was modifying search. BST can still find deleted entries
because we don't touch the BST at all. So now search reads the actual
record from .dat and checks is_deleted before printing. Stale BST entries
get treated as not found. This is actually how real storage engines behave.

Also finally switched from cin>> to getline() so names with spaces work now.
Had to add cin.ignore() before every getline to eat the leftover newline
from cin>>choose. Classic C++ gotcha that got me good initially.

Rebuild already skipped deleted records from Phase IV so nothing to change there.
That felt satisfying, past me was looking out for future me.


Phase VI: Authorization

This is where the project started feeling real.

Before this, anyone could open any vault just by typing the name.
That's not a vault, that's a folder with extra steps.

So now when you create a new vault it asks for a password, hashes it
using our own polynomial rolling hash, and stores the hash inside a .meta file.
Not inside the .dat, because .dat stores records and .meta stores vault info.
Exactly how real databases separate metadata from data.

The beautiful part is I didn't use SHA256 or OpenSSL or bcrypt or any external lib.
I used the same polynomial rolling hash I wrote in Phase I for bloom filter.
That hash function finally has two jobs now.

To make that work I had to extract all the hash functions out of
secret_bloom_filter.cpp and put them in a shared secret_hash_utils.cpp.
Now both bloom filter and auth import from the same place, zero duplicate code.

Also wrote hash_polynomial_raw() which is the same polynomial rolling hash
but returns the full ll value without modding by array size. Because for password
hashing we want the actual hash value not a bucket index. Small difference,
but it matters.

Wrong password? Get outta here. Right password? Welcome back bruv.


Phase VII: Bloom Filter Integration

This might be my favourite phase because it made everything click.

Before this, bloom filter was just sitting there doing nothing.
I built it in Phase I, learned all about it, and then it just existed.
Now it has an actual job.

Insert flow now goes through bloom first. If bloom says definitely not present
we skip straight to insert, no BST search needed. If bloom says maybe present
then we check BST to confirm. If actually duplicate, reject. This is exactly
how production systems reduce unnecessary index lookups.

Search does the same thing. Bloom says definitely not present? Return immediately.
Don't even touch BST. Bloom says maybe? Then go through BST and .dat as usual.

Delete doesn't touch bloom at all. Because bloom filters can't delete.
That's why counting bloom filters exist. But we don't need that here.
Bloom can have stale entries after soft delete, and that's perfectly fine
because bloom filters are probabilistic by nature. 

The coolest part was the rebuild. When the vault restarts, we read every record
from .dat and in the same single pass we rebuild both BST and bloom filter.
One read, two structures rebuilt. That felt clean.

Now every component has a real job.
Metadata handles auth. Bloom handles fast negative lookups.
BST handles exact indexing. .dat handles persistent storage.
Everything has a purpose. Nothing is wasted.