1048576 

256*64


[Header principal][Header secondaire][Bloc mem][Header secondaire][Bloc mem]


[Header principal]
- size_t    size    En fonction de la taille je sais le nb de bloc dans l'allocation
- void *    next;
16 octets 8 + 8 

[Header secondaire]
- uint_8    free;
- char *    head;