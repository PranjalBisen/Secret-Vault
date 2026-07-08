## Current Features

### Bloom Filter

- Bloom Filter using `vector<bool>`
- Four independent hash functions
  - ASCII Hash
  - Polynomial Rolling Hash
  - DJB2
  - Jenkins One-at-a-Time
- Insert
- Lookup
- Duplicate detection (Bloom Filter only)

### Binary Storage Engine

- Binary `.dat` file creation
- Fixed-size `SecretRecord` storage
- Binary serialization using `fstream`
- Append records
- Read complete data file
- Read record using record number
- Read record using byte offset
- `tellg()`, `tellp()`
- `seekg()`
- Soft delete flag support