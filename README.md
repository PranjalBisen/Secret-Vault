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