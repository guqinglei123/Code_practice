#include <inc/mmu.h>

# Start the CPU: switch to 32-bit protected mode, jump into C.
# The BIOS loads this code from the first sector of the hard disk into
# memory at physical address 0x7c00 and starts executing in real mode
# with %cs=0 %ip=7c00.
# .set 相当于 #define，用于设置常量
.set PROT_MODE_CSEG, 0x8         # kernel code segment selector
.set PROT_MODE_DSEG, 0x10        # kernel data segment selector
.set CR0_PE_ON,      0x1         # protected mode enable flag

# .globl使得连接程序(ld)能够看到start。
# 作用是使得同一文件夹的其他文件能引用start。
.globl start
start:
  .code16                     # Assemble for 16-bit mode
  cli                         # Disable interrupts　这条指令用于把所有的中断都关闭。因为在BIOS运行期间有可能打开了中断
  cld                         # String operations increment 指定之后发生的串处理操作的指针移动方向

  # Set up the important data segment registers (DS, ES, SS).
    # AX, DS, ES, SS 寄存器全部置0
  xorw    %ax,%ax             # Segment number zero
  movw    %ax,%ds             # -> Data Segment
  movw    %ax,%es             # -> Extra Segment
  movw    %ax,%ss             # -> Stack Segment

  # Enable A20:
  #   For backwards compatibility with the earliest PCs, physical
  #   address line 20 is tied low, so that addresses higher than
  #   1MB wrap around to zero by default.  This code undoes this.

  # 从PS/2 Controller的I/O Port读取一个byte
  # **** **1* 表示忙, 所以用0x2作test运算
  # 若test结果不为0, jnz跳转回函数起点
seta20.1:
  inb     $0x64,%al               # Wait for not busy  0x64端口属于键盘控制器804x
  testb   $0x2,%al
  jnz     seta20.1

# 通知PS/2 Controller，将下一个写入0x60的字节写出到 Output Port
  movb    $0xd1,%al               # 0xd1 -> port 0x64
  outb    %al,$0x64

  # 与seta20.1作用相同，等待端口空闲
seta20.2:
  inb     $0x64,%al               # Wait for not busy
  testb   $0x2,%al
  jnz     seta20.2
 # 将0xdf写出到0x60, 再写出到 Output Port, 打开了A20 gate 
  movb    $0xdf,%al               # 0xdf -> port 0x60
  outb    %al,$0x60

  # Switch from real to protected mode, using a bootstrap GDT
  # and segment translation that makes virtual addresses 
  # identical to their physical addresses, so that the 
  # effective memory map does not change during the switch.
  lgdt    gdtdesc
  movl    %cr0, %eax
  orl     $CR0_PE_ON, %eax
  movl    %eax, %cr0
  
  # Jump to next instruction, but in 32-bit code segment.
  # Switches processor into 32-bit mode.
  ljmp    $PROT_MODE_CSEG, $protcseg

  .code32                     # Assemble for 32-bit mode
protcseg:
  # Set up the protected-mode data segment registers
  movw    $PROT_MODE_DSEG, %ax    # Our data segment selector
  movw    %ax, %ds                # -> DS: Data Segment
  movw    %ax, %es                # -> ES: Extra Segment
  movw    %ax, %fs                # -> FS
  movw    %ax, %gs                # -> GS
  movw    %ax, %ss                # -> SS: Stack Segment
  
  # Set up the stack pointer and call into C.
  movl    $start, %esp
  call bootmain

  # If bootmain returns (it shouldn't), loop.
spin:
  jmp spin

# Bootstrap GDT
.p2align 2                                # force 4 byte alignment
gdt:
  SEG_NULL				# null seg
  SEG(STA_X|STA_R, 0x0, 0xffffffff)	# code seg
  SEG(STA_W, 0x0, 0xffffffff)	        # data seg

gdtdesc:
  .word   0x17                            # sizeof(gdt) - 1
  .long   gdt                             # address gdt

