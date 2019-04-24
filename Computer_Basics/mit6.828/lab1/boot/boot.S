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

  # inb和outb是读取IO端口的数据，和in/out稍微有点不同，具体可以查看《linux设备驱动编程》
seta20.1:
  #  0x64是PS/2 Controller(键盘控制器804x)的一个I/O Port。
  # 这三条指令读取了0x64处的１byte数据，并不断测试该数据的bit 1是否为1。若为１则继续等待
  # bit1的值代表输入缓冲区是否满了，也就是说CPU传送给控制器的数据，控制器是否已经取走了，如果CPU想向控制器传送新的数据的话，必须先保证这一位为0。
  inb     $0x64,%al               # Wait for not busy
  testb   $0x2,%al
  jnz     seta20.1

  # 将数据0x60写入到0x64端口中,即代表像PS/2 Controller发送指令，这个指令将会被送给0x60端口。
  # D1指令代表下一次写入0x60端口的数据将被写入给804x控制器的输出端口。可以理解为下一个写入0x60端口的数据是一个控制指令
  movb    $0xd1,%al               # 0xd1 -> port 0x64
  outb    %al,$0x64


seta20.2:
  # 与seta20.1作用相同，等待端口空闲
  # 等待刚刚写入的指令D1，是否已经被读取了
  inb     $0x64,%al               # Wait for not busy
  testb   $0x2,%al
  jnz     seta20.2
 # 将0xdf写出到0x60, 再写出到 Output Port, 
 # 0xdf的含义是打开了A20 gate ，代表开始进入了保护模式
  movb    $0xdf,%al               # 0xdf -> port 0x60
  outb    %al,$0x60



# ################进入保护模式########################

  # Switch from real to protected mode, using a bootstrap GDT
  # and segment translation that makes virtual addresses 
  # identical to their physical addresses, so that the 
  # effective memory map does not change during the switch.
  lgdt    gdtdesc  # 把gdtdesc这个标识符的值送入全局映射描述符表寄存器GDTR中

  # 修改CR0寄存器的内容,将CR0寄存器的bit0置1。CR0~CR3寄存器都是80x86的控制寄存器
  # CR0寄存器的bit0是保护模式启动位，把这一位值1代表保护模式启动。
  movl    %cr0, %eax
  orl     $CR0_PE_ON, %eax # CR0_PE_ON定义在inc/mmu.h中值为0x00000001
  movl    %eax, %cr0
  
  # Jump to next instruction, but in 32-bit code segment.
  # Switches processor into 32-bit mode.
  ljmp    $PROT_MODE_CSEG, $protcseg　# 这条指令的目的在于把当前的运行模式切换成32位地址模式

  .code32                     # Assemble for 32-bit mode
protcseg:
  # Set up the protected-mode data segment registers 修改这些段寄存器的值
  movw    $PROT_MODE_DSEG, %ax    # Our data segment selector
  movw    %ax, %ds                # -> DS: Data Segment
  movw    %ax, %es                # -> ES: Extra Segment
  movw    %ax, %fs                # -> FS
  movw    %ax, %gs                # -> GS
  movw    %ax, %ss                # -> SS: Stack Segment
  
  # Set up the stack pointer and call into C.
  # 设置当前的esp寄存器的值，然后准备正式跳转到main.c文件中的bootmain函数处
  movl    $start, %esp
  call bootmain

  # If bootmain returns (it shouldn't), loop.
spin:
  jmp spin

# Bootstrap GDT
.p2align 2                                # force 4 byte alignment
gdt:
  SEG_NULL				# null seg
  SEG(STA_X|STA_R, 0x0, 0xffffffff)	# code seg  调用mmu.h中的SEG函数来构造GDT表
  SEG(STA_W, 0x0, 0xffffffff)	        # data seg

gdtdesc:
  .word   0x17                            # sizeof(gdt) - 1 =24-1=23=0x17
  .long   gdt                             # address gdt

