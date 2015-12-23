#include <git2.h>
#include <stdio.h>
#include <stdlib.h>

void open_repository(git_repository *repo, char *path);
void find_repository_root(git_buf *root, char *path);
void exit_if_git_error_occured(int error);

int main(int argc, char *argv[])
{
	git_libgit2_init();

	git_repository *repo = NULL;
	open_repository(repo, ".");
	git_repository_free(repo);

	int i = 0;
	printf("Hello, world! %d\n", i);

	// TODO: read all branches

	// TODO: git_branch_upstream

	// cleanup libgit2
	git_libgit2_shutdown();

	return 0;
}

void open_repository(git_repository *repo, char *path)
{
	git_buf root = {0};
	find_repository_root(&root, path);
	int error = git_repository_open(&repo, root.ptr);
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