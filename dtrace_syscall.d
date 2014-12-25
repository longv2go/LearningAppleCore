#pragma D option flowindent
syscall::open:entry
{
	self->tracing = 1; /*现在开始跟踪一切*/
	printf("file at: %x opened with mode %x", arg0, arg1);
}

fbt:::entry
/ self->tracing /
{
	printf("%x, %x, %x", arg0, arg1, arg2); /*打印参数*/
}

fbt::open:entry
/ self->tracing /
{
	printf("PID %d (%s) is opening \n", ((proc_t)arg0)->p_pid, ((proc_t)arg0)->p_comm);
}

fbt:::return
/ self->tracing /
{
	printf("Returned %x\n", arg1);
}

syscall::open:return
/ self->tracing /
{
	self->tracing = 0;
	exit(1);
}