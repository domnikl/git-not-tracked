#include <git2.h>
#include <stdio.h>
#include <stdlib.h>

#include "libgit2-helper.h"

int main(int argc, char *argv[])
{
	git_libgit2_init();

	git_repository *repo;
	open_repository(&repo, ".");

	unsigned int i = 0;
	char out[GIT_OID_HEXSZ + 1];
  	out[GIT_OID_HEXSZ] = '\0';
	git_strarray ref_list;
  	git_reference_list(&ref_list, repo);
  	
  	char branch_name_buffer[1024];
  	const char *branch_name;
	branch_name = (const char*) &branch_name_buffer;

  	const char *refname;
  	git_reference *ref;
  	git_reference *upstream;

  	for (i = 0; i < ref_list.count; ++i) {
	    refname = ref_list.strings[i];
	    git_reference_lookup(&ref, repo, refname);

	    switch (git_reference_type(ref)) {
	    case GIT_REF_OID:
	    	if (git_reference_is_branch(ref)) {
				if (git_branch_upstream(&upstream, ref) == GIT_ENOTFOUND) {
		      		git_oid_fmt(out, git_reference_target(ref));
		      		git_branch_name(&branch_name, ref);
		      		printf("%s\n", branch_name);
				}
	    	}
	      break;
	    case GIT_REF_SYMBOLIC:
	      // do not consider symbolic references
	      break;
	    default:
	      fprintf(stderr, "Unexpected reference type\n");
	      exit(1);
	    }

	    git_reference_free(ref);
	}

	git_reference_free(upstream);
	git_strarray_free(&ref_list);
	git_repository_free(repo);

	// cleanup libgit2
	git_libgit2_shutdown();

	return 0;
}
