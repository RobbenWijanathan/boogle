# 🧠 Boogle — A Trie-Powered Slang Dictionary (C)

> A fast, text-UI slang dictionary featuring add/search/list and **prefix-based lookup** — all backed by a compact **Trie** for efficient string storage and retrieval.

---

## 📘 Overview
**Boogle** is a console application written in C that acts as a slang dictionary.  
Users can add words with descriptions, search exact matches, list all entries, and discover words by **typing a prefix** and seeing live matches.  
The UI is fully keyboard-driven and optimized for speed.

---

## 🚀 Features
- ➕ **Insert** new slang terms with short descriptions (validated: lowercase, no spaces)
- 🔍 **Search** for words directly
- 📜 **List all** slang terms in alphabetical order
- ✨ **Prefix Search** – instantly show suggestions as you type
- 🧩 Built using a **Trie Data Structure** for fast lookups
- 💾 Lightweight & memory-efficient (pure C implementation)

---

## ⚙️ How It Works (Data Structure)
Each Trie node contains:
- `children[26]` → pointers for each lowercase alphabet
- `bool isEndOfWord` → marks the end of a valid word
- `char description[100]` → stores the slang definition

### Core Operations
| Operation | Description |
|------------|-------------|
| `insert(word, description)` | Inserts a slang term and saves its meaning |
| `search(word)` | Finds a slang term in the dictionary |
| `traverse(root)` | Displays all words & their meanings |
| `displayWordsByPrefix(prefix)` | Displays all slang terms starting with a given prefix |
---
