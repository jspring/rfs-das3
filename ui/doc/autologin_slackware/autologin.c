# include <unistd.h>

int main() {
	execlp( "login", "login", "-f", "tilcon", 0);
}
