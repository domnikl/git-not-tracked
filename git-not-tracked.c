//#include <git2.h>
#include <stdio.h>
#include <stdlib.h>

#include "/usr/include/git2.h"

int main(int argc, char *argv[])
{
	git_libgit2_init();

	printf("Hello, world!\n");

	git_libgit2_shutdown();

	return 0;
}

/*git_buf root = {0};
int error = git_repository_discover(&root, "/tmp/…", 0, NULL);



int error = git_repository_open();
git_repository *repo = NULL;
int error = git_repository_open(&repo, ".");
if (error < 0) {
  const git_error *e = giterr_last();
  printf("Error %d/%d: %s\n", error, e->klass, e->message);
  exit(error);
}

	git_libgit2_shutdown();

	return 0;
}

char* git_repository_root()
{

}*/