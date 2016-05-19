###(spoc1)请以键盘输入、到标准输出设备stdout的printf输出、串口输出、磁盘文件复制为例，描述ucore操作系统I/O从请求到完成的整个执行过程，并分析I/O过程的时间开销。
用户在按下键盘之后，会出发KBD中断，然后调用`trap.c`中的trap_dispatch函数处理中断，中断号为IRQ_KBD:
	
	 case IRQ_OFFSET + IRQ_KBD:
	        c = cons_getc();
	        //cprintf("kbd [%03d] %c\n", c, c);
	        {
	          extern void dev_stdin_write(char c);
	          dev_stdin_write(c);
	        }
	        break;

上述代码先通过cons_getc()从控制台获取输入字符串。之后调用了dev_stdin_write来处理输入的字符：
	
	bool intr_flag;
    if (c != '\0') {
        local_intr_save(intr_flag);
        {
            stdin_buffer[p_wpos % STDIN_BUFSIZE] = c;
            if (p_wpos - p_rpos < STDIN_BUFSIZE) {
                p_wpos ++;
            }
            if (!wait_queue_empty(wait_queue)) {
                wakeup_queue(wait_queue, WT_KBD, 1);
            }
        }
        local_intr_restore(intr_flag);
    }

上述代码首先屏蔽中断，然后将输入的字符存储在一个stdin_buffer的字符数组里。之后判断等待队列是否为空，非空则唤醒队列。

I/O的时间开销主要集中在进程切换过程中。