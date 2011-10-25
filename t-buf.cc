#include <errno.h>
#include <unistd.h>
#include <simple.h>
#include <scc.h>

	const size_t buf_size=1000;
	char* buf;

int readline(int fd, char *buf, int nbytes) {
	int     numread = 0;
	int     returnval;

	while (numread < nbytes - 1) {
		returnval = read(fd, buf + numread, 1);

		if ((returnval == -1) && (errno == EINTR))	continue;
		if ((returnval == 0) && (numread == 0))		return 0;
		if ( returnval == 0)				break;
		if ( returnval == -1)				return -1;

		numread++;
		
		if (buf[numread - 1] == '\n') {
			buf[numread] = '\0';
			return numread;
		}
	}
	errno = EINVAL;
	return -1;
}

bool get_rec(int fd, strr) {
	return false;
}

int main() {
	buf = new char[buf_size];
	strr sr;
	while(get_rec(0, sr))
		__ sr;
}

