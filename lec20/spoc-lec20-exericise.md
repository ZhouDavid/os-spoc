在lab7-answer中分析：

1.cvp->count含义是什么？cvp->count是否可能<0, 是否可能>1？请举例或说明原因。

	cvp->count的含义是等待条件变量的进程数。
	cvp->count不可能<0，因为cond_wait函数中对cvp->count的操作都是先加一、后减一，所以不论中间是否被打断，都不可能出现<0的情况。
	cvp->count可能>1，可能多个进程等待同一个条件变量。
	cvp->owner->next_count含义是什么？cvp->owner->next_count是否可能<0, 是否可能>1？请举例或说明原因。

2.owner表示条件变量cvp的宿主是哪个管程，next_count表示了由于发出singal_cv而睡眠的进程个数。

	cvp->owner->next_count不可能<0，理由和上一题是一样的，所有操作都是先加后减。
	cvp->owner->next_count不可能>1，因为当进程A执行signal唤醒进程B，A睡眠，进程B结束后先唤醒A，next_count减一。

2.目前的lab7-answer中管程的实现是Hansen管程类型还是Hoare管程类型？请在lab7-answer中实现另外一种类型的管程。

	Hoare类型