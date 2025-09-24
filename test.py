memory_bloc = 16 + 128
header_main = 16
size = header_main + memory_bloc

print("TINY :")
for i in range(0,1000):
    if (size) % 4096 == 0:
        print(f"{size} = {(size) / 4096} pages and {(size - header_main) / memory_bloc} blocs")
    size += memory_bloc


memory_bloc = 16 + 1024
header_main = 16
size = header_main + memory_bloc

print("TINY :")
for i in range(0,1000):
    if (size) % 4096 == 0:
        print(f"{size} = {(size) / 4096} pages and {(size - header_main) / memory_bloc} blocs")
    size += memory_bloc


