#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

class splice {
    private:
	size_t len;
	char *sentence;

	void setword_list(char *);

    public:
	char **word_list;

	splice(char *s)
	{
		len = std::strlen(s);
		sentence = static_cast<char *>(
			std::malloc(sizeof(char) * (len + 1)));
		std::strcpy(sentence, s);
		setword_list(s);
	}

	char *getsentence()
	{
		return sentence;
	}
};

void splice::setword_list(char *s)
{
	char **cArr = static_cast<char **>(std::malloc(sizeof(char *)));
	char **move = cArr;
	*move++ = static_cast<char *>(std::malloc(sizeof(char) * 4));
	int count = 0;
	for (char *split = std::strtok(s, " "); split;
	     split = std::strtok(NULL, " ")) {
		*move = static_cast<char *>(
			std::malloc(sizeof(char) * (strlen(split) + 1)));
		std::strcpy(*move, split);
		move++;
		count++;
	}

	std::strcpy(*cArr, std::to_string(count).c_str());
	this->word_list = cArr;
}

char *fget_string(FILE *fp)
{
	/* Preliminary check */
	if (!fp || feof(fp))
		return NULL;

	enum { initial, updated };
	int size = 128;
	char *pp[2];
	char *p = static_cast<char *>(std::malloc(size));
	pp[initial] = p;

	int c;
	while ((c = fgetc(fp)) != EOF && (*p++ = c) != '\n') {
		if ((p - pp[initial]) >= size) {
			size += size;
			pp[updated] = static_cast<char *>(
				std::malloc(sizeof(char) * size));
			memcpy(pp[updated], pp[initial], (p - *pp));
			p = pp[updated] + (p - pp[initial]);
			free(pp[initial]);
			pp[initial] = pp[updated];
		}
	}
	*p = '\0';
	return *pp;
}

int main(int argc, char *argv[])
{
	FILE *fp = argv[1] ? fopen(argv[1], "r") : stdin;
	char *buf = fget_string(fp);
	splice bar(buf);

	std::printf("Input was %s\n", bar.getsentence());
	std::printf("Number of words is %s", *bar.word_list);

	return 0;
}
