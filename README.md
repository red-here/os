SPPU TE IT Operating Systems Practicals — Easy C Programs
========================================================

Files:
1. address_book.sh       Shell address book (create/view/insert/delete/modify/exit)
2. fork_wait_sort.c      fork() and wait(); parent/child sorting demonstration
3. zombie_orphan.c       Demonstrates zombie and orphan process states
4. producer_consumer.c   Producer-consumer using pthreads, semaphores, and mutex
5. dining_philosophers.c Deadlock-avoiding dining philosophers using semaphores
6. bankers_algorithm.c   Banker's deadlock-avoidance algorithm
7. fifo_full_duplex.c   Two independent processes using two named FIFOs
8. pipe_file_parent_child.c Parent-child full-duplex pipes to send file contents
9. disk_scheduling.c     SSTF, SCAN, and C-LOOK disk scheduling

Compile/run on Linux. These are intentionally kept simple for practical exams.

Compile examples:
  gcc fork_wait_sort.c -o fork_wait_sort
  gcc zombie_orphan.c -o zombie_orphan
  gcc producer_consumer.c -o producer_consumer -pthread
  gcc dining_philosophers.c -o dining_philosophers -pthread
  gcc bankers_algorithm.c -o bankers_algorithm
  gcc fifo_full_duplex.c -o fifo_full_duplex
  gcc pipe_file_parent_child.c -o pipe_file_parent_child
  gcc disk_scheduling.c -o disk_scheduling

Run shell script:
  chmod +x address_book.sh
  ./address_book.sh

Notes:
- Run the FIFO program in one terminal; it creates two named pipes and forks/execs
  a second copy of itself as the reader process.
- For zombie_orphan, observe the printed PIDs and timing. Process-state observation
  depends on OS scheduling; use `ps -o pid,ppid,state,cmd -p PID` quickly if needed.
- The disk program assumes cylinders numbered 0..199 and that the initial head
  first moves toward higher cylinder numbers ("away from the spindle") for SCAN/C-LOOK.
