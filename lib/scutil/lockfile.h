/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/*
 * Four routines to be able to lock access to a file in the Linux
 * approved manner.  This seems to be the only method that works
 * over NFS:
 *
 *  __pg_make_lock_file()
 *	Creates a uniquely-named file in the current directory.
 *	To work, this must be created on the same filesystem
 *	as the file which we are attempting to lock.
 *	If there are multiple processes running each competing for the
 *	same lock, each gets a unique file here.
 *  __pg_get_lock( char* lname )
 *	The argument is the name of the lock.
 *	Each process tries to create a hard link with this name
 *	to its own uniquely-named file from __pg_make_lock_file().
 *	The one that succeeds is the new lock owner.  The others
 *	fail and try again.  There is a fail-over to handle the case
 *	where the process with the lock dies, which is inherently unsafe,
 *	but we haven't come up with a better solution.
 *  __pg_release_lock( char* lname )
 *	The argument is the same name for the lock.
 *	The lock is released by deleting (calling unlink) for the
 *	hard link we had just created.
 *  __pg_delete_lock_file()
 *	Clean up by deleting the uniquely named file we had created earlier.
 *  These routines only allow one lock to be managed at a time.
 *  They dynamically allocate and free memory.
 */

extern int __pg_make_lock_file(char *dir);
extern void __pg_get_lock(char *lname);
extern void __pg_release_lock(char *lname);
extern void __pg_delete_lock_file(void);
