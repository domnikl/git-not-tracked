#include <git2.h>
#include <stdio.h>
#include <stdlib.h>

#include "libgit2-helper.h"

void open_repository(git_repository **repo, char *path)
{
	git_buf root = {0};
	find_repository_root(&root, path);
	int error = git_repository_open(repo, root.ptr);
	git_buf_free(&root);
	exit_if_git_error_occured(error);
}

void find_repository_root(git_buf *root, char *path)
{
	int error = git_repository_discover(root, path, 0, NULL);
	exit_if_git_error_occured(error);
}

void exit_if_git_error_occured(int error)
{
	if (error < 0) {
		const git_error *e = giterr_last();
		printf("Error %d/%d: %s\n", error, e->klass, e->message);
		exit(error);
	}
}
