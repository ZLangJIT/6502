#ifndef SIMPLE_THREAD_H
#define SIMPLE_THREAD_H

struct thread {
	void (*func)(void *);
	void *ud;
};

struct thread_event;

void thread_join(struct thread * threads, int n);
void thread_event_create(struct thread_event *ev);
void thread_event_release(struct thread_event *ev);
void thread_event_trigger(struct thread_event *ev);
void thread_event_wait(struct thread_event *ev);

#endif
