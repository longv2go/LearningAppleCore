// 这个文件来自 《MacOSX and iOS Internals: To the Apple`s Core》

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <stdio.h>


void main(int agrc, char ** argv)
{
	pid_t pid;
	int kq;
	int rc;
	int done;
	struct  kevent ke;

	pid = atoi(argv[1]);

	kq = kqueue();

	if (kq == -1) { perror("kqueue"); exit(2); }

	//设置进程fork 和 exec通知
	EV_SET(&ke, pid, EVFILT_PROC, EV_ADD, NOTE_EXIT | NOTE_FORK| NOTE_EXEC, 0 ,NULL);

	rc = kevent(kq, &ke, 1, NULL, 0, NULL);
	if (rc < 0) {perror("kevent"); exit(3); }

	done = 0;
	while(!done) {
		memset(&ke, '\0', sizeof(struct  kevent));

		//这个调用会阻塞，直到有一个符合过滤器的事件发生
		rc = kevent(kq, NULL, 0, &ke, 1, NULL);
		if (rc < 0) {perror("kevent"); exit(4); }

		if (ke.fflags & NOTE_FORK) 
			printf("PID %d fork()ed \n", ke.ident);

		if (ke.fflags & NOTE_EXEC)
			printf("pid %d has exec()ed\n", ke.ident);

		if (ke.fflags & NOTE_EXIT) {
			printf("pid %d has exited\n", ke.ident);
			done ++;
		}
	} // end while


}