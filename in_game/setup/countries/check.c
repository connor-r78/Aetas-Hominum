#include <dirent.h>
#include <stdio.h>
#include <string.h>

int findTag(char *tag, char *countryfileName) 
{
	char mutatedTag[5];
  snprintf(mutatedTag, sizeof(mutatedTag), "%s =", tag);

	FILE *countryfile;
	countryfile = fopen(countryfileName, "r");

	char readString[100];
	while ( fgets(readString, 100, countryfile) ) {
		if ( strstr(readString, mutatedTag) ) return 1;
	}

	fclose(countryfile);

	return 0;
}

int main(int argc, char *argv[])
{
  if ( argc == 2 && strlen(argv[1]) == 3 ) {
		DIR *countries;
		struct dirent *dir;

		int found = 0;

		countries = opendir("./");
		if (!countries) return 2;

		while ( (dir = readdir(countries)) ) {
			if ( strstr(dir->d_name, ".txt") && findTag(argv[1], dir->d_name) ) {
				printf("%s is already in use.\n", argv[1]);
				found = 1;
			}
		}

		closedir(countries);
		if(!found) printf("%s is safe to use.\n", argv[1]);
		return 0;
  }
  else {
		printf("Usage: ./check TAG\n");
		return 1;
  }
}