from ghidra.program.model.mem import MemoryAccessException

memory = currentProgram.getMemory()
listing = currentProgram.getListing()
addr_factory = currentProgram.getAddressFactory()

pattern = [0xFF, 0x90, 0xB8, 0x07, 0x00, 0x00]
start = addr_factory.getAddress("0x140000000")
end   = addr_factory.getAddress("0x141FFFFFF")

addr = memory.findBytes(start, end, bytes(pattern), None, True, monitor)
while addr:
    print("vtable+0x7b8 call at: 0x{:X}".format(int(str(addr), 16)))
    addr = memory.findBytes(addr.add(1), end, bytes(pattern), None, True, monitor)
