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
- Fast negative lookups before BST search
- Bloom Filter may contain stale entries after soft delete. This is acceptable because Bloom Filters are probabilistic.

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

### Binary Search Tree Index

- Custom BST implementation
- Create BST node
- Recursive insertion
- Recursive search
- Inorder traversal
- Preorder traversal
- Postorder traversal
- Offset-based indexing

### Storage Engine Integration

- Binary storage integrated with BST index
- Offset returned after record insertion
- Offset stored inside BST nodes
- O(log n) lookup through BST
- Offset-based record retrieval from binary file
- Interactive CLI menu

### Vault Persistence

- Vault file existence check before creation
- BST rebuild from existing `.dat` file on startup
- Sequential record reading using `read_next_record()`
- Skips deleted records during rebuild
- No data loss between sessions

### Soft Delete

- `soft_delete_record()` marks record as deleted in `.dat`
- Record stays physically, `is_deleted` flag set to `true`
- Search validates record from `.dat` before printing
- Stale BST entries treated as not found
- `read_all_dat_file()` skips deleted records
- Deletion persists across restarts
- `getline()` support for multi-word input

### Shared Hash Utilities

- Hash functions extracted into `secret_hash_utils.cpp`
- Shared by Bloom Filter and Authorization
- `hash_polynomial_raw()` for full hash without bucket modding
- No duplicate code across modules

### Authorization

- `VaultMetadata` struct stores password hash in `.meta` file
- Password hashed using own polynomial rolling hash
- No SHA256, no OpenSSL, no bcrypt
- New vault asks user to set password
- Existing vault verifies password before opening
- Metadata stored separately from record data

### Bloom Filter Integration

- Insert checks Bloom first, then BST for actual duplicates
- Search checks Bloom first, skips BST if definitely not present
- Delete does not remove from Bloom (Bloom Filters can't delete)
- Bloom Filter rebuilt alongside BST on startup in single pass
- Reduces unnecessary index lookups