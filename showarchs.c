//
//  main.c

#include <stdio.h>
#include <mach-o/arch.h>

const char *ByteOrder(enum NXByteOrder bo)
{
    switch (bo) {
        case NX_LittleEndian:
            return "Little-Endian";
            break;
        case NX_BigEndian:
            return "Big-Endian";
            break;
        case NX_UnknownByteOrder:
            return "unknow-Endian";
        default:
            return "!?!";
            break;
    }
}

int main(int argc, const char * argv[]) {
    const NXArchInfo *local = NXGetLocalArchInfo();
    const NXArchInfo *known = NXGetAllArchInfos();
    
    while (known && known->description) {
        printf("Know: %s\t%x/%x\t%s\n", known->description,
               known->cputype, known->cpusubtype, ByteOrder(known->byteorder));
        
        known++;
    }
    
    if (local) {
        printf("Local: %s\t%x/%x\t%s\n", local->description,
               local->cputype, local->cpusubtype, ByteOrder(local->byteorder));

    }
    
    return 0;
}
