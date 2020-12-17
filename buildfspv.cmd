BuildFsp.py build -p qemu -a ia32

move "C:\code\fspsdk\fspsdk\BuildFsp\*" "C:\code\fspsdk\slimbootloader\Silicon\QemuSocPkg\FspBin\"


del "C:\code\fspsdk\slimbootloader\Silicon\QemuSocPkg\FspBin\Fsp.bsf"
del "C:\code\fspsdk\slimbootloader\Silicon\QemuSocPkg\FspBin\FspDbg.bin"
ren "C:\code\fspsdk\slimbootloader\Silicon\QemuSocPkg\FspBin\QEMU_FSP.bsf" "Fsp.bsf"
ren "C:\code\fspsdk\slimbootloader\Silicon\QemuSocPkg\FspBin\QEMU_FSP_DEBUG.fd" "FspDbg.bin"