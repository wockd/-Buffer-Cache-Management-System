Project Overview: Buffer Cache Management System

This project is a Buffer Cache Management System developed as part of an operating systems assignment. It is based on the files buf.c and buf.h, and implements buffer cache functionality to manage disk blocks efficiently and handle read/write requests. The system maintains cache buffers in memory and leverages policies like LRU for efficient data access.

Key Features:

Buffer Initialization (BufInit): Initializes buffer lists and state lists to set up the cache system. Uses a hash table to support fast block lookup.

Block Read (BufRead): Checks the cache for the requested block number and, if not found, reads it from the disk and stores it in the cache. If the block already exists, it returns the data from the cache directly.

Block Write (BufWrite): Records data in the cache and marks it as Dirty. Later, the Dirty data can be synchronized to the disk as needed.

Cache Synchronization (BufSync): Synchronizes Dirty data with the disk to maintain data consistency. This functionality is currently not implemented but is needed.

Buffer Lookup (BufGet): Checks the cache for the requested block number and returns the corresponding buffer if found.

Data Structures:

Buf Struct: Represents each buffer block, containing information like block number, state (DIRTY, CLEAN), memory pointer, etc.

Hash List (ppBufList): A hash table for fast buffer lookup.

State List (ppStateListHead): Manages buffers by their state, either Dirty or Clean.

LRU List (pLruListHead): Manages buffers based on usage frequency using an LRU policy.

Areas for Improvement and Further Implementation:

Implement synchronization functionality like BufSync to ensure data consistency.

Improve memory allocation and error handling to enhance system stability.

Refine the LRU policy implementation to improve cache management efficiency.

This project is a valuable exercise for understanding and implementing the concept of buffer caching in operating systems. Each function in the code aims to reduce disk I/O costs and enable efficient data access
