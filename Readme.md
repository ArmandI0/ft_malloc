```
cc mon_programme.c -o mon_programme -L. -lft_malloc
➜  ft_malloc git:(main) ✗ /usr/bin/time -v ./test0

```
```
    export LD_PRELOAD=./libft_malloc.so
```
[Header principal][Header secondaire][Bloc mem][Header secondaire][Bloc mem]


(28672 - 16 ) / 144 = 199 page
TINY malloc = 128
[Header principal][Header secondaire][Bloc mem][Header secondaire][Bloc mem]
[16octets][16octets][128octets][16octets][128octets]


SMALL malloc = 1024
[Header principal][Header secondaire][Bloc mem][Header secondaire][Bloc mem]
[16octets][16octets][1024octets][16octets][1024octets]

SMALL bloc + header = 1024 + 16 = 1040

Si j'alloue 146 page ca fait 598016 octets
- Moins le header principal 598000

1024 * 1024 = 1048576 taille du test
taille total des header = 146 * 16 = 2336
575 bloc de  1024 dispo

➜  ft_malloc_42School git:(main) ✗ python test.py
TINY :
28672 = 7.0 pages and 199.0 blocs
65536 = 16.0 pages and 455.0 blocs
102400 = 25.0 pages and 711.0 blocs
139264 = 34.0 pages and 967.0 blocs

SMALL :
65536 = 16.0 pages and 63.0 blocs
331776 = 81.0 pages and 319.0 blocs
598016 = 146.0 pages and 575.0 blocs
864256 = 211.0 pages and 831.0 blocs
