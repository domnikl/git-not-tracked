/**
 * opens the repository at path
 */
void open_repository(git_repository **repo, char *path);

/**
 * finds the repository root. access it with `root.ptr`
 */
void find_repository_root(git_buf *root, char *path);

/**
 * exit if there was a git error, prints the error to STDERR
 */
void exit_if_git_error_occured(int error);
