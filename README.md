# Boogle — A Trie-Powered Slang Dictionary (C)

Boogle is a text-based slang dictionary written in C. It supports adding terms, searching, listing entries, and performing prefix-based lookups. All operations are implemented using a Trie for efficient string storage and retrieval.

## Overview
Users can insert slang words with descriptions, search for exact matches, list all words alphabetically, and retrieve suggestions based on a typed prefix. The interface is fully text-based and keyboard-driven.

## Features
- Insert new slang terms with descriptions  
- Search for existing terms  
- List all terms  
- Prefix-based lookup  
- Implemented with a Trie data structure  

## Data Structure
Each Trie node contains:
- `children[26]` for lowercase letters  
- `isEndOfWord` flag  
- `description[100]` for storing definitions  

### Core Operations
| Operation | Description |
|----------|-------------|
| `insert(word, description)` | Adds a slang term and its meaning |
| `search(word)` | Looks up a term |
| `traverse(root)` | Lists all terms |
| `displayWordsByPrefix(prefix)` | Lists all terms beginning with a prefix |
