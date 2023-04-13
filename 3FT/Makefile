#--------------------------------------------------------------------
# Author: Julian & Sid 
#--------------------------------------------------------------------

# Dependency rules for non-file targets
all: ft 
clobber: clean
    rm -f *~ \#*\#
clean:
    rm -f ft *.o

# Dependency rules for file targets
ft: dynarray.o nodeFT.o path.o ft.o ft_client.o
    gcc217 -g dynarray.o nodeFT.o path.o ft.o ft_client.o -o ft

ftclient_gdb: dynarray.o nodeFT.o path.o ft.o ft_client.o
    gcc217 -g dynarray.o nodeFT.o path.o ft.o ft_client.o -o ftclient_gdb

dynarray.o: dynarray.c dynarray.h
    gcc217 -c -g dynarray.c 
nodeFT.o: nodeFT.c nodeFT.h dynarray.h path.h a4def.h
    gcc217 -c -g nodeFT.c
path.o: path.c path.h dynarray.h a4def.h
    gcc217 -c -g path.c 
ft.o: ft.c ft.h nodeFT.h dynarray.h path.h a4def.h
    gcc217 -c -g ft.c
ft_client.o: ft_client.c ft.h a4def.h
    gcc217 -c -g ft_client.c