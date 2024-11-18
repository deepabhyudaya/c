+-----------------------+ <- High memory
| Stack | (Local variables, function calls)
+-----------------------+
| Heap | (Dynamic allocations via malloc/calloc)
+-----------------------+
| Uninitialized Data | (BSS: global/static uninitialized vars)
+-----------------------+
| Initialized Data | (Global/static initialized vars)
+-----------------------+
| Text | (Code segment: program instructions)
+-----------------------+ <- Low memory
