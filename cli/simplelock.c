#include "simplelock.h"

void rwlock_init(struct rwlock *lock) {
	lock->write = 0;
	lock->read = 0;
}

void rwlock_rlock(struct rwlock *lock) {
	for (;;) {
		while(lock->write) {
			atom_sync();
		}
		atom_inc(&lock->read);
		if (lock->write) {
			atom_dec(&lock->read);
		} else {
			break;
		}
	}
}

void rwlock_wlock(struct rwlock *lock) {
	atom_spinlock(&lock->write);
	while(lock->read) {
		atom_sync();
	}
}

void rwlock_wunlock(struct rwlock *lock) {
	atom_spinunlock(&lock->write);
}

void rwlock_runlock(struct rwlock *lock) {
	atom_dec(&lock->read);
}
